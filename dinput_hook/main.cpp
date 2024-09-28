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

extern "C"
{
#include <Win95/stdDisplay.h>
#include <Win95/stdConsole.h>
#include <Swr/swrSprite.h>
#include <Swr/swrEvent.h>
#include <Swr/swrUI.h>
#include <Swr/swrRace.h>
#include <Swr/swrLoader.h>
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

    return WndProcOrig(wnd, code, wparam, lparam);
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

    hook_replace(swrUI_GetTrackNameFromId, swrUI_GetTrackNameFromId_Hook);
    hook_replace(swrRace_CourseInfoMenu, swrRace_CourseInfoMenu_Hook);
    hook_replace(stdDisplay_Update, stdDisplay_Update_Hook);
    hook_replace(stdConsole_GetCursorPos, stdConsole_GetCursorPos_Hook);
    hook_replace(stdConsole_SetCursorPos, stdConsole_SetCursorPos_Hook);
    init_hooks();

    return TRUE;
}