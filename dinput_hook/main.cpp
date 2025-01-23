//
// Created by tly on 27.02.2024.
//
#include "backends/imgui_impl_d3d.h"
#include "backends/imgui_impl_win32.h"
#include "imgui.h"
#include <fstream>
#include <thread>
#include <windows.h>

#include "globals.h"

#define hr_assert(x) assert(SUCCEEDED(x))

#include <d3d.h>
#include <ddraw.h>

#include "detours.h"
#include "hook_helper.h"

#include <optional>
#include <unordered_map>
#include <cstring>

extern "C"
{
#include <Win95/stdDisplay.h>
#include <Win95/stdConsole.h>
#include <Swr/swrSprite.h>
#include <Swr/swrEvent.h>
#include <Swr/swrUI.h>
#include <Swr/swrRace.h>
#include <Swr/swrLoader.h>
#include <Raster/rdCache.h>
#include <Swr/swrViewport.h>
#include <Swr/swrRace.h>
#include <Swr/swrModel.h>
#include <Engine/rdMaterial.h>
#include <Platform/stdControl.h>
#include <Primitives/rdMatrix.h>
#include <Primitives/rdMath.h>
#include <Engine/rdCamera.h>
}

extern "C"
{
    FILE* hook_log = nullptr;
}

static WNDPROC WndProcOrig;

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND wnd, UINT code, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(wnd, code, wparam, lparam))
        return 1;

    return CallWindowProcA(WndProcOrig, wnd, code, wparam, lparam);
}

static bool imgui_initialized = false;

int stdDisplay_Update_Hook()
{
    // fprintf(hook_log, "[D3DDrawSurfaceToWindow].\n");
    fflush(hook_log);

    if (!imgui_initialized && std3D_pD3Device)
    {
        imgui_initialized = true;
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        assert(ImGui::CreateContext());
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        const auto wnd = GetActiveWindow();
        assert(ImGui_ImplWin32_Init(wnd));
        assert(ImGui_ImplD3D_Init(std3D_pD3Device, (IDirectDrawSurface4*)stdDisplay_g_backBuffer.pVSurface.pDDSurf));

        WndProcOrig = (WNDPROC)SetWindowLongA(wnd, GWL_WNDPROC, (LONG)WndProc);

        fprintf(hook_log, "[D3DDrawSurfaceToWindow] imgui initialized.\n");
    }

    if (imgui_initialized)
    {
        ImGui_ImplD3D_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Test");
        swrObjHang* hang = (swrObjHang*)swrEvent_GetItem('Hang', 0);
        if (hang)
        {
            ImGui::Text("hang->circuitIdx=%d", int(hang->circuitIdx));
            ImGui::Text("hang->track_index=%d", int(hang->track_index));
        }

        int data[6];
        for (int i = 0; i < 6; i++)
            data[i] = stdControl_aAxisPos[i];

        ImGui::Text("num joystick axes: %d", swrConfig_joystickNbAxis);
        for (int i = 0; i < 6; i++)
            ImGui::Text("joystick input %d: %f %d", i, swrControl_JoystickAxisInputs[i], data[i]);

        ImGui::End();

        // Rendering
        ImGui::EndFrame();

        if (std3D_pD3Device->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplD3D_RenderDrawData(ImGui::GetDrawData());
            std3D_pD3Device->EndScene();
        }

        while (ShowCursor(true) <= 0)
            ;
    }

    return hook_call_original(stdDisplay_Update);
}

static POINT virtual_cursor_pos{ -100, -100 };

int stdConsole_GetCursorPos_Hook(int* out_x, int* out_y)
{
    if (!out_x || !out_y)
        return 0;

    const auto& io = ImGui::GetIO();

    if (io.WantCaptureMouse)
    {
        // move mouse pos out of window
        virtual_cursor_pos = { -100, -100 };
    }
    else
    {
        if (io.MouseDelta.x != 0 || io.MouseDelta.y != 0)
        {
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

void stdConsole_SetCursorPos_Hook(int X, int Y)
{
    virtual_cursor_pos = POINT{ X, Y };
}

extern "C" HRESULT WINAPI DirectDrawCreateHook(GUID* guid, LPDIRECTDRAW* dd, IUnknown* unk);
extern "C" HRESULT (*WINAPI DirectDrawCreatePtr)(GUID* guid, LPDIRECTDRAW* dd, IUnknown* unk);

void write(uint32_t address, void* data, int size)
{
    DWORD old_protect;
    VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy((void*)address, data, size);
    VirtualProtect((void*)address, size, old_protect, &old_protect);
}

const char* swrUI_GetTrackNameFromId_Hook(int trackId)
{
    if (trackId == -1)
    {
        static char buff[64];
        sprintf(buff, "~%dSelect custom track", std::rand() % 9 + 1);
        return buff;
    }

    return hook_call_original(swrUI_GetTrackNameFromId, trackId);
}

std::optional<std::string> replacement_modelblock_bin;
std::optional<std::string> replacement_splineblock_bin;
std::optional<std::string> replacement_textureblock_bin;

void swrRace_CourseInfoMenu_Hook(swrObjHang* hang)
{
    if (hang->track_index == -1)
    {
        OPENFILENAMEA ofn{};
        char szFile[260]; // buffer for file name

        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFile = szFile;
        // Set lpstrFile[0] to '\0' so that GetOpenFileName does not
        // use the contents of szFile to initialize itself.
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = nullptr;
        ofn.nFilterIndex = 0;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn))
        {
            replacement_modelblock_bin = szFile;
            const std::filesystem::path folder = std::filesystem::path(*replacement_modelblock_bin).parent_path();
            replacement_splineblock_bin = (folder / "out_splineblock.bin").generic_string();
            replacement_textureblock_bin = (folder / "out_textureblock.bin").generic_string();
            hang->track_index = 22;

            *(const char**)0x4B9598 = replacement_modelblock_bin->c_str();
            *(const char**)0x4B9590 = replacement_splineblock_bin->c_str();
            *(const char**)0x4B9594 = replacement_textureblock_bin->c_str();
        }
        else
        {
            // no track selected, go back to circuit selection ui
            hang->state = swrObjHang_STATE_SELECT_PLANET;
            return; // <-- do not draw course info, it would crash
        }
    }
    else if (hang->circuitIdx != 4)
    {
        *(const char**)0x4B9598 = "data/lev01/out_modelblock.bin";
        *(const char**)0x4B9590 = "data/lev01/out_splineblock.bin";
        *(const char**)0x4B9594 = "data/lev01/out_textureblock.bin";
    }
    hook_call_original(swrRace_CourseInfoMenu, hang);
}

std::unordered_map<swrModel_NodeTransformed*, rdMatrix34> prev_transforms, curr_transforms;
std::optional<rdMatrix44> prev_cam_matrix;
rdMatrix44 curr_cam_matrix;

auto interpolate_transforms(const auto& a, const auto& b, float t)
{
    // TODO hack
    decltype(a) result{};
    for (int i = 0; i < sizeof(a) / sizeof(float); i++)
        ((float*)&result)[i] = (1 - t) * ((const float*)&a)[i] + t * ((const float*)&b)[i];

    return result;
}

void collect_all_transforms(swrModel_Node* node, std::unordered_map<swrModel_NodeTransformed*, rdMatrix34>& transforms)
{
    if (!node)
        return;

    if (node->type & NODE_IS_TRANSFORMED)
    {
        auto transformed_node = (swrModel_NodeTransformed*)node;
        transforms[transformed_node] = transformed_node->transform;
    }

    if (!(node->type & NODE_HAS_CHILDREN))
        return;

    for (int i = 0; i < node->num_children; i++)
        collect_all_transforms(node->child_nodes[i], transforms);
}

void restore_transforms(const std::unordered_map<swrModel_NodeTransformed*, rdMatrix34>& transforms)
{
    for (const auto& [node, transform] : transforms)
        node->transform = transform;
}

void (*sub_445980)(int16_t a1, int16_t a2) = (void (*)(int16_t, int16_t))0x445980;

void sub_445980_Hook(int16_t a1, int16_t a2)
{
    const auto backup = std::make_tuple(swrTextEntries1Count, swrTextEntries2Count, numMiniMapPositions);
    if (a2 != 2)
        sub_445980(a1, a2);

    if (a2 == 2)
    {
        curr_transforms.clear();
        collect_all_transforms(swrViewport_Get(1)->model_root_node, curr_transforms);
        curr_cam_matrix = swrViewport_Get(1)->model_matrix;

        const int N = 3;
        for (int i = 0; i < N; i++)
        {
            const float t = float(i + 1) / N;
            if (!prev_transforms.empty())
            {
                for (const auto& [node, transform] : curr_transforms)
                {
                    auto it = prev_transforms.find(node);
                    if (it == prev_transforms.end())
                        continue;

                    node->transform = interpolate_transforms(it->second, transform, t);
                }
            }

            if (i != 0)
            {
                swrViewport_UpdateCameras();
                if (prev_cam_matrix)
                    swrViewport_Get(1)->model_matrix = interpolate_transforms(*prev_cam_matrix, curr_cam_matrix, t);

                swrDisplay_SkipNextFrameUpdate = false;
                rdCache_Flush();
                rdCache_FlushAlpha();
                stdDisplay_g_frontBuffer.pVSurface.pDDSurf->Flip(0, 0);
                // stdDisplay_Update();

                rdCache_AdvanceFrame();
                stdDisplay_BackBufferFill(backBufferClearColor[0], backBufferClearColor[1], backBufferClearColor[2], 0);
                std::tie(swrTextEntries1Count, swrTextEntries2Count, numMiniMapPositions) = backup;
            }
            if (prev_cam_matrix)
            {
                rdMatrix44 cam_matrix = interpolate_transforms(*prev_cam_matrix, curr_cam_matrix, t);
                swrViewport_Get(1)->model_matrix = cam_matrix;
                rdMatrix34 cam_matrix_{
                    (const rdVector3&)cam_matrix.vA,
                    (const rdVector3&)cam_matrix.vB,
                    (const rdVector3&)cam_matrix.vC,
                    (const rdVector3&)cam_matrix.vD,
                };
                rdCamera_Update(&cam_matrix_);
            }
            // RenderAll();
            sub_445980(a1, a2);
        }

        restore_transforms(curr_transforms);
        std::swap(curr_transforms, prev_transforms);
        prev_cam_matrix = curr_cam_matrix;
    }
}

void swrRace_HandleInputs_Hook(swrRace* player)
{
    // fprintf(hook_log, "swrRace_DebugFlag=%08x\n", swrRace_DebugFlag);
    // fflush(hook_log);
    swrRace_DebugFlag |= 0x2000000;
    localPlayerForwardAxisInput[2] = -(stdControl_aAxisPos[5] - 32768) / 32768.0;
    localPlayerTurnAxisInput[2] = (stdControl_aAxisPos[2] - 32768) / 32768.0;
    hook_call_original(swrRace_HandleInputs, player);
}

void** texture_buffer_replacement = nullptr;

void swrModel_InitializeTextureBuffer_Hook()
{
    swrLoader_OpenBlock(swrLoader_TYPE_TEXTURE_BLOCK);
    swrLoader_ReadAt(swrLoader_TYPE_TEXTURE_BLOCK, 0, &texture_count, 4u);
    texture_count = SWAP32(texture_count);

    texture_buffer_replacement = (void**)malloc(texture_count * sizeof(uint32_t));
    memset(texture_buffer_replacement, 0, texture_count * sizeof(uint32_t));

    char* range_begin = (char*)0x00447420;
    char* range_end = (char*)0x004475ED;
    DWORD old_protect;
    VirtualProtect(range_begin, range_end - range_begin, PAGE_EXECUTE_READWRITE, &old_protect);

    *(void**)0x4474B1 = texture_buffer_replacement;
    *(void**)0x4474C4 = texture_buffer_replacement;
    *(void**)0x447555 = texture_buffer_replacement;
    *(void**)0x4475D5 = texture_buffer_replacement;
    *(void**)0x4475E7 = texture_buffer_replacement + texture_count;

    VirtualProtect(range_begin, range_end - range_begin, old_protect, &old_protect);

    swrLoader_CloseBlock(swrLoader_TYPE_TEXTURE_BLOCK);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason != DLL_PROCESS_ATTACH)
        return TRUE;

    hook_log = fopen("hook.log", "wb");

    fprintf(hook_log, "[DllMain]\n");
    fflush(hook_log);

    // enable one more circuit
    uint32_t max_circuit_idx = 4;
    write(0x043B0BA + 6, &max_circuit_idx, sizeof(max_circuit_idx));

    // remove "planet not loaded" message
    char zero = '\0';
    write(0x4C0EE4, &zero, 1);

    // frame interpolation:
    // DetourTransactionBegin();
    // DetourAttach(&sub_445980, sub_445980_Hook);
    // DetourTransactionCommit();

    // custom track menu:
    // hook_replace(swrUI_GetTrackNameFromId, swrUI_GetTrackNameFromId_Hook);
    // hook_replace(swrRace_CourseInfoMenu, swrRace_CourseInfoMenu_Hook);

    // imgui:
    // hook_replace(stdDisplay_Update, stdDisplay_Update_Hook);
    // hook_replace(stdConsole_GetCursorPos, stdConsole_GetCursorPos_Hook);
    // hook_replace(stdConsole_SetCursorPos, stdConsole_SetCursorPos_Hook);

    // rrdual mode:
    // hook_replace(swrRace_HandleInputs, swrRace_HandleInputs_Hook);

    // remove texture count limitation
    // hook_replace(swrModel_InitializeTextureBuffer, swrModel_InitializeTextureBuffer_Hook);

    init_hooks();

    return TRUE;
}