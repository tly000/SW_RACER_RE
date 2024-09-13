#pragma once

#include "renderer_utils.h"

extern "C" {
#include <Swr/swrModel.h>
}

bool try_replace(MODELID model_id, const rdMatrix44 &proj_matrix, const rdMatrix44 &view_matrix,
                 const rdMatrix44 &model_matrix);
