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
#include <vector>
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
#include <General/utils.h>
#include <Main/swrControl.h>
#include <Raster/rdCache.h>
#include <Swr/swrEvent.h>
#include <Swr/swrRace.h>
#include <Swr/swrRender.h>
#include <Swr/swrViewport.h>
#include <Win95/DirectX.h>
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

    return CallWindowProcA(WndProcOrig, wnd, code, wparam, lparam);
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
            ImGui::Text("Local player %d UI_down=%08x UI_pressed=%08x down=%08x pressed=%08x "
                        "released=%08x forward=%f turn=%f",
                        i, swrUI_localPlayersInputDownBitset[i],
                        swrUI_localPlayersInputPressedBitset[i], localPlayerInputDownBitset[i],
                        localPlayerInputPressedBitset[i], localPlayerInputReleasedBitset[i],
                        localPlayerForwardAxisInput[i], localPlayerTurnAxisInput[i]);
        }
        auto judge = (swrObjJdge *) swrEvent_GetItem('Jdge', 0);
        if (judge) {
            ImGui::Text("Jdge: obj.flags=%0x flag=%0x", judge->obj.flags, judge->flag);
        }

        if (hang) {
            int num_players = hang->num_local_players;
            if (ImGui::SliderInt("num players", &num_players, 1, 4))
                hang->num_local_players = num_players;

            for (int i = 0; i < hang->num_local_players; i++)
                ImGui::Text("Player %d selected pilot %d", i, hang->pilot_per_player[i]);
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
            ImGui::Text("Test %d: obj.flags=%x flags0=%x flags1=%x score_ptr->unk10=%x "
                        "score_ptr->profile->unk1[3]=%d",
                        i, test_obj->obj.flags, test_obj->flags0, test_obj->flags1,
                        test_obj->score_ptr->unk10 & 0xFF,
                        test_obj->score_ptr->profile ? test_obj->score_ptr->profile->unk1[3] : -1);
        }

        for (int i = 0; i < 15; i++) {
            ImGui::Text("Button %d time: %f", i, swrControl_ButtonDownTime[i]);
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

    if (!imgui_initialized)
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

const static int viewport_per_local_player_num[][5][4]{
    {{0, 0, 320, 240}, {0, 0, 320, 240}},
    {{0, 0, 320, 240}, {0, 0, 320, 120}, {0, 120, 320, 240}},
    //{{0, 0, 320, 240}, {0, 0, 160, 120}, {160, 0, 320, 120}, {0, 120, 160, 240}, {160, 120, 320, 240}},
    //{{0, 0, 320, 240}, {0, 0, 160, 120}, {160, 0, 320, 120}, {0, 120, 160, 240}, {160, 120, 320, 240}},
};

void swrViewport_Render_Hook(int viewport_index) {
    auto &viewport = swrViewport_array[viewport_index];
    auto cur_canvas = rdCamera_pCurCamera->canvas;

    const bool in_race = swrEvent_GetEventCount('Test') != 0;
    if (in_race) {
        const auto &v = viewport_per_local_player_num[numLocalPlayers - 1][viewport_index];
        viewport.viewport_x1 = v[0];
        viewport.viewport_y1 = v[1];
        viewport.viewport_x2 = v[2];
        viewport.viewport_y2 = v[3];
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

    hook_call_original(swrViewport_Render, viewport_index);
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
        return localPlayerInputPressedBitset[0] & key_bitset;

    if (pauseState)
        return key_bitset & localPlayerInputPressedBitset[playerNumberInitiatingPause];

    if (localPlayerInputPressedBitset[0] & key_bitset) {
        playerNumberInitiatingPause = 0;
        return 1;
    }
    if (localPlayerInputPressedBitset[1] & key_bitset) {
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
    const bool in_race = swrEvent_GetEventCount('Test') != 0;
    if (in_race) {
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
    }

    hook_call_original(swrSprite_Draw1, a1, a2, a3, a4, a5, angle, a7, a8, a9, r, g, b, a);
}

void swrRace_InRaceTimer_Hook(swrScore *param_1, swrObjJdge *param_2) {
    hook_call_original(swrRace_InRaceTimer, param_1, param_2);
    const int player_number = param_1 == secondLocalPlayer ? 1 : 0;
    speedDialPositions1[player_number] = speedDialPosition1;
    speedDialPositions2[player_number] = speedDialPosition2;
}

auto store_state(auto &...vars) {
    return std::make_tuple(std::make_pair(&vars, vars)...);
}

auto copy_current_state(const auto &backup) {
    return std::apply(
        [](const auto &...elems) {
            return std::make_tuple(std::make_pair(elems.first, *elems.first)...);
        },
        backup);
}

auto restore_state(const auto &backup) {
    std::apply([](const auto &...elems) { ((*elems.first = elems.second), ...); }, backup);
}

auto second_player_input_state =
    store_state(*(std::array<float, 4> *) &swrControl_AxisInput,
                *(std::array<float, 15> *) &swrControl_ButtonInput,
                *(std::array<float, 15> *) &swrControl_ButtonDownTime,
                *(std::array<char, 15> *) &swrControl_ButtonPressed, swrControl_BrakeInputDown,
                swrControl_ConfirmKeyDown, swrControl_ConfirmKeyNotDown,
                swrControl_ConfirmKeyJustPressed, swrControl_ConfirmKeyJustReleased,
                swrControl_AbortKeyDown, swrControl_AbortKeyNotDown, swrControl_AbortKeyJustPressed,
                swrControl_AbortKeyJustReleased, swrControl_ConfirmKeyDownButNotMouse,
                swrControl_ConfirmKeyButNotMouseJustPressed, swrControl_MaybeMouseDisabledInUI);

void swrControl_ProcessInputs_Hook() {
    /*auto hang = (const swrObjHang *) swrEvent_GetItem('Hang', 0);
    if (!hang || hang->num_local_players <= 1) {
        hook_call_original(swrControl_ProcessInputs);
        return;
    }

    if (hang->num_local_players != 2)
        std::abort();*/

    auto last_read_time = stdControl_lastReadTime;

    const auto input_config_backup = store_state(
        DirectInputNbKeyboard, DirectInputNbMouses, stdControl_numJoystickDevices,
        swrConfig_keyboard_enabled, swrConfig_mouse_enabled, swrConfig_joystick_enabled);

    const auto input_state = copy_current_state(second_player_input_state);

    restore_state(second_player_input_state);
    // second player input first, disable mouse and keyboard input
    DirectInputNbKeyboard = 0;
    DirectInputNbMouses = 0;
    swrConfig_keyboard_enabled = false;
    swrConfig_mouse_enabled = false;
    stdControl_numJoystickDevices = 1;

    hook_call_original(swrControl_ProcessInputs);
    // copy internalInputData to second player, this will make sure that the local player input
    // bitsets are created correctly.
    std::memcpy(internalInputData + 24, internalInputData, 24);
    // copy input state:
    second_player_input_state = copy_current_state(second_player_input_state);

    restore_state(input_state);

    // first player afterwards, this way all global vars should be set as if nothing happened,
    // (hopefully...)
    stdControl_lastReadTime = last_read_time;
    stdControl_numJoystickDevices = 0;
    swrConfig_joystick_enabled = false;
    swrConfig_keyboard_enabled = true;
    DirectInputNbKeyboard = 1;
    DirectInputNbMouses = 0;
    hook_call_original(swrControl_ProcessInputs);

    restore_state(input_config_backup);
}

void swrRace_HandleInputs_Hook(swrRace *player) {
    const int player_index = GetLocalPlayerNumberFromScore(player->score_ptr);
    // this value defines which of the localPlayerInputBitsets is used.
    *(uint8_t *) &player->score_ptr->unk10 = player_index;

    if (player_index == 0) {
        hook_call_original(swrRace_HandleInputs, player);
        return;
    }

    if (player_index != 1)
        std::abort();

    // copy the current input state
    auto input_state = copy_current_state(second_player_input_state);
    // replace it by the second player input state
    restore_state(second_player_input_state);

    hook_call_original(swrRace_HandleInputs, player);

    // restore state by original input state
    restore_state(input_state);
}

swrScore *swrObjHang_PreparePlayerPodData_Hook(swrObjHang *hang, int a2) {
    // select pilot per player
    uint32_t pilot_bitset = 0xFFFFFFF;

    // disallow pilots selected by local players
    for (int i = 0; i < hang->num_local_players; i++)
        pilot_bitset &= ~(1 << hang->pilot_per_player[i]);

    const int first_ai_index = hang->num_local_players;
    if (first_ai_index < hang->num_players) {
        int rest_ai_index = first_ai_index;
        const int favorite_pilot = g_aTrackInfos[hang->track_index].FavoritePilot;
        if (pilot_bitset & (1 << favorite_pilot)) {
            // favorite pilot not selected by local players.
            hang->pilot_per_player[first_ai_index] = favorite_pilot;
            pilot_bitset &= ~(1 << favorite_pilot);
            rest_ai_index++;
        }

        // fill the rest of the AI with random pilots
        for (; rest_ai_index < hang->num_players; rest_ai_index++) {
            while (true) {
                const int pilot = swrUtils_Rand() * 4.6566129e-10 * 23.0;
                if (pilot_bitset & (1 << pilot)) {
                    hang->pilot_per_player[rest_ai_index] = pilot;
                    pilot_bitset &= ~(1 << pilot);
                    break;
                }
            }
        }
    }

    return hook_call_original(swrObjHang_PreparePlayerPodData, hang, a2);
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
    hook_replace(swrControl_ProcessInputs, swrControl_ProcessInputs_Hook);
    hook_replace(swrRace_HandleInputs, swrRace_HandleInputs_Hook);
    hook_replace(swrObjHang_PreparePlayerPodData, swrObjHang_PreparePlayerPodData_Hook);
    init_hooks();

    DWORD old_protect;
    VirtualProtect(&IPX_GUID, sizeof(IPX_GUID), PAGE_READWRITE, &old_protect);
    IPX_GUID = TCPIP_GUID;
    //*(uint32_t *) 0x4B79FC =
    //    0;// disable cd check function (makes the game portable, skips some registry checks)

    //

    // removes code that forces the number of local players to 1, assigns the favorite pilot to
    // player 2 and then random pilots to the other players. this code needs to be reimplemented
    // correctly for multiple local players.
    char *patch_pos = (char *) 0x45B833;
    char *patch_end = (char *) 0x45B8BC;
    VirtualProtect(patch_pos, patch_end - patch_pos, PAGE_EXECUTE_READWRITE, &old_protect);
    memset(patch_pos, 0x90, patch_end - patch_pos);

    return TRUE;
}