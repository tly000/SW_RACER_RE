#include "meshes.h"

int cube_model_id = 1000;
float cube_verts[24] = {
    -100, -100, -100,//0
    +100, -100, -100,//1
    +100, +100, -100,//2
    -100, +100, -100,//3
    -100, -100, +100,//4
    +100, -100, +100,//5
    +100, +100, +100,//6
    -100, +100, +100 //7
};

unsigned short cube_indices[36] = {
    0, 1, 3, 3, 1, 2,//
    1, 5, 2, 2, 5, 6,//
    5, 4, 6, 6, 4, 7,//
    4, 0, 7, 7, 0, 3,//
    3, 2, 7, 7, 2, 6,//
    4, 5, 0, 0, 5, 1 //
};

int tetrahedron_model_id = 1001;
float tetrahedron_verts[12] = {
    +100.0, +100.0, +100.0,//0
    -100.0, -100.0, +100.0,//1
    -100.0, +100.0, -100.0,//2
    +100.0, -100.0, -100.0 //3
};

// GL_TRIANGLE_STRIP
unsigned short tetrahedron_indices[6] = {0, 1, 2, 3, 0, 1};

int gltf_model_id = 1002;
