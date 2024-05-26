//
// Created by tly on 27.02.2024.
//
#include "backends/imgui_impl_d3d.h"
#include "backends/imgui_impl_win32.h"
#include "imgui.h"
#include <array>
#include <cmath>
#include <cstring>
#include <fstream>
#include <map>
#include <thread>
#include <windows.h>

#include "globals.h"

#define hr_assert(x) assert(SUCCEEDED(x))

#include <d3d.h>
#include <ddraw.h>

#include "detours.h"
#include "hook_helper.h"

#include <optional>

extern "C" {
#include <Engine/rdCamera.h>
#include <Engine/rdCanvas.h>
#include <Raster/rdCache.h>
#include <Swr/swrEvent.h>
#include <Swr/swrRace.h>
#include <Swr/swrRender.h>
#include <Swr/swrViewport.h>
#include <Win95/Window.h>
#include <Win95/stdConsole.h>
#include <Win95/stdDisplay.h>
#include <swr.h>
#include <swr/swrSprite.h>
}

extern "C" FILE *hook_log = nullptr;

static WNDPROC WndProcOrig;

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND wnd, UINT code, WPARAM wparam, LPARAM lparam) {
    if (ImGui_ImplWin32_WndProcHandler(wnd, code, wparam, lparam))
        return 1;

    return WndProcOrig(wnd, code, wparam, lparam);
}

static bool imgui_initialized = false;
static bool show_opengl = true;

void fix_lods_for_2_local_players(
    swrModel_Node *node,
    std::map<swrModel_NodeLODSelector *, std::array<float, 8>> &saved_lod_values) {
    if (!node)
        return;

    if (node->type == NODE_LOD_SELECTOR) {
        auto selector = (swrModel_NodeLODSelector *) node;
        auto &values = saved_lod_values[selector];
        std::memcpy(values.data(), selector->lod_distances, sizeof(values));

        int first_elem = 0;
        for (int k = 0; k < selector->node.num_children; k++) {
            if (selector->node.child_nodes[k]) {
                first_elem = k;
                break;
            }
        }

        for (int k = 0; k < selector->node.num_children; k++) {
            selector->lod_distances[k] = k <= first_elem ? 0 : -1;
        }
    }

    if (!(node->type & NODE_HAS_CHILDREN))
        return;

    for (int i = 0; i < node->num_children; i++)
        fix_lods_for_2_local_players(node->child_nodes[i], saved_lod_values);
}

int stdDisplay_Update_Hook() {
    auto *hang = (swrObjHang *) swrEvent_GetItem('Hang', 0);
    //if (hang)
    //    hang->unk70_count = 2;

    // fprintf(hook_log, "[D3DDrawSurfaceToWindow].\n");
    // fflush(hook_log);
    if (!imgui_initialized && std3D_pD3Device) {
        imgui_initialized = true;
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        if (!ImGui::CreateContext())
            std::abort();

        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        const auto wnd = GetActiveWindow();
        if (!ImGui_ImplWin32_Init(wnd))
            std::abort();
        if (!ImGui_ImplD3D_Init(std3D_pD3Device, stdDisplay_g_backBuffer.pVSurface.pDDSurf))
            std::abort();

        WndProcOrig = (WNDPROC) SetWindowLongA(wnd, GWL_WNDPROC, (LONG) WndProc);

        fprintf(hook_log, "[D3DDrawSurfaceToWindow] imgui initialized.\n");
    }

    if (imgui_initialized) {
        ImGui_ImplD3D_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Test");
        ImGui::Text("FPS: %.2f (%.02f ms)", ImGui::GetIO().Framerate,
                    ImGui::GetIO().DeltaTime * 1000);

        for (int i = 0; i < 4; i++) {
            ImGui::Text("Local player %d UI_down=%08x UI_pressed=%08x ingame_1=%08x ingame_2=%08x "
                        "ingame_3=%08x",
                        i, swrUI_localPlayersInputDownBitset[i],
                        swrUI_localPlayersInputPressedBitset[i], ingameLocalPlayerInputBitset1[i],
                        ingameLocalPlayerInputBitset2[i], ingameLocalPlayerInputBitset3[i]);
        }
        auto judge = (swrObjJdge *) swrEvent_GetItem('Jdge', 0);
        if (judge) {
            ImGui::Text("Jdge: obj.flags=%0x flag=%0x", judge->obj.flags, judge->flag);
        }

        if (hang) {
            static bool first = true;
            if (first) {
                first = false;

                char *patch_pos = (char *) 0x45B833;
                DWORD old_protect;
                VirtualProtect(patch_pos, 4, PAGE_EXECUTE_READWRITE, &old_protect);
                memset(patch_pos, 0x90, 4);
            }

            bool two_players = hang->num_local_players == 2;
            if (ImGui::Checkbox("2 Player", &two_players)) {
                hang->num_local_players = two_players ? 2 : 1;
            }
        }

        for (int i = 0; i < 4; i++) {
            auto &unk = swrViewport_array[i];
            ImGui::Text("Viewport %d: flags=%x x=%d y=%d w=%d h=%d fov=%f vis_flags1=%0x "
                        "vis_flags2=%0x root_node=%x",
                        i, unk.flag, unk.viewport_x1, unk.viewport_y1, unk.viewport_x2,
                        unk.viewport_y2, unk.fov_y_degrees, unk.node_flags1_any_match_for_rendering,
                        unk.node_flags1_exact_match_for_rendering, unk.model_root_node);
        }

        int num_test_objs = swrEvent_GetEventCount('Test');
        for (int i = 0; i < num_test_objs; i++) {
            auto test_obj = (swrRace *) swrEvent_GetItem('Test', i);
            ImGui::Text("Test %d: obj.flags=%x flags0=%x flags1=%x", i, test_obj->obj.flags,
                        test_obj->flags0, test_obj->flags1);
        }
        ImGui::End();

        // Rendering
        ImGui::EndFrame();

        if (std3D_pD3Device->BeginScene() >= 0) {
            ImGui::Render();
            ImGui_ImplD3D_RenderDrawData(ImGui::GetDrawData());
            std3D_pD3Device->EndScene();
        }

        while (ShowCursor(true) <= 0)
            ;
    }

    return hook_call_original(stdDisplay_Update);

    auto *front_buffer = stdDisplay_g_frontBuffer.pVSurface.pDDSurf;
    front_buffer->Flip(0, 0);
    return 0;
}

static POINT virtual_cursor_pos{-100, -100};

int stdConsole_GetCursorPos_Hook(int *out_x, int *out_y) {
    if (!out_x || !out_y)
        return 0;

    const auto &io = ImGui::GetIO();

    if (io.WantCaptureMouse) {
        // move mouse pos out of window
        virtual_cursor_pos = {-100, -100};
    } else {
        if (io.MouseDelta.x != 0 || io.MouseDelta.y != 0) {
            // mouse moved, update virtual mouse position
            virtual_cursor_pos.x = (io.MousePos.x * 640) / io.DisplaySize.x;
            virtual_cursor_pos.y = (io.MousePos.y * 480) / io.DisplaySize.y;
        }
    }

    *out_x = virtual_cursor_pos.x;
    *out_y = virtual_cursor_pos.y;
    swrSprite_SetVisible(249, 0);
    return 1;
}

void stdConsole_SetCursorPos_Hook(int X, int Y) {
    virtual_cursor_pos = POINT{X, Y};
}

void update_camera(const swrViewport &viewport) {
    rdCamera_pCurCamera->pClipFrustum->bFarClip = 0;
    rdCamera_pCurCamera->pClipFrustum->zNear = viewport.near_clipping;
    rdCamera_pCurCamera->pClipFrustum->zFar = viewport.far_clipping;
    rdCamera_pCurCamera->fov = std::min(std::max(viewport.fov_y_degrees, 5.0f), 179.0f);
    rdCamera_UpdateProject(rdCamera_pCurCamera, viewport.aspect_ratio);
    const rdMatrix34 mat{
        (const rdVector3 &) viewport.model_matrix.vA,
        (const rdVector3 &) viewport.model_matrix.vB,
        (const rdVector3 &) viewport.model_matrix.vC,
        (const rdVector3 &) viewport.model_matrix.vD,
    };
    rdCamera_Update(&mat);
}

void swrViewport_Render_Hook(int x) {
    auto &viewport = swrViewport_array[x];
    auto cur_canvas = rdCamera_pCurCamera->canvas;

    const bool in_race = swrEvent_GetEventCount('Test') != 0;
    if (in_race && numLocalPlayers == 2) {
        if (x == 1) {
            viewport.viewport_x1 = 0;
            viewport.viewport_y1 = 0;
            viewport.viewport_x2 = 320;
            viewport.viewport_y2 = 120;
        } else if (x == 2) {
            viewport.viewport_x1 = 0;
            viewport.viewport_y1 = 120;
            viewport.viewport_x2 = 320;
            viewport.viewport_y2 = 240;
        }
    } else {
        viewport.viewport_x1 = 0;
        viewport.viewport_y1 = 0;
        viewport.viewport_x2 = 320;
        viewport.viewport_y2 = 240;
    }
    update_camera(viewport);

    std::map<swrModel_NodeLODSelector *, std::array<float, 8>> saved_lod_values;
    if (in_race && numLocalPlayers == 2) {
        fix_lods_for_2_local_players(viewport.model_root_node, saved_lod_values);
    }

    IDirect3DViewport3 *backup_viewport = nullptr;
    std3D_pD3Device->GetCurrentViewport(&backup_viewport);

    int v_x0 = (viewport.viewport_x1) * screen_width / 320;
    int v_y0 = (viewport.viewport_y1) * screen_height / 240;
    int v_x1 = (viewport.viewport_x2) * screen_width / 320;
    int v_y1 = (viewport.viewport_y2) * screen_height / 240;

    IDirect3DViewport3 *d3d_viewport;
    std3D_pDirect3D->CreateViewport(&d3d_viewport, nullptr);

    // Setup viewport
    D3DVIEWPORT2 vp{};
    vp.dwSize = sizeof(D3DVIEWPORT2);
    vp.dwX = v_x0;
    vp.dwY = v_y0;
    vp.dwWidth = v_x1 - v_x0;
    vp.dwHeight = v_y1 - v_y0;
    vp.dvMinZ = 0.0f;
    vp.dvMaxZ = 1.0f;
    vp.dvClipX = v_x0;
    vp.dvClipY = v_y0;
    vp.dvClipWidth = v_x1 - v_x0;
    vp.dvClipHeight = v_y1 - v_y0;

    std3D_pD3Device->AddViewport(d3d_viewport);
    d3d_viewport->SetViewport2(&vp);
    std3D_pD3Device->SetCurrentViewport(d3d_viewport);

    auto canvas = rdCanvas_New(1, &stdDisplay_g_backBuffer, v_x0, v_y0, v_x1, v_y1);
    rdCamera_SetCanvas(rdCamera_pCurCamera, canvas);

    hook_call_original(swrViewport_Render, x);
    rdCamera_SetCanvas(rdCamera_pCurCamera, cur_canvas);
    rdCanvas_Free(canvas);

    rdCache_Flush();

    std3D_pD3Device->SetCurrentViewport(backup_viewport);
    std3D_pD3Device->DeleteViewport(d3d_viewport);
    d3d_viewport->Release();

    // restore lod values
    if (in_race && numLocalPlayers == 2) {
        for (const auto &[selector, values]: saved_lod_values) {
            std::memcpy(selector->lod_distances, values.data(), sizeof(values));
        }
    }
}

int KeyDownForPlayer1Or2_Hook(int key_bitset) {
    if (*(const uint32_t *) 0x50CA3C && !*(const uint32_t *) 0x50CA44)
        return 0;

    if (numLocalPlayers <= 1)
        return ingameLocalPlayerInputBitset1[0] & key_bitset;

    if (pauseState)
        return key_bitset & ingameLocalPlayerInputBitset1[playerNumberInitiatingPause];

    if (ingameLocalPlayerInputBitset1[0] & key_bitset) {
        playerNumberInitiatingPause = 0;
        return 1;
    }
    if (ingameLocalPlayerInputBitset1[1] & key_bitset) {
        playerNumberInitiatingPause = 1;
        return 1;
    }
    return 0;
}

float speedDialPositions1[2]{};
float speedDialPositions2[2]{};

void swrSprite_Draw1_Hook(swrSpriteTexture *a1, int16_t a2, int16_t a3, float a4, float a5,
                          float angle, int16_t a7, int16_t a8, int a9, uint8_t r, uint8_t g,
                          uint8_t b, uint8_t a) {
    int player_number = 0;
    if (a1 == swrSprite_array[19].texture) {
        a1 = swrSpriteTexture_dial_gradient_rgb;
        player_number = 1;
    } else if (a1 == swrSprite_array[20].texture) {
        a1 = swrSpriteTexture_dial_gradient_rgb2;
        player_number = 1;
    }

    speedDialPosition1 = speedDialPositions1[player_number];
    speedDialPosition2 = speedDialPositions2[player_number];
    hook_call_original(swrSprite_Draw1, a1, a2, a3, a4, a5, angle, a7, a8, a9, r, g, b, a);
}

void swrRace_InRaceTimer_Hook(swrScore *param_1, swrObjJdge *param_2) {
    hook_call_original(swrRace_InRaceTimer, param_1, param_2);
    const int player_number = param_1 == secondLocalPlayer ? 1 : 0;
    speedDialPositions1[player_number] = speedDialPosition1;
    speedDialPositions2[player_number] = speedDialPosition2;
}

extern "C" HRESULT WINAPI DirectDrawCreateHook(GUID *guid, LPDIRECTDRAW *dd, IUnknown *unk);
extern "C" HRESULT (*WINAPI DirectDrawCreatePtr)(GUID *guid, LPDIRECTDRAW *dd, IUnknown *unk);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason != DLL_PROCESS_ATTACH)
        return TRUE;

    hook_log = fopen("hook.log", "wb");

    fprintf(hook_log, "[DllMain]\n");
    fflush(hook_log);

    hook_replace(stdDisplay_Update, stdDisplay_Update_Hook);
    hook_replace(swrViewport_Render, swrViewport_Render_Hook);
    hook_replace(stdConsole_GetCursosPos, stdConsole_GetCursorPos_Hook);
    hook_replace(stdConsole_SetCursorPos, stdConsole_SetCursorPos_Hook);
    hook_replace(KeyDownForPlayer1Or2, KeyDownForPlayer1Or2_Hook);
    hook_replace(swrSprite_Draw1, swrSprite_Draw1_Hook);
    hook_replace(swrRace_InRaceTimer, swrRace_InRaceTimer_Hook);
    init_hooks();

    DWORD old_protect;
    VirtualProtect(&IPX_GUID, sizeof(IPX_GUID), PAGE_READWRITE, &old_protect);
    IPX_GUID = TCPIP_GUID;
    //*(uint32_t *) 0x4B79FC =
    //    0;// disable cd check function (makes the game portable, skips some registry checks)
    return TRUE;
}