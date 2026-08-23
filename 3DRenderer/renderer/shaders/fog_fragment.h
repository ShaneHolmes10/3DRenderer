#pragma once

#include <Eigen/Dense>
#include <algorithm>

#include "renderer/shaders/default_uniform.h"
#include "renderer/shaders/default_varying.h"
#include "renderer/types.h"

/**
 * @brief Blends the interpolated vertex color toward a fog color based
 * on camera-space depth.
 *
 * position.w() holds 1/z after projection, so it is large for close
 * fragments and small for distant ones. Multiplying by fog_density gives
 * a clarity factor in [0, 1]: 1 = fully clear, 0 = fully fogged.
 *
 * Tune fog_density to match your scene scale. Larger values push the fog
 * further away; smaller values bring it closer.
 */
inline FragmentShader<DefaultUniform, DefaultVarying> fog_fragment_shader =
    [](const DefaultUniform&, const DefaultVarying& v) -> Eigen::Vector3i {
    const float fog_density = 80.0f;
    const Eigen::Vector3f fog_color(200.0f, 200.0f, 220.0f);

    float clarity = std::min(1.0f, v.position.w() * fog_density);
    Eigen::Vector3f out = v.color * clarity + fog_color * (1.0f - clarity);
    return out.cast<int>();
};
