#include "gltf_utils.h"

// Define these only in *one* .cc file.
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION// optional. disable exception handling.
#include "tiny_gltf.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <format>

#include "../imgui_utils.h"
#include "../shaders_utils.h"
#include "../meshes.h"

extern "C" FILE *hook_log;

extern ImGuiState imgui_state;

std::vector<gltfModel> g_models;

bool default_material_infos_initialized = false;
materialInfos default_material_infos{};

std::optional<struct iblShader> g_iblShader = std::nullopt;

void load_gltf_models() {
    fprintf(hook_log, "[load_gltf_models]\n");
    tinygltf::TinyGLTF loader;

    std::vector<std::string> asset_names = {"Box.gltf", "BoxTextured.gltf", "box_textured_red.gltf",
                                            "MetalRoughSpheresNoTextures.gltf",
                                            "MetalRoughSpheresTextured.gltf"};
    std::string asset_dir = "./assets/gltf/";

    for (auto name: asset_names) {
        std::string err;
        std::string warn;
        tinygltf::Model model;
        bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, asset_dir + name);
        //bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, argv[1]); // for binary glTF(.glb)

        if (!warn.empty()) {
            fprintf(hook_log, "Warn: %s\n", warn.c_str());
        }

        if (!err.empty()) {
            fprintf(hook_log, "Err: %s\n", err.c_str());
        }

        if (!ret) {
            fprintf(hook_log, "Failed to parse %s glTF\n", name.c_str());
        }
        fflush(hook_log);

        g_models.push_back(gltfModel{.filename = name,
                                     .setuped = false,
                                     .gltf = model,
                                     .material_infos = {},
                                     .mesh_infos = {},
                                     .shader_pool = {}});
        fprintf(hook_log, "Loaded %s\n", name.c_str());
    }
}

static unsigned int getComponentCount(int tinygltfType) {
    switch (tinygltfType) {
        case TINYGLTF_TYPE_SCALAR:
            return 1;
        case TINYGLTF_TYPE_VEC2:
            return 2;
        case TINYGLTF_TYPE_VEC3:
            return 3;
        case TINYGLTF_TYPE_VEC4:
            return 4;
        case TINYGLTF_TYPE_MAT2:
            return 4;
        case TINYGLTF_TYPE_MAT3:
            return 9;
        case TINYGLTF_TYPE_MAT4:
            return 16;
    }

    fprintf(hook_log, "Unrecognized tinygltfType %d", tinygltfType);
    fflush(hook_log);
    assert(false);
}

static unsigned int getComponentByteSize(int componentType) {
    switch (componentType) {
        case TINYGLTF_COMPONENT_TYPE_BYTE:         //GL_BYTE
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:// GL_UNSIGNED_BYTE
            return 1;
        case TINYGLTF_COMPONENT_TYPE_SHORT:         // GL_SHORT
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:// GL_UNSIGNED_SHORT
            return 2;
            // No GL equivalent ?
            // TINYGLTF_COMPONENT_TYPE_INT
        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:// GL_UNSIGNED_INT
        case TINYGLTF_COMPONENT_TYPE_FLOAT:       // GL_FLOAT
            return 4;
    }

    fprintf(hook_log, "Unrecognized glType %d", componentType);
    fflush(hook_log);
    assert(false);
}

static void setupAttribute(unsigned int bufferObject, tinygltf::Model &model, int accessorId,
                           unsigned int location) {
    const tinygltf::Accessor &accessor = model.accessors[accessorId];
    const tinygltf::BufferView &bufferView = model.bufferViews[accessor.bufferView];
    auto buffer = reinterpret_cast<const float *>(model.buffers[bufferView.buffer].data.data() +
                                                  accessor.byteOffset + bufferView.byteOffset);

    glBindBuffer(bufferView.target, bufferObject);
    glBufferData(bufferView.target,
                 accessor.count * getComponentCount(accessor.type) *
                     getComponentByteSize(accessor.componentType),
                 buffer, GL_STATIC_DRAW);

    glVertexAttribPointer(location, getComponentCount(accessor.type), accessor.componentType,
                          GL_FALSE, bufferView.byteStride, 0);
}

static void setupTexture(GLuint textureObject, tinygltf::Model &model, int textureId) {
    tinygltf::Texture texture = model.textures[textureId];
    if (texture.source == -1) {
        fprintf(hook_log, "Source not provided for texture %d\n", textureId);
        fflush(hook_log);
        return;
    }
    tinygltf::Image image = model.images[texture.source];

    glBindTexture(GL_TEXTURE_2D, textureObject);
    GLint internalFormat = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.width, image.height, 0, internalFormat,
                 image.pixel_type, image.image.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    if (texture.sampler == -1) {// Default sampler
        // Might be ugly but we'll see
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    } else {
        tinygltf::Sampler sampler = model.samplers[texture.sampler];

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sampler.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sampler.wrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, sampler.minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, sampler.magFilter);
    }
}

static void createTexture(GLuint &textureObjectOut, int width, int height, int pixelType,
                          void *pixelData, GLint wrapS, GLint wrapT, GLint minFilter,
                          GLint magFilter, bool generateMipMaps) {

    glGenTextures(1, &textureObjectOut);

    glBindTexture(GL_TEXTURE_2D, textureObjectOut);
    GLint internalFormat = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, pixelType,
                 pixelData);
    if (generateMipMaps)
        glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

// IBL Parameters
const size_t ibl_textureSize = 256;
const size_t ibl_lambertianSampleCount = 2048;
const size_t ibl_ggxSampleCount = 1024;
const size_t ibl_lowestMipLevel = 4;
const size_t ibl_lutResolution = 1024;
// TODO: Should switch based on OES_texture_float_linear, EXT_color_buffer_half_float, default byte
const GLint ibl_internalFormat = GL_RGBA32F;
const GLint ibl_format = GL_RGBA;
const GLint ibl_targetType = GL_FLOAT;
size_t ibl_mipmapLevels;

static GLuint createIBLCubemapTexture(bool generateMipMaps) {
    GLuint targetCubemap;
    glGenTextures(1, &targetCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, targetCubemap);

    for (size_t i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, ibl_internalFormat, ibl_textureSize,
                     ibl_textureSize, 0, ibl_format, ibl_targetType, NULL);
    }

    if (generateMipMaps) {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    } else {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return targetCubemap;
}

GLuint createIBLLutTexture(void) {
    GLuint targetTexture;
    glGenTextures(1, &targetTexture);
    glBindTexture(GL_TEXTURE_2D, targetTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, ibl_internalFormat, ibl_lutResolution, ibl_lutResolution, 0,
                 ibl_format, ibl_targetType, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return targetTexture;
}

enum IBLDistribution {
    Lambertian = 0,
    GGX = 1,
    Charlie = 2,
};

iblShader createIBLShader() {
    iblShader shader;

    // https://github.com/KhronosGroup/glTF-Sample-Renderer/tree/main/source/shaders
    const char *vertex_shader_source = R"(
#version 130

precision highp float;

out vec2 texCoord;

void main(void)
{
    float x = float((gl_VertexID & 1) << 2);
    float y = float((gl_VertexID & 2) << 1);
    texCoord.x = x * 0.5;
    texCoord.y = y * 0.5;
    gl_Position = vec4(x - 1.0, y - 1.0, 0, 1);
}
)";

    const char *fragment_shader_source = R"(
#version 420

precision highp float;
#define MATH_PI 3.1415926535897932384626433832795

layout(binding = 0) uniform samplerCube CubeMap;

// enum
const int cLambertian = 0;
const int cGGX = 1;
const int cCharlie = 2;

uniform float roughness;
uniform int sampleCount;
uniform int width;
uniform int distribution; // enum
uniform int currentFace;
uniform int isGeneratingLUT;

// 0: Byte Target Texture (normalized)
// 1: Float Target Texture
uniform int floatTexture;

uniform float intensityScale;

in vec2 texCoord;

out vec4 fragmentColor;

vec3 uvToXYZ(int face, vec2 uv)
{
    if(face == 0)
        return vec3(1.f, uv.y, -uv.x);
    else if(face == 1)
        return vec3(-1.f, uv.y, uv.x);
    else if(face == 2)
        return vec3(+uv.x, -1.f, +uv.y);
    else if(face == 3)
        return vec3(+uv.x, 1.f, -uv.y);
    else if(face == 4)
        return vec3(+uv.x, uv.y, 1.f);
    else {// face == 5
        return vec3( -uv.x, +uv.y, -1.f);
    }
}

vec2 dirToUV(vec3 dir)
{
    return vec2(
        0.5f + 0.5f * atan(dir.z, dir.x) / MATH_PI,
        1.f - acos(dir.y) / MATH_PI
    );
}

float saturate(float v)
{
    return clamp(v, 0.0f, 1.0f);
}

// Hammersley Points on the Hemisphere
// CC BY 3.0 (Holger Dammertz <3)
// http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html
// with adapted interface
float radicalInverse_VdC(uint bits)
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

// hammersley2d describes a sequence of points in the 2d unit square [0,1)^2
// that can be used for quasi Monte Carlo integration
vec2 hammersley2d(int i, int N) {
    return vec2(float(i)/float(N), radicalInverse_VdC(uint(i)));
}

// Hemisphere Sample

// TBN generates a tangent bitangent normal coordinate frame from the normal
// (the normal must be normalized)
mat3 generateTBN(vec3 normal)
{
    vec3 bitangent = vec3(0.0, 1.0, 0.0);

    float NdotUp = dot(normal, vec3(0.0, 1.0, 0.0));
    float epsilon = 0.0000001;
    if (1.0 - abs(NdotUp) <= epsilon)
    {
        // Sampling +Y or -Y, so we need a more robust bitangent.
        if (NdotUp > 0.0)
        {
            bitangent = vec3(0.0, 0.0, 1.0);
        }
        else
        {
            bitangent = vec3(0.0, 0.0, -1.0);
        }
    }

    vec3 tangent = normalize(cross(bitangent, normal));
    bitangent = cross(normal, tangent);

    return mat3(tangent, bitangent, normal);
}

struct MicrofacetDistributionSample
{
    float pdf;
    float cosTheta;
    float sinTheta;
    float phi;
};

float D_GGX(float NdotH, float roughness) {
    float a = NdotH * roughness;
    float k = roughness / (1.0 - NdotH * NdotH + a * a);
    return k * k * (1.0 / MATH_PI);
}

// GGX microfacet distribution
// https://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.html
// This implementation is based on https://bruop.github.io/ibl/,
//  https://www.tobias-franke.eu/log/2014/03/30/notes_on_importance_sampling.html
// and https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch20.html
MicrofacetDistributionSample GGX(vec2 xi, float roughness)
{
    MicrofacetDistributionSample ggx;

    // evaluate sampling equations
    float alpha = roughness * roughness;
    ggx.cosTheta = saturate(sqrt((1.0 - xi.y) / (1.0 + (alpha * alpha - 1.0) * xi.y)));
    ggx.sinTheta = sqrt(1.0 - ggx.cosTheta * ggx.cosTheta);
    ggx.phi = 2.0 * MATH_PI * xi.x;

    // evaluate GGX pdf (for half vector)
    ggx.pdf = D_GGX(ggx.cosTheta, alpha);

    // Apply the Jacobian to obtain a pdf that is parameterized by l
    // see https://bruop.github.io/ibl/
    // Typically you'd have the following:
    // float pdf = D_GGX(NoH, roughness) * NoH / (4.0 * VoH);
    // but since V = N => VoH == NoH
    ggx.pdf /= 4.0;

    return ggx;
}

// NDF
float D_Ashikhmin(float NdotH, float roughness)
{
    float alpha = roughness * roughness;
    // Ashikhmin 2007, "Distribution-based BRDFs"
    float a2 = alpha * alpha;
    float cos2h = NdotH * NdotH;
    float sin2h = 1.0 - cos2h;
    float sin4h = sin2h * sin2h;
    float cot2 = -cos2h / (a2 * sin2h);
    return 1.0 / (MATH_PI * (4.0 * a2 + 1.0) * sin4h) * (4.0 * exp(cot2) + sin4h);
}

// NDF
float D_Charlie(float sheenRoughness, float NdotH)
{
    sheenRoughness = max(sheenRoughness, 0.000001); //clamp (0,1]
    float invR = 1.0 / sheenRoughness;
    float cos2h = NdotH * NdotH;
    float sin2h = 1.0 - cos2h;
    return (2.0 + invR) * pow(sin2h, invR * 0.5) / (2.0 * MATH_PI);
}

MicrofacetDistributionSample Charlie(vec2 xi, float roughness)
{
    MicrofacetDistributionSample charlie;

    float alpha = roughness * roughness;
    charlie.sinTheta = pow(xi.y, alpha / (2.0*alpha + 1.0));
    charlie.cosTheta = sqrt(1.0 - charlie.sinTheta * charlie.sinTheta);
    charlie.phi = 2.0 * MATH_PI * xi.x;

    // evaluate Charlie pdf (for half vector)
    charlie.pdf = D_Charlie(alpha, charlie.cosTheta);

    // Apply the Jacobian to obtain a pdf that is parameterized by l
    charlie.pdf /= 4.0;

    return charlie;
}

MicrofacetDistributionSample Lambertian(vec2 xi, float roughness)
{
    MicrofacetDistributionSample lambertian;

    // Cosine weighted hemisphere sampling
    // http://www.pbr-book.org/3ed-2018/Monte_Carlo_Integration/2D_Sampling_with_Multidimensional_Transformations.html#Cosine-WeightedHemisphereSampling
    lambertian.cosTheta = sqrt(1.0 - xi.y);
    lambertian.sinTheta = sqrt(xi.y); // equivalent to `sqrt(1.0 - cosTheta*cosTheta)`;
    lambertian.phi = 2.0 * MATH_PI * xi.x;

    lambertian.pdf = lambertian.cosTheta / MATH_PI; // evaluation for solid angle, therefore drop the sinTheta

    return lambertian;
}


// getImportanceSample returns an importance sample direction with pdf in the .w component
vec4 getImportanceSample(int sampleIndex, vec3 N, float roughness)
{
    // generate a quasi monte carlo point in the unit square [0.1)^2
    vec2 xi = hammersley2d(sampleIndex, sampleCount);

    MicrofacetDistributionSample importanceSample;

    // generate the points on the hemisphere with a fitting mapping for
    // the distribution (e.g. lambertian uses a cosine importance)
    if(distribution == cLambertian)
    {
        importanceSample = Lambertian(xi, roughness);
    }
    else if(distribution == cGGX)
    {
        // Trowbridge-Reitz / GGX microfacet model (Walter et al)
        // https://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.html
        importanceSample = GGX(xi, roughness);
    }
    else if(distribution == cCharlie)
    {
        importanceSample = Charlie(xi, roughness);
    }

    // transform the hemisphere sample to the normal coordinate frame
    // i.e. rotate the hemisphere to the normal direction
    vec3 localSpaceDirection = normalize(vec3(
        importanceSample.sinTheta * cos(importanceSample.phi),
        importanceSample.sinTheta * sin(importanceSample.phi),
        importanceSample.cosTheta
    ));
    mat3 TBN = generateTBN(N);
    vec3 direction = TBN * localSpaceDirection;

    return vec4(direction, importanceSample.pdf);
}

// Mipmap Filtered Samples (GPU Gems 3, 20.4)
// https://developer.nvidia.com/gpugems/gpugems3/part-iii-rendering/chapter-20-gpu-based-importance-sampling
// https://cgg.mff.cuni.cz/~jaroslav/papers/2007-sketch-fis/Final_sap_0073.pdf
float computeLod(float pdf)
{
    float lod = 0.5 * log2( 6.0 * float(width) * float(width) / (float(sampleCount) * pdf));

    return lod;
}

vec3 filterColor(vec3 N)
{
    vec3 color = vec3(0.f);
    float weight = 0.0f;

    for(int i = 0; i < sampleCount; ++i)
    {
        vec4 importanceSample = getImportanceSample(i, N, roughness);

        vec3 H = vec3(importanceSample.xyz);
        float pdf = importanceSample.w;

        // mipmap filtered samples (GPU Gems 3, 20.4)
        float lod = computeLod(pdf);

        if(distribution == cLambertian)
        {
            // sample lambertian at a lower resolution to avoid fireflies
            vec3 lambertian = textureLod(CubeMap, H, lod).rgb * intensityScale;

            //// the below operations cancel each other out
            // lambertian *= NdotH; // lamberts law
            // lambertian /= pdf; // invert bias from importance sampling
            // lambertian /= MATH_PI; // convert irradiance to radiance https://seblagarde.wordpress.com/2012/01/08/pi-or-not-to-pi-in-game-lighting-equation/

            color += lambertian;
        }
        else if(distribution == cGGX || distribution == cCharlie)
        {
            // Note: reflect takes incident vector.
            vec3 V = N;
            vec3 L = normalize(reflect(-V, H));
            float NdotL = dot(N, L);

            if (NdotL > 0.0)
            {
                if(roughness == 0.0)
                {
                    // without this the roughness=0 lod is too high
                    lod = 0.0;
                }
                vec3 sampleColor = textureLod(CubeMap, L, lod).rgb * intensityScale;
                color += sampleColor * NdotL;
                weight += NdotL;
            }
        }
    }

    if(weight != 0.0f)
    {
        color /= weight;
    }
    else
    {
        color /= float(sampleCount);
    }

    return color.rgb ;
}

// From the filament docs. Geometric Shadowing function
// https://google.github.io/filament/Filament.html#toc4.4.2
float V_SmithGGXCorrelated(float NoV, float NoL, float roughness) {
    float a2 = pow(roughness, 4.0);
    float GGXV = NoL * sqrt(NoV * NoV * (1.0 - a2) + a2);
    float GGXL = NoV * sqrt(NoL * NoL * (1.0 - a2) + a2);
    return 0.5 / (GGXV + GGXL);
}

// https://github.com/google/filament/blob/master/shaders/src/brdf.fs#L136
float V_Ashikhmin(float NdotL, float NdotV)
{
    return clamp(1.0 / (4.0 * (NdotL + NdotV - NdotL * NdotV)), 0.0, 1.0);
}

// Compute LUT for GGX distribution.
// See https://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf
vec3 LUT(float NdotV, float roughness)
{
    // Compute spherical view vector: (sin(phi), 0, cos(phi))
    vec3 V = vec3(sqrt(1.0 - NdotV * NdotV), 0.0, NdotV);

    // The macro surface normal just points up.
    vec3 N = vec3(0.0, 0.0, 1.0);

    // To make the LUT independant from the material's F0, which is part of the Fresnel term
    // when substituted by Schlick's approximation, we factor it out of the integral,
    // yielding to the form: F0 * I1 + I2
    // I1 and I2 are slighlty different in the Fresnel term, but both only depend on
    // NoL and roughness, so they are both numerically integrated and written into two channels.
    float A = 0.0;
    float B = 0.0;
    float C = 0.0;

    for(int i = 0; i < sampleCount; ++i)
    {
        // Importance sampling, depending on the distribution.
        vec4 importanceSample = getImportanceSample(i, N, roughness);
        vec3 H = importanceSample.xyz;
        // float pdf = importanceSample.w;
        vec3 L = normalize(reflect(-V, H));

        float NdotL = saturate(L.z);
        float NdotH = saturate(H.z);
        float VdotH = saturate(dot(V, H));
        if (NdotL > 0.0)
        {
            if (distribution == cGGX)
            {
                // LUT for GGX distribution.

                // Taken from: https://bruop.github.io/ibl
                // Shadertoy: https://www.shadertoy.com/view/3lXXDB
                // Terms besides V are from the GGX PDF we're dividing by.
                float V_pdf = V_SmithGGXCorrelated(NdotV, NdotL, roughness) * VdotH * NdotL / NdotH;
                float Fc = pow(1.0 - VdotH, 5.0);
                A += (1.0 - Fc) * V_pdf;
                B += Fc * V_pdf;
                C += 0.0;
            }

            if (distribution == cCharlie)
            {
                // LUT for Charlie distribution.
                float sheenDistribution = D_Charlie(roughness, NdotH);
                float sheenVisibility = V_Ashikhmin(NdotL, NdotV);

                A += 0.0;
                B += 0.0;
                C += sheenVisibility * sheenDistribution * NdotL * VdotH;
            }
        }
    }

    // The PDF is simply pdf(v, h) -> NDF * <nh>.
    // To parametrize the PDF over l, use the Jacobian transform, yielding to: pdf(v, l) -> NDF * <nh> / 4<vh>
    // Since the BRDF divide through the PDF to be normalized, the 4 can be pulled out of the integral.
    return vec3(4.0 * A, 4.0 * B, 4.0 * 2.0 * MATH_PI * C) / float(sampleCount);
}

void main()
{
    vec3 color = vec3(0);

    if(isGeneratingLUT == 0)
    {
        vec2 newUV = texCoord ;

        newUV = newUV*2.0-1.0;

        vec3 scan = uvToXYZ(currentFace, newUV);

        vec3 direction = normalize(scan);
        direction.y = -direction.y;

        color = filterColor(direction);
    }
    else
    {
        color = LUT(texCoord.x, texCoord.y);
        fragmentColor.rgb = color;
        fragmentColor.a = 1.0;
        return;
    }

    fragmentColor.a = 1.0;

    if(floatTexture == 0)
    {
        float maxV = max(max(color.r,color.g),color.b);
        color /= intensityScale;
        color = clamp(color, 0.0f, 1.0f);
    }

    fragmentColor.rgb = color;
}
)";

    std::optional<GLuint> program_opt =
        compileProgram(1, &vertex_shader_source, 1, &fragment_shader_source);
    if (!program_opt.has_value())
        std::abort();
    GLuint program = program_opt.value();

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    shader = {
        .handle = program,
        .emptyVAO = VAO,
        .roughness_pos = glGetUniformLocation(program, "roughness"),
        .sampleCount_pos = glGetUniformLocation(program, "sampleCount"),
        .width_pos = glGetUniformLocation(program, "width"),
        .distribution_pos = glGetUniformLocation(program, "distribution"),
        .currentFace_pos = glGetUniformLocation(program, "currentFace"),
        .isGeneratingLUT_pos = glGetUniformLocation(program, "isGeneratingLUT"),
        .floatTexture_pos = glGetUniformLocation(program, "floatTexture"),
        .intensityScale_pos = glGetUniformLocation(program, "intensityScale"),
    };
    return shader;
}


void applyFilter(GLuint framebuffer, int distribution, float roughness, unsigned int targetMipLevel,
                 GLuint targetCubemap, unsigned int sampleCount) {
    size_t currentTextureSize = ibl_textureSize >> targetMipLevel;

    for (size_t i = 0; i < 6; i++) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, targetCubemap, targetMipLevel);
        glBindTexture(GL_TEXTURE_CUBE_MAP, targetCubemap);
        glViewport(0, 0, currentTextureSize, currentTextureSize);
        glClearColor(1.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        iblShader shader = g_iblShader.value();
        GLuint ibl_filtering_program = shader.handle;
        glUseProgram(ibl_filtering_program);
        glBindTexture(GL_TEXTURE_CUBE_MAP, targetCubemap);

        glUniform1f(shader.roughness_pos, roughness);
        glUniform1i(shader.sampleCount_pos, sampleCount);
        glUniform1i(shader.width_pos, ibl_textureSize);
        glUniform1i(shader.distribution_pos, distribution);
        glUniform1i(shader.currentFace_pos, i);
        glUniform1i(shader.isGeneratingLUT_pos, 0);
        glUniform1i(shader.floatTexture_pos, 1);
        glUniform1f(shader.intensityScale_pos, 1.0);// TODO: scaleValue on HDR

        glBindVertexArray(shader.emptyVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void sampleLut(GLuint framebuffer, GLuint input_cubemap, int distribution, GLuint targetTexture,
               size_t currentTextureSize) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, targetTexture, 0);

    glBindTexture(GL_TEXTURE_2D, targetTexture);
    glViewport(0, 0, currentTextureSize, currentTextureSize);
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    iblShader shader = g_iblShader.value();
    glUseProgram(shader.handle);

    glBindTexture(GL_TEXTURE_CUBE_MAP, input_cubemap);

    glUniform1f(shader.roughness_pos, 0.0);
    glUniform1i(shader.sampleCount_pos, 512);
    glUniform1i(shader.width_pos, 0.0);
    glUniform1i(shader.distribution_pos, distribution);
    glUniform1i(shader.currentFace_pos, 0);
    glUniform1i(shader.isGeneratingLUT_pos, 1);

    glBindVertexArray(shader.emptyVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void setupIBL(GLuint input_cubemap) {
    // TODO: check for OES_float_texture here

    GLuint ibl_framebuffer;
    glGenFramebuffers(1, &ibl_framebuffer);
    GLuint lambertianCubemapID = createIBLCubemapTexture(false);
    GLuint ggxCubemapID = createIBLCubemapTexture(true);
    // GLuint sheenCubemapID;

    ibl_mipmapLevels = floor(log2(ibl_textureSize)) + 1 - ibl_lowestMipLevel;

    // Read and create HDR texture and convert it to cubemap. We already have a cubemap as input in this case

    if (!g_iblShader.has_value()) {
        g_iblShader = createIBLShader();
    }

    {// cubeMapToLambertian
        applyFilter(ibl_framebuffer, 0, 0.0, 0, lambertianCubemapID, ibl_lambertianSampleCount);
    }
    {// cubeMapToGGX
        for (size_t currentMipLevel = 0; currentMipLevel <= ibl_mipmapLevels; currentMipLevel++) {
            float roughness = currentMipLevel / (ibl_mipmapLevels - 1);
            applyFilter(ibl_framebuffer, 1, roughness, currentMipLevel, ggxCubemapID,
                        ibl_ggxSampleCount);
        }
    }
    // cubeMapToSheen
    // applyFilter(...)

    {// sampleGGXLut
        GLuint ggxLutTextureID = createIBLLutTexture();
        sampleLut(ibl_framebuffer, input_cubemap, IBLDistribution::GGX, ggxLutTextureID,
                  ibl_lutResolution);
    }
}

pbrShader compile_pbr(ImGuiState &state, int gltfFlags) {
    pbrShader shader;
    bool hasNormals = gltfFlags & gltfFlags::HasNormals;
    bool hasTexCoords = gltfFlags & gltfFlags::HasTexCoords;
    bool unlit = gltfFlags & gltfFlags::Unlit;
    fprintf(hook_log, "Compiling shader %s%s%s...", hasNormals ? "NORMALS," : "",
            hasTexCoords ? "TEXCOORDS," : "", unlit ? "UNLIT" : "");
    fflush(hook_log);

    (void) state;

    const std::string defines = std::format("{}{}{}", hasNormals ? "#define HAS_NORMALS\n" : "",
                                            hasTexCoords ? "#define HAS_TEXCOORDS\n" : "",
                                            unlit ? "#define MATERIAL_UNLIT\n" : "");

    // Taken from https://github.com/KhronosGroup/glTF-Sample-Renderer
    const char *vertex_shader_source = R"(
layout(location = 0) in vec3 position;
#ifdef HAS_NORMALS
layout(location = 1) in vec3 normal;
#endif
#ifdef HAS_TEXCOORDS
layout(location = 2) in vec2 texcoords;
#endif

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform int model_id;

out vec3 worldPosition;
#ifdef HAS_NORMALS
out vec3 passNormal;
#endif
#ifdef HAS_TEXCOORDS
out vec2 passTexcoords;
#endif

void main() {
    vec4 pos = modelMatrix * vec4(position, 1.0);
    worldPosition = vec3(pos.xyz) / pos.w;

    // Yes, precomputing modelView is better and we should do it
    gl_Position = projMatrix * viewMatrix * pos;

#ifdef HAS_NORMALS
    passNormal = normal;
#endif
#ifdef HAS_TEXCOORDS
    passTexcoords = texcoords;
#endif
}
)";

    const char *fragment_shader_source = R"(
in vec3 worldPosition;
#ifdef HAS_NORMALS
in vec3 passNormal;
#endif
#ifdef HAS_TEXCOORDS
in vec2 passTexcoords;
#endif

uniform vec4 baseColorFactor;
// useful with punctual light or IBL
uniform float metallicFactor;
uniform float roughnessFactor;
uniform vec3 cameraWorldPosition;

#ifdef HAS_TEXCOORDS
layout(binding = 0) uniform sampler2D baseColorTexture;
layout(binding = 1) uniform sampler2D metallicRoughnessTexture;
#endif

// Spot light
struct Light {
    vec3 color;
    float intensity;

    vec3 position;
};
const Light light = Light(vec3(1), 100.0, vec3(0, 0.03, 0.40));

out vec4 outColor;

// Utils
float clampedDot(vec3 x, vec3 y) {
    return clamp(dot(x, y), 0.0, 1.0);
}

const float GAMMA = 2.2;
const float INV_GAMMA = 1.0 / GAMMA;

vec3 linearTosRGB(vec3 color) {
    return pow(color, vec3(INV_GAMMA));
}

vec3 toneMap(vec3 color) {
    return linearTosRGB(color);
}
// IBL Functions

// lambertianEnvSampler
// GGXEnvSampler
// const envRotation
// u_envIntensity
// u_mipCount
// GGXLUT
vec3 getDiffuseLight(vec3 n) {
    // vec4 textureSample = texture(u_LambertianEnvSampler, u_EnvRotation * n);
    // textureSample.rgb *= u_EnvIntensity;
    // return textureSample.rgb;
    return vec3(0);
}

vec4 getSpecularSample(vec3 reflection, float lod)
{
    // vec4 textureSample = textureLod(u_GGXEnvSampler, u_EnvRotation * reflection, lod);
    // textureSample.rgb *= u_EnvIntensity;
    // return textureSample;
    return vec4(0);
}

vec3 getIBLRadianceGGX(vec3 n, vec3 v, float roughness)
{
    // float NdotV = clampedDot(n, v);
    // float lod = roughness * float(u_MipCount - 1);
    // vec3 reflection = normalize(reflect(-v, n));
    // vec4 specularSample = getSpecularSample(reflection, lod);

    // vec3 specularLight = specularSample.rgb;

    // return specularLight;
    return vec3(0);
}

vec3 getIBLGGXFresnel(vec3 n, vec3 v, float roughness, vec3 F0, float specularWeight) {
    // see https://bruop.github.io/ibl/#single_scattering_results at Single Scattering Results
    // Roughness dependent fresnel, from Fdez-Aguera
    // float NdotV = clampedDot(n, v);
    // vec2 brdfSamplePoint = clamp(vec2(NdotV, roughness), vec2(0.0, 0.0), vec2(1.0, 1.0));
    // vec2 f_ab = texture(u_GGXLUT, brdfSamplePoint).rg;
    // vec3 Fr = max(vec3(1.0 - roughness), F0) - F0;
    // vec3 k_S = F0 + Fr * pow(1.0 - NdotV, 5.0);
    // vec3 FssEss = specularWeight * (k_S * f_ab.x + f_ab.y);

    // // Multiple scattering, from Fdez-Aguera
    // float Ems = (1.0 - (f_ab.x + f_ab.y));
    // vec3 F_avg = specularWeight * (F0 + (1.0 - F0) / 21.0);
    // vec3 FmsEms = Ems * FssEss * F_avg / (1.0 - F_avg * Ems);

    // return FssEss + FmsEms;
    return vec3(0);
}

// Light BRDF

vec3 getLightIntensity(Light light, vec3 pointToLight) {
    float rangeAttenuation = 1.0 / pow(length(pointToLight), 2.0); // unlimited
    float spotAttenuation = 1.0;

    return rangeAttenuation * spotAttenuation * light.intensity * light.color;
}

vec3 F_Schlick(vec3 f0, vec3 f90, float VdotH) {
    return f0 + (f90 - f0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
}

const float M_PI = 3.141592653589793;

vec3 BRDF_lambertian(vec3 diffuseColor) {
    return (diffuseColor / M_PI);
}

// Smith Joint GGX
// Note: Vis = G / (4 * NdotL * NdotV)
// see Eric Heitz. 2014. Understanding the Masking-Shadowing Function in Microfacet-Based BRDFs. Journal of Computer Graphics Techniques, 3
// see Real-Time Rendering. Page 331 to 336.
// see https://google.github.io/filament/Filament.md.html#materialsystem/specularbrdf/geometricshadowing(specularg)

float V_GGX(float NdotL, float NdotV, float alphaRoughness)
{
    float alphaRoughnessSq = alphaRoughness * alphaRoughness;

    float GGXV = NdotL * sqrt(NdotV * NdotV * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);
    float GGXL = NdotV * sqrt(NdotL * NdotL * (1.0 - alphaRoughnessSq) + alphaRoughnessSq);

    float GGX = GGXV + GGXL;
    if (GGX > 0.0)
    {
        return 0.5 / GGX;
    }
    return 0.0;
}

// The following equation(s) model the distribution of microfacet normals across the area being drawn (aka D())
// Implementation from "Average Irregularity Representation of a Roughened Surface for Ray Reflection" by T. S. Trowbridge, and K. P. Reitz
// Follows the distribution function recommended in the SIGGRAPH 2013 course notes from EPIC Games [1], Equation 3.

float D_GGX(float NdotH, float alphaRoughness)
{
    float alphaRoughnessSq = alphaRoughness * alphaRoughness;
    float f = (NdotH * NdotH) * (alphaRoughnessSq - 1.0) + 1.0;
    return alphaRoughnessSq / (M_PI * f * f);
}

vec3 BRDF_specularGGX(float alphaRoughness, float NdotL, float NdotV, float NdotH) {
    float Vis = V_GGX(NdotL, NdotV, alphaRoughness);
    float D = D_GGX(NdotH, alphaRoughness);

    return vec3(Vis * D);
}

void main() {

    vec4 baseColor;

#ifdef HAS_TEXCOORDS
    vec4 texColor = texture(baseColorTexture, passTexcoords);
    baseColor = baseColorFactor * texColor;
#else
    baseColor = baseColorFactor;
#endif

    vec3 color;
#ifndef MATERIAL_UNLIT
    vec3 v = normalize(cameraWorldPosition - worldPosition);
    vec3 n = passNormal;
    vec3 f0_dielectric = vec3(0.04);
    float specularWeight = 1.0;
    vec3 f90_dielectric = vec3(1.0);

    vec4 metallicRoughnessTexel = texture(metallicRoughnessTexture, passTexcoords);
    float metallic = metallicFactor * metallicRoughnessTexel.r;
    float perceptualRoughness = roughnessFactor * metallicRoughnessTexel.g;
    float alphaRoughness = perceptualRoughness * perceptualRoughness;

// USE_IBL
    // getDiffuseLight();
    // getIBLRadianceGGX();
    // getIBLGGXFresnel();

// END USE_IBL

// FOR EACH LIGHT
    vec3 pointToLight = light.position - worldPosition;
    vec3 l = normalize(pointToLight);
    vec3 h = normalize(l + v);
    float NdotL = clampedDot(n, l);
    float NdotV = clampedDot(n, v);
    float NdotH = clampedDot(n, h);
    float LdotH = clampedDot(l, h);
    float VdotH = clampedDot(v, h);

    vec3 dielectric_fresnel = F_Schlick(f0_dielectric * specularWeight, f90_dielectric, abs(VdotH));
    vec3 metal_fresnel = F_Schlick(baseColor.rgb, vec3(1.0), abs(VdotH));

    vec3 lightIntensity = getLightIntensity(light, pointToLight);
    vec3 l_diffuse = lightIntensity * NdotL * BRDF_lambertian(baseColor.rgb);
    vec3 l_specular_metal = lightIntensity * NdotL * BRDF_specularGGX(alphaRoughness, NdotL, NdotV, NdotH);
    vec3 l_specular_dielectric = l_specular_metal;
    vec3 l_metal_brdf = metal_fresnel * l_specular_metal;
    vec3 l_dielectric_brdf = mix(l_diffuse, l_specular_dielectric, dielectric_fresnel);
    vec3 l_color = mix(l_dielectric_brdf, l_metal_brdf, metallic);
    color = l_color;
// # END FOR EACH
#else
// MATERIAL_UNLIT
    color = baseColor.rgb;
#endif
    // outColor = vec4(1.0, 0.0, 1.0, 0.0);
    outColor = vec4(toneMap(color), baseColor.a);
}
)";

    const char *vertex_sources[]{"#version 420\n", defines.c_str(), vertex_shader_source};
    const char *fragment_sources[]{"#version 420\n", defines.c_str(), fragment_shader_source};

    std::optional<GLuint> program_opt = compileProgram(
        std::size(vertex_sources), vertex_sources, std::size(fragment_sources), fragment_sources);
    if (!program_opt.has_value())
        std::abort();
    GLuint program = program_opt.value();

    shader = {
        .handle = program,
        .proj_matrix_pos = glGetUniformLocation(program, "projMatrix"),
        .view_matrix_pos = glGetUniformLocation(program, "viewMatrix"),
        .model_matrix_pos = glGetUniformLocation(program, "modelMatrix"),
        .baseColorFactor_pos = glGetUniformLocation(program, "baseColorFactor"),
        .metallicFactor_pos = glGetUniformLocation(program, "metallicFactor"),
        .roughnessFactor_pos = glGetUniformLocation(program, "roughnessFactor"),
        .model_id_pos = glGetUniformLocation(program, "model_id"),
    };

    // TODO: Setup requirements for IBL
    //      TODO: generate the textures, then setup them
    //      environmentFiltering (init -> filterAll)
    //      view + imageHDR -> env textures
    // lambertianEnvSampler // diffuseEnvMap
    // GGXEnvSampler // specularEnvMap
    // const envRotation
    // u_envIntensity // iblIntensity
    // u_mipCount // mipCount
    // GGXLUT // lut

    fprintf(hook_log, "Done\n");
    fflush(hook_log);

    return shader;
}

void setupModel(gltfModel &model) {
    fprintf(hook_log, "Setuping model %s...\n", model.filename.c_str());
    fflush(hook_log);

    model.setuped = true;

    // flags for some models
    const char *unlit_models[] = {
        "Box.gltf", "BoxTextured.gltf", "box_textured_red.gltf",
        //   "MetalRoughSpheresTextured.gltf"
    };
    int additionnalFlags = gltfFlags::Empty;
    for (size_t i = 0; i < std::size(unlit_models); i++) {
        if (strcmp(unlit_models[i], model.filename.c_str()) == 0)
            additionnalFlags |= gltfFlags::Unlit;
    }

    for (size_t meshId = 0; meshId < model.gltf.meshes.size(); meshId++) {
        meshInfos mesh_infos{};
        mesh_infos.gltfFlags |= additionnalFlags;

        if (model.gltf.meshes[meshId].primitives.size() > 1) {
            fprintf(hook_log, "Multiples primitives for mesh %zu not yet supported in renderer\n",
                    meshId);
            fflush(hook_log);
            continue;
        }

        int primitiveId = 0;
        tinygltf::Primitive primitive = model.gltf.meshes[meshId].primitives[primitiveId];
        int indicesAccessorId = primitive.indices;
        if (indicesAccessorId == -1) {
            fprintf(hook_log, "Un-indexed topology not yet supported for mesh %zu in renderer\n",
                    meshId);
            fflush(hook_log);
            continue;
        }
        mesh_infos.gltfFlags |= gltfFlags::IsIndexed;

        GLint drawMode = primitive.mode;
        if (drawMode == -1) {
            fprintf(hook_log, "Unsupported draw mode %d in renderer\n", drawMode);
            fflush(hook_log);
            continue;
        }
        int materialIndex = primitive.material;
        if (materialIndex == -1) {
            fprintf(hook_log, "Material-less model not yet supported in renderer\n");
            fflush(hook_log);
            continue;
        }

        int positionAccessorId = -1;
        int normalAccessorId = -1;
        int texcoordAccessorId = -1;
        for (const auto &[key, value]: primitive.attributes) {
            if (key == "POSITION")
                positionAccessorId = value;
            if (key == "NORMAL") {
                mesh_infos.gltfFlags |= gltfFlags::HasNormals;
                normalAccessorId = value;
            }
            if (key == "TEXCOORD_0") {
                mesh_infos.gltfFlags |= gltfFlags::HasTexCoords;
                texcoordAccessorId = value;
            }
        }

        if (positionAccessorId == -1) {
            fprintf(hook_log, "Unsupported mesh %zu without position attribute in renderer\n",
                    meshId);
            fflush(hook_log);
            continue;
        }
        if (mesh_infos.gltfFlags & gltfFlags::HasNormals == 0) {
            fprintf(hook_log, "Unsupported mesh %zu without normal attribute in renderer\n",
                    meshId);
            fflush(hook_log);
            continue;
        }

        if (model.gltf.accessors[indicesAccessorId].type != TINYGLTF_TYPE_SCALAR) {
            fprintf(hook_log,
                    "Error: indices accessor does not have type scalar in renderer for mesh %zu\n",
                    meshId);
            fflush(hook_log);
            continue;
        }
        const tinygltf::Accessor &indicesAccessor = model.gltf.accessors[indicesAccessorId];

        if (indicesAccessor.componentType != GL_UNSIGNED_SHORT)// 0x1403
        {
            fprintf(hook_log, "Unsupported type for indices buffer of mesh %zu in renderer\n",
                    meshId);
            fflush(hook_log);
            continue;
        }

        // compile shader with options
        // https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html#appendix-b-brdf-implementation
        if (!model.shader_pool.contains(mesh_infos.gltfFlags)) {
            model.shader_pool[mesh_infos.gltfFlags] =
                compile_pbr(imgui_state, mesh_infos.gltfFlags);
        }

        // create GL objects
        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        GLuint VBOs[3];
        glGenBuffers(std::size(VBOs), VBOs);

        GLuint EBO;
        glGenBuffers(1, &EBO);

        mesh_infos.VAO = VAO;
        mesh_infos.PositionBO = VBOs[0];
        mesh_infos.NormalBO = VBOs[1];
        mesh_infos.TexCoordsBO = VBOs[2];
        mesh_infos.EBO = EBO;

        if (materialIndex != -1 && !model.material_infos.contains(materialIndex)) {

            unsigned int glTextures[2];
            glGenTextures(std::size(glTextures), glTextures);

            materialInfos material_infos{.baseColorGLTexture = glTextures[0],
                                         .metallicRoughnessGLTexture = glTextures[1]};
            model.material_infos[materialIndex] = material_infos;
        }
        model.mesh_infos[meshId] = mesh_infos;

        // Setup VAO
        pbrShader shader = model.shader_pool[mesh_infos.gltfFlags];
        glUseProgram(shader.handle);

        glBindVertexArray(mesh_infos.VAO);

        // Position is mandatory attribute
        setupAttribute(mesh_infos.PositionBO, model.gltf, positionAccessorId, 0);
        glEnableVertexArrayAttrib(mesh_infos.VAO, 0);

        if (mesh_infos.gltfFlags & gltfFlags::HasNormals) {
            setupAttribute(mesh_infos.NormalBO, model.gltf, normalAccessorId, 1);
            glEnableVertexArrayAttrib(mesh_infos.VAO, 1);
        }

        if (mesh_infos.gltfFlags & gltfFlags::HasTexCoords) {
            setupAttribute(mesh_infos.TexCoordsBO, model.gltf, texcoordAccessorId, 2);
            glEnableVertexArrayAttrib(mesh_infos.VAO, 2);

            if (!default_material_infos_initialized) {
                unsigned char data[] = {255, 255, 255, 255};
                createTexture(default_material_infos.baseColorGLTexture, 1, 1, GL_UNSIGNED_BYTE,
                              data, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST,
                              false);
                createTexture(default_material_infos.metallicRoughnessGLTexture, 1, 1,
                              GL_UNSIGNED_BYTE, data, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE,
                              GL_NEAREST, GL_NEAREST, false);

                default_material_infos_initialized = true;
            }

            materialInfos material_infos = model.material_infos[materialIndex];
            tinygltf::Material material = model.gltf.materials[materialIndex];
            int baseColorTextureId = material.pbrMetallicRoughness.baseColorTexture.index;
            if (baseColorTextureId == -1) {
                material_infos.baseColorGLTexture = default_material_infos.baseColorGLTexture;
            } else {
                setupTexture(material_infos.baseColorGLTexture, model.gltf, baseColorTextureId);
            }

            int metallicRoughnessTextureId =
                material.pbrMetallicRoughness.metallicRoughnessTexture.index;
            if (metallicRoughnessTextureId == -1) {
                material_infos.metallicRoughnessGLTexture =
                    default_material_infos.metallicRoughnessGLTexture;
            } else {
                setupTexture(material_infos.metallicRoughnessGLTexture, model.gltf,
                             metallicRoughnessTextureId);
            }
        }

        // is indexed geometry
        const tinygltf::BufferView &indicesBufferView =
            model.gltf.bufferViews[indicesAccessor.bufferView];
        auto indexBuffer = reinterpret_cast<const unsigned short *>(
            model.gltf.buffers[indicesBufferView.buffer].data.data() + indicesAccessor.byteOffset +
            indicesBufferView.byteOffset);

        glBindBuffer(indicesBufferView.target, mesh_infos.EBO);
        glBufferData(indicesBufferView.target,
                     indicesAccessor.count * getComponentCount(indicesAccessor.type) *
                         getComponentByteSize(indicesAccessor.componentType),
                     indexBuffer, GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
    fprintf(hook_log, "Model %s setup Done\n", model.filename.c_str());
    fflush(hook_log);
}
