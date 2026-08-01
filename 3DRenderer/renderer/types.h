#pragma once

#include <Eigen/Dense>
#include <functional>

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"
#include "forms/types.h"

/**
 * @brief Data that is constant across every fragment of a draw call.
 */
struct Uniform {
    struct {
        Texture* texture = nullptr;
    } material;
};

/**
 * @brief Per-vertex data passed into the rasterizer and interpolated
 * per-fragment before the shader is called.
 *
 * position packs four values whose meaning is fixed after projection:
 *   x, y  = screen-space pixel coordinates
 *   z     = normalized depth, used for the depth-buffer test
 *   w     = reciprocal of clip-space w (1/w_clip), kept so that color,
 *           UVs, and any other varying fields can be
 * perspective-correctly interpolated across the triangle instead of
 * linearly in 2D
 */
struct Varying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector3i color = Eigen::Vector3i::Zero();
};

/**
 * @brief Per-vertex input to the vertex shader.
 */
struct Vertex {
    Eigen::Vector3f position = Eigen::Vector3f::Zero();
    Eigen::Vector3i color = Eigen::Vector3i::Zero();
};

/**
 * @brief Computes a vertex's Varying from Uniform and Vertex data.
 */
using VertexShader =
    std::function<Varying(const Uniform&, const Vertex&)>;

/**
 * @brief Computes a fragment's color from Uniform and Varying data.
 */
using FragmentShader =
    std::function<Eigen::Vector3i(const Uniform&, const Varying&)>;

/**
 * @brief Non-owning bundle of the buffers a rasterizer draw call
 * writes into.
 */
struct Buffers {
    FrameBuffer& frame;
    DepthBuffer& depth;
};
