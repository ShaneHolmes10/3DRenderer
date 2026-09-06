#pragma once

#include <Eigen/Dense>

#include "renderer/shaders/default_uniform.h"
#include "renderer/shaders/default_varying.h"
#include "renderer/types.h"

/**
 * @brief Returns the interpolated vertex color as the fragment color.
 */
inline FragmentShader<DefaultUniform, DefaultVarying>
    color_fragment_shader =
        [](const DefaultUniform&,
           const DefaultVarying& v) -> Eigen::Vector3i {
    return v.color.cast<int>();
};
