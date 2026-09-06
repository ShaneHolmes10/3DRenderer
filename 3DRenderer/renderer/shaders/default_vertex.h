#pragma once

#include <Eigen/Dense>

#include "renderer/shaders/default_uniform.h"
#include "renderer/shaders/default_varying.h"
#include "renderer/types.h"

/**
 * @brief Passes camera-space position and vertex color through
 * unchanged.
 *
 * The camera already applies the view and model transforms before
 * calling the vertex shader, so the incoming position is in camera
 * space. This shader promotes it to a homogeneous Vec4 and casts the
 * integer color to float for interpolation.
 */
inline VertexShader<DefaultUniform, DefaultVarying>
    default_vertex_shader =
        [](const DefaultUniform&, const VertexAttributes& v) {
            DefaultVarying out;
            out.position = Eigen::Vector4f(
                v.position.x(), v.position.y(), v.position.z(), 1.0f);
            out.color = v.color.cast<float>();
            return out;
        };
