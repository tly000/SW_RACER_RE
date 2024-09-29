#pragma once

#include "tiny_gltf.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>

enum gltfFlags {
    Empty = 0,
    isIndexed = 1 << 0,
    hasNormals = 1 << 1,
    hasTexCoords = 1 << 2,// == hasTexture
};

struct meshInfos {
    int gltfFlags;
    GLuint VAO{0};
    GLuint PositionBO{0};
    GLuint NormalBO{0};
    GLuint TexCoordsBO{0};
    GLuint EBO{0};
    GLuint glTexture{0};// TODO: glTexture in a material instead
};

struct pbrShader {
    GLuint handle{0};
    GLint proj_matrix_pos{-1};
    GLint view_matrix_pos{-1};
    GLint model_matrix_pos{-1};
    GLint baseColorFactor_pos{-1};
    GLint metallicFactor_pos{-1};
    GLint model_id_pos{-1};
};

struct gltfModel {
    tinygltf::Model gltf;
    // mesh index, gltfFlags
    std::map<int, meshInfos> mesh_infos;
    // gltfFlags, pbrShader
    std::map<int, pbrShader> shader_pool;
};

extern std::vector<gltfModel> g_models;

void load_gltf_models();

void gltfModel_to_imgui(gltfModel &model);

void setupModel(gltfModel &model);