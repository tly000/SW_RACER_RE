#include <fstream>
#include <thread>
#include <windows.h>
#include <vector>
#include <cmath>
#include <format>
#include <bit>
#include <optional>
#include <algorithm>

#include "globals.h"
#include "backends/imgui_impl_d3d.h"
#include "backends/imgui_impl_win32.h"
#include "imgui.h"

#define hr_assert(x) assert(SUCCEEDED(x))

#include <d3d.h>
#include <ddraw.h>
#include <shellscalingapi.h>

#include "detours.h"
#include "hook_helper.h"

extern "C"
{
#include <swr/swrRender.h>
#include <Win95/stdConsole.h>
#include <Win95/stdDisplay.h>
#include <swr/swrSprite.h>
#include <Primitives/rdMatrix.h>
#include <swr/swrModel.h>
#include <Platform/std3D.h>
#include <Raster/rdCache.h>
#include <swr/swrObj.h>
#include <swr/swrEvent.h>
}

#include "annodue_interface.h"

extern "C" FILE* hook_log = nullptr;

static WNDPROC WndProcOrig;

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND wnd, UINT code, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(wnd, code, wparam, lparam))
        return 1;

    return WndProcOrig(wnd, code, wparam, lparam);
}

static GlobalState* global_state = nullptr;
static bool imgui_initialized = false;
static bool show_imgui = false;

struct CollisionViewerSettings
{
    bool show_visual_mesh = true;
    float collision_mesh_opacity = 0.3;
    float collision_mesh_brightness = 1.0;
    float collision_line_opacity = 1.0;
    float collision_line_brightness = 1.0;
    bool depth_test = true;
    bool cull_backfaces = true;

    constexpr auto operator<=>(const CollisionViewerSettings&) const = default;
};

const static std::pair<const char*, CollisionViewerSettings> presets[]{
    {
        "transparent overlay",
        CollisionViewerSettings{
            .show_visual_mesh = true,
            .collision_mesh_opacity = 0.3,
            .collision_mesh_brightness = 1.0,
            .collision_line_opacity = 1.0,
            .collision_line_brightness = 1.0,
            .depth_test = true,
            .cull_backfaces = true,
        },
    },
    {
        "wireframe overlay",
        CollisionViewerSettings{
            .show_visual_mesh = true,
            .collision_mesh_opacity = 0.0,
            .collision_mesh_brightness = 1.0,
            .collision_line_opacity = 1.0,
            .collision_line_brightness = 1.0,
            .depth_test = true,
            .cull_backfaces = true,
        },
    },
    {
        "collision mesh only",
        CollisionViewerSettings{
            .show_visual_mesh = false,
            .collision_mesh_opacity = 1.0,
            .collision_mesh_brightness = 0.5,
            .collision_line_opacity = 1.0,
            .collision_line_brightness = 1.0,
            .depth_test = true,
            .cull_backfaces = true,
        },
    },
    {
        "transparent collision mesh only",
        CollisionViewerSettings{
            .show_visual_mesh = false,
            .collision_mesh_opacity = 0.4,
            .collision_mesh_brightness = 1.0,
            .collision_line_opacity = 1.0,
            .collision_line_brightness = 1.0,
            .depth_test = false,
            .cull_backfaces = false,
        },
    },
};

static bool enable_collision_viewer = false;
static CollisionViewerSettings settings = presets[0].second;
static float depth_bias = 0.1;

void render_collision_meshes();

int stdDisplay_Update_Hook()
{
    // fprintf(hook_log, "[D3DDrawSurfaceToWindow].\n");
    // fflush(hook_log);

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
        // ImGui::StyleColorsClassic();
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        const auto wnd = GetActiveWindow();
        assert(ImGui_ImplWin32_Init(wnd));
        assert(ImGui_ImplD3D_Init(std3D_pD3Device, (IDirectDrawSurface4*)stdDisplay_g_backBuffer.ddraw_surface));

        const float scale = 1.0; // TODO

        ImGui::GetIO().FontGlobalScale = scale;
        ImGui::GetStyle().ScaleAllSizes(scale);

        WndProcOrig = (WNDPROC)SetWindowLongA(wnd, GWL_WNDPROC, (LONG)WndProc);

        fprintf(hook_log, "[D3DDrawSurfaceToWindow] imgui initialized.\n");
    }

    if (imgui_initialized)
    {
        ImGui_ImplD3D_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (global_state && global_state->practice_mode)
        {
            if (global_state->in_race == GlobalState::ON)
            {
                if (ImGui::IsKeyPressed('7'))
                    enable_collision_viewer ^= 1;

                if (ImGui::IsKeyPressed('8'))
                    settings.show_visual_mesh ^= 1;

                if (ImGui::IsKeyPressed('9'))
                    show_imgui ^= 1;
            }

            if (show_imgui)
            {
                while (ShowCursor(true) <= 0)
                    ;

                ImGui::Begin("Collision viewer");
                ImGui::Checkbox("show collisions", &enable_collision_viewer);

                auto it = std::find_if(std::begin(presets), std::end(presets), [&](const auto& preset) { return preset.second == settings; });
                int current_preset = it - std::begin(presets);
                int new_preset = current_preset;
                bool preset_changed = ImGui::Combo(
                    "Presets", &new_preset,
                    [](void*, int index, const char** out) -> bool {
                        *out = index == std::size(presets) ? "[modified preset]" : presets[index].first;
                        return true;
                    },
                    nullptr, int(current_preset == std::size(presets) ? std::size(presets) + 1 : std::size(presets)));
                if (new_preset != current_preset)
                    settings = presets[new_preset].second;

                ImGui::Checkbox("show visual mesh", &settings.show_visual_mesh);
                ImGui::SliderFloat("collision mesh opacity", &settings.collision_mesh_opacity, 0, 1);
                ImGui::SliderFloat("collision mesh brightness", &settings.collision_mesh_brightness, 0, 1);
                ImGui::SliderFloat("collision line opacity", &settings.collision_line_opacity, 0, 1);
                ImGui::SliderFloat("collision line brightness", &settings.collision_line_brightness, 0, 1);
                ImGui::Checkbox("depth test", &settings.depth_test);
                ImGui::Checkbox("cull backfaces", &settings.cull_backfaces);
                ImGui::InputFloat("depth bias", &depth_bias);
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("Increase if collision mesh is hidden by visual mesh. Default is 0.1");
                ImGui::End();
            }
        }
        else
        {
            show_imgui = false;
            enable_collision_viewer = false;
        }

        if (!show_imgui)
        {
            while (ShowCursor(false) > 0)
                ;
        }

        // Rendering
        ImGui::EndFrame();

        if (std3D_pD3Device->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplD3D_RenderDrawData(ImGui::GetDrawData());
            std3D_pD3Device->EndScene();
        }
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

void debug_render_mesh(const swrModel_Mesh* mesh, bool mirrored, const rdMatrix44& proj_mat, const rdMatrix44& view_mat, const rdMatrix44& model_matrix)
{
    if (!mesh->collision_vertices)
        return;

    struct Color
    {
        uint8_t b, g, r, a = 255;
    };
    struct D3DVertex
    {
        float x, y, z;
        Color c;
    };

    uint32_t vehicle_reaction_bitset = mesh->mapping ? mesh->mapping->vehicle_reaction : 0;

    static std::array<std::optional<Color>, 32> vehicle_reaction_colors = [] {
        std::array<std::optional<Color>, 32> colors;
        colors[std::countr_zero((uint32_t)ZOn)] = Color{ 255, 180, 50 };
        colors[std::countr_zero((uint32_t)ZOff)] = Color{ 100, 255, 100 };
        colors[std::countr_zero((uint32_t)Fast)] = Color{ 0, 255, 255 };
        colors[std::countr_zero((uint32_t)Slow)] = Color{ 255, 100, 170 };
        colors[std::countr_zero((uint32_t)Swst)] = Color{ 255, 0, 0 };
        colors[std::countr_zero((uint32_t)Slip)] = Color{ 255, 255, 127 };
        colors[std::countr_zero((uint32_t)Lava)] = Color{ 50, 50, 255 };
        colors[std::countr_zero((uint32_t)Fall)] = Color{ 0, 127, 255 };
        colors[std::countr_zero((uint32_t)NRSp)] = Color{ 255, 0, 255 };
        colors[std::countr_zero((uint32_t)Side)] = Color{ 0, 255, 0 };
        return colors;
    }();

    Color color{ 255, 255, 255 };
    for (int i = 0; i < 32; i++)
    {
        if ((vehicle_reaction_bitset & (1 << i)) && vehicle_reaction_colors[i])
        {
            color = *vehicle_reaction_colors[i];
            break;
        }
    }

    static std::vector<D3DVertex> vertices;
    vertices.resize(mesh->num_collision_vertices);

    static std::vector<uint16_t> indices;
    indices.clear();

    const Color line_color{
        color.b * settings.collision_line_brightness,
        color.g * settings.collision_line_brightness,
        color.r * settings.collision_line_brightness,
        255 * settings.collision_line_opacity,
    };

    const Color mesh_color{
        color.b * settings.collision_mesh_brightness,
        color.g * settings.collision_mesh_brightness,
        color.r * settings.collision_mesh_brightness,
        255 * settings.collision_mesh_opacity,
    };

    for (int i = 0; i < mesh->num_collision_vertices; i++)
    {
        const auto& v = mesh->collision_vertices[i];
        vertices[i] = { v.x, v.y, v.z, mesh_color };
    }

    switch (mesh->primitive_type)
    {
    case 3: {
        for (int i = 0; i < mesh->num_primitives; i++)
        {
            indices.push_back(3 * i + 0);
            indices.push_back(3 * i + 1);
            indices.push_back(3 * i + 2);
        }
        break;
    }
    case 4:
        for (int i = 0; i < mesh->num_primitives; i++)
        {
            indices.push_back(4 * i + 0);
            indices.push_back(4 * i + 1);
            indices.push_back(4 * i + 2);

            indices.push_back(4 * i + 0);
            indices.push_back(4 * i + 2);
            indices.push_back(4 * i + 3);
        }
        break;
    case 5: {
        int offset = 0;
        for (int i = 0; i < mesh->num_primitives; i++)
        {
            int s = mesh->primitive_sizes[i];

            for (int j = 0; j < s - 2; j++)
            {
                if (j % 2 == 0)
                {
                    indices.push_back(offset + j + 0);
                    indices.push_back(offset + j + 1);
                    indices.push_back(offset + j + 2);
                }
                else
                {
                    indices.push_back(offset + j + 1);
                    indices.push_back(offset + j + 0);
                    indices.push_back(offset + j + 2);
                }
            }

            offset += s;
        }
        break;
    }
    }

    std3D_pD3Device->SetTransform(D3DTRANSFORMSTATE_WORLD, (D3DMATRIX*)&model_matrix.vA.x);

    if (settings.collision_mesh_opacity != 0.0)
    {
        std3D_pD3Device->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
        std3D_pD3Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_XYZ | D3DFVF_DIFFUSE, vertices.data(), vertices.size(), indices.data(), indices.size(), 0);
    }

    for (auto& v : vertices)
        v.c = line_color;

    if (settings.collision_line_opacity != 0.0)
    {
        std3D_pD3Device->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
        std3D_pD3Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DFVF_XYZ | D3DFVF_DIFFUSE, vertices.data(), vertices.size(), indices.data(), indices.size(), 0);
    }
}

void debug_render_node(const swrModel_unk& current, const swrModel_Node* node, bool mirrored, const rdMatrix44& proj_mat, const rdMatrix44& view_mat, rdMatrix44 model_mat, uint32_t col_flags)
{
    if (!node)
        return;

    if ((node->flags_2 & col_flags) != col_flags)
        return;

    if (node->type == NODE_TRANSFORMED || node->type == NODE_TRANSFORMED_WITH_PIVOT)
    {
        // this node has a transform.
        rdMatrix44 mat{};
        swrModel_NodeGetTransform((const swrModel_NodeTransformed*)node, &mat);
        if (node->type == NODE_TRANSFORMED_WITH_PIVOT && (node->flags_3 & 0x10))
        {
            // some kind of pivot point: the translation v is removed from the transform and then added untransformed.
            const rdVector3 v = ((const swrModel_NodeTransformedWithPivot*)node)->pivot;
            const rdVector3 v_transformed = {
                mat.vA.x * v.x + mat.vB.x * v.y + mat.vC.x * v.z,
                mat.vA.y * v.x + mat.vB.y * v.y + mat.vC.y * v.z,
                mat.vA.z * v.x + mat.vB.z * v.y + mat.vC.z * v.z,
            };
            mat.vD.x += v.x - v_transformed.x;
            mat.vD.y += v.y - v_transformed.y;
            mat.vD.z += v.z - v_transformed.z;
        }

        rdMatrix44 model_mat_new;
        rdMatrix_Multiply44(&model_mat_new, &mat, &model_mat);
        model_mat = model_mat_new;
    }
    else if (node->type == NODE_TRANSFORMED_COMPUTED)
    {
        const swrModel_NodeTransformedComputed* transformed_node = (const swrModel_NodeTransformedComputed*)node;
        rdMatrix34 transform{
            *(const rdVector3*)&model_mat.vA,
            *(const rdVector3*)&model_mat.vB,
            *(const rdVector3*)&model_mat.vC,
            *(const rdVector3*)&model_mat.vD,
        };

        switch (transformed_node->orientation_option)
        {
        case 0:
            break;
        case 1: {
            rdVector3 forward;
            rdVector_Sub3(&forward, &transform.scale, (const rdVector3*)&current.model_matrix.vD);
            rdVector_Normalize3Acc(&forward);

            // first transform up vector into the current coordinate system:
            rdVector3 up;
            rdVector_Scale3(&up, transformed_node->up_vector.x, &transform.rvec);
            rdVector_Scale3Add3(&up, &up, transformed_node->up_vector.y, &transform.lvec);
            rdVector_Scale3Add3(&up, &up, transformed_node->up_vector.z, &transform.uvec);
            float length = rdVector_Normalize3Acc(&up);

            // now build an orthonormal basis
            transform.uvec = up;
            // forward x up -> right
            rdVector_Cross3(&transform.rvec, &forward, &transform.uvec);
            rdVector_Normalize3Acc(&transform.rvec);
            // up x right -> forward
            rdVector_Cross3(&transform.lvec, &transform.uvec, &transform.rvec);
            // no normalize, because uvec and rvec are otrhogonal

            // scale
            rdVector_Scale3(&transform.rvec, length, &transform.rvec);
            rdVector_Scale3(&transform.lvec, length, &transform.lvec);
            rdVector_Scale3(&transform.uvec, length, &transform.uvec);
        }
        break;
        case 2: // TODO
        case 3: // TODO
        default:
            std::abort();
        }

        if (transformed_node->follow_model_position == 1)
            transform.scale = *(const rdVector3*)&current.model_matrix.vD;

        rdMatrix_Copy44_34(&model_mat, &transform);
    }

    if (node->flags_5 & 0x1)
        mirrored = !mirrored;

    if (node->type == NODE_MESH_GROUP)
    {
        for (int i = 0; i < node->num_children; i++)
            debug_render_mesh(node->meshes[i], mirrored, proj_mat, view_mat, model_mat);
    }
    else if (node->type == NODE_LOD_SELECTOR)
    {
        const swrModel_NodeLODSelector* lods = (const swrModel_NodeLODSelector*)node;
        // find correct lod node
        int i = 1;
        for (; i < 8; i++)
        {
            if (lods->lod_distances[i] == -1 || lods->lod_distances[i] >= 10)
                break;
        }
        if (i - 1 < node->num_children)
            debug_render_node(current, node->child_nodes[i - 1], mirrored, proj_mat, view_mat, model_mat, col_flags);
    }
    else if (node->type == NODE_SELECTOR)
    {
        const swrModel_NodeSelector* selector = (const swrModel_NodeSelector*)node;
        int child = selector->selected_child_node;
        switch (child)
        {
        case -2:
            // dont render any child node
            break;
        case -1:
            // render all child nodes
            for (int i = 0; i < node->num_children; i++)
                debug_render_node(current, node->child_nodes[i], mirrored, proj_mat, view_mat, model_mat, col_flags);
            break;
        default:
            if (child >= 0 && child < node->num_children)
                debug_render_node(current, node->child_nodes[child], mirrored, proj_mat, view_mat, model_mat, col_flags);

            break;
        }
    }
    else
    {
        for (int i = 0; i < node->num_children; i++)
            debug_render_node(current, node->child_nodes[i], mirrored, proj_mat, view_mat, model_mat, col_flags);
    }
}

void render_collision_meshes()
{
    if (!std3D_pD3Device || !rdCamera_pCurCamera)
        return;

    swrModel_Node* root_node = swrModel_unk_array[0].model_root_node;
    if (!root_node)
        return;

    auto hang = (const swrObjHang*)swrEvent_GetItem('Hang', 0);
    const auto& track_info = g_aTrackInfos[hang->track_index];
    const uint32_t col_flags = 0x2 | (1 << (4 + track_info.PlanetTrackNumber));
    const bool mirrored = (GameSettingFlags & 0x4000) != 0;

    IDirect3DViewport3* backup_viewport;
    std3D_pD3Device->GetCurrentViewport(&backup_viewport);

    IDirect3DViewport3* viewport;
    std3D_pDirect3D->CreateViewport(&viewport, nullptr);

    // Setup viewport
    D3DVIEWPORT2 vp{};
    vp.dwSize = sizeof(D3DVIEWPORT2);
    vp.dwX = 0;
    vp.dwY = 0;
    vp.dwWidth = screen_width;
    vp.dwHeight = screen_height;
    vp.dvMinZ = -1.0f;
    vp.dvMaxZ = 1.0f;
    vp.dvClipX = -1;
    vp.dvClipY = 1;
    vp.dvClipWidth = 2;
    vp.dvClipHeight = 2;

    std3D_pD3Device->AddViewport(viewport);
    viewport->SetViewport2(&vp);
    std3D_pD3Device->SetCurrentViewport(viewport);

    std3D_SetRenderState(Std3DRenderState(STD3D_RS_UNKNOWN_1 | STD3D_RS_UNKNOWN_2 | STD3D_RS_UNKNOWN_200));
    std3D_pD3Device->SetRenderState(D3DRENDERSTATE_ZENABLE, settings.depth_test);

    std3D_pD3DTex = NULL;
    std3D_pD3Device->SetTexture(0, NULL);

    if (settings.cull_backfaces)
        std3D_pD3Device->SetRenderState(D3DRENDERSTATE_CULLMODE, mirrored ? D3DCULL_CCW : D3DCULL_CW);

    if (std3D_pD3Device->BeginScene() >= 0)
    {
        rdMatrix44 model_mat;
        rdMatrix_SetIdentity44(&model_mat);

        rdMatrix44 view_mat;
        rdMatrix_Copy44_34(&view_mat, &rdCamera_pCurCamera->view_matrix);

        rdMatrix44 rotation{
            { 1, 0, 0, 0 },
            { 0, 0, -1, 0 },
            { 0, 1, 0, 0 },
            { 0, 0, 0, 1 },
        };

        rdMatrix44 view_mat_corrected;
        rdMatrix_Multiply44(&view_mat_corrected, &view_mat, &rotation);

        const auto& frustum = rdCamera_pCurCamera->pClipFrustum;
        float f = frustum->zFar;
        float n = frustum->zNear;
        const float t = 1.0f / std::tan(0.5 * rdCamera_pCurCamera->fov / 180.0 * 3.14159);
        float a = float(screen_height) / screen_width;
        const rdMatrix44 proj_mat{
            { mirrored ? -t : t, 0, 0, 0 },
            { 0, t / a, 0, 0 },
            { 0, 0, -1, -1 },
            { 0, 0, -1 - depth_bias, 0 },
        };

        std3D_pD3Device->SetTransform(D3DTRANSFORMSTATE_VIEW, (D3DMATRIX*)&view_mat_corrected.vA.x);
        std3D_pD3Device->SetTransform(D3DTRANSFORMSTATE_PROJECTION, (D3DMATRIX*)&proj_mat.vA.x);

        debug_render_node(swrModel_unk_array[0], root_node->child_nodes[3], mirrored, proj_mat, view_mat_corrected, model_mat, col_flags);
        std3D_pD3Device->EndScene();
    }
    std3D_pD3Device->SetCurrentViewport(backup_viewport);
    std3D_pD3Device->DeleteViewport(viewport);

    std3D_pD3Device->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
    std3D_pD3Device->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);

    std3D_pD3Device->SetRenderState(D3DRENDERSTATE_ZENABLE, 1);

    viewport->Release();
}

void swrModel_UnkDraw_Hook(int x)
{
    if (!enable_collision_viewer)
    {
        hook_call_original(swrModel_UnkDraw, x);
        return;
    }

    auto* root_node = swrModel_unk_array[x].model_root_node;
    std::vector<swrModel_Node*> temp_children(root_node->child_nodes, root_node->child_nodes + root_node->num_children);

    // first render the terrain...
    if (settings.show_visual_mesh)
    {
        for (int i = 4; i < root_node->num_children; i++)
            root_node->child_nodes[i] = NULL;

        hook_call_original(swrModel_UnkDraw, x);
    }
    else
    {
        stdDisplay_BackBufferFill(0, 0, 0, 0);
    }

    rdCache_Flush();
    render_collision_meshes();

    // ... and after the collision meshes render the rest:
    for (int i = 0; i < root_node->num_children; i++)
        root_node->child_nodes[i] = i < 4 ? NULL : temp_children[i];

    hook_call_original(swrModel_UnkDraw, x);

    // restore node:
    std::copy(temp_children.begin(), temp_children.end(), root_node->child_nodes);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason != DLL_PROCESS_ATTACH)
        return TRUE;

    hook_log = fopen("hook.log", "wb");

    fprintf(hook_log, "[DllMain]\n");
    fflush(hook_log);

    hook_replace(stdDisplay_Update, stdDisplay_Update_Hook);
    // hook_replace(stdConsole_GetCursosPos, stdConsole_GetCursorPos_Hook);
    // hook_replace(stdConsole_SetCursorPos, stdConsole_SetCursorPos_Hook);
    hook_replace(swrModel_UnkDraw, swrModel_UnkDraw_Hook);
    init_hooks();

    return TRUE;
}

extern "C" __declspec(dllexport) const char* PluginName()
{
    return "collision_viewer";
}

extern "C" __declspec(dllexport) const char* PluginVersion()
{
    return "0.1";
}

extern "C" __declspec(dllexport) uint32_t PluginCompatibilityVersion()
{
    return 17;
}

extern "C" __declspec(dllexport) void OnInit(GlobalState* global_state, GlobalFunction* global_functions)
{
    ::global_state = global_state;
}

extern "C" __declspec(dllexport) void OnInitLate(GlobalState* global_state, GlobalFunction* global_functions)
{}

extern "C" __declspec(dllexport) void OnDeinit(GlobalState* global_state, GlobalFunction* global_functions)
{}