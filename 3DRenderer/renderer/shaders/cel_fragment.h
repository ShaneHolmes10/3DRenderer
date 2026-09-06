#pragma once

#include <Eigen/Dense>
#include <cmath>

#include "renderer/shaders/default_uniform.h"
#include "renderer/shaders/default_varying.h"
#include "renderer/types.h"

/**
 * @brief Quantizes the interpolated color into discrete flat bands,
 * producing a cartoon/cel-shading look.
 *
 * Tune levels to control how many distinct shades appear per channel.
 * Lower = more dramatic posterization, higher = closer to smooth color.
 */
inline FragmentShader<DefaultUniform, DefaultVarying>
    cel_fragment_shader =
        [](const DefaultUniform&,
           const DefaultVarying& v) -> Eigen::Vector3i {
    const float levels = 4.0f;
    Eigen::Vector3f normalized = v.color / 255.0f;
    Eigen::Vector3f quantized =
        (normalized * levels).array().floor() / levels * 255.0f;
    return quantized.cast<int>();
};
