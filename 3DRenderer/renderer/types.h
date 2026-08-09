#pragma once

#include <Eigen/Dense>
#include <functional>

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"

/**
 * @brief Per-vertex data passed into the rasterizer and interpolated
 * per-fragment before the shader is called.
 *
 * position packs four values whose meaning is fixed after projection:
 *   x, y  = screen-space pixel coordinates
 *   z     = normalized depth, used for the depth-buffer test
 *   w     = reciprocal of clip-space w (1/w_clip), kept so that color,
 *           UVs, and any other varying fields can be
 *           perspective-correctly interpolated across the triangle instead of
 *           linearly in 2D
 */
struct Varying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector3i color    = Eigen::Vector3i::Zero();
};

/**
 * @brief Non-owning bundle of the buffers a rasterizer draw call
 * writes into.
 */
struct Buffers {
    FrameBuffer& frame;
    DepthBuffer& depth;
};

/**
 * @brief Per-vertex input to the vertex shader.
 */
struct VertexAttributes {
    Eigen::Vector3f position = Eigen::Vector3f::Zero();
    Eigen::Vector3i color    = Eigen::Vector3i::Zero();
};

/**
 * @brief Transforms a vertex's attributes into a Varying for the rest
 * of the pipeline.
 */
template <typename TUniform>
using VertexShader =
    std::function<Varying(const TUniform&, const VertexAttributes&)>;

/**
 * @brief Computes a fragment's color from uniform and interpolated
 * Varying data.
 */
template <typename TUniform>
using FragmentShader =
    std::function<Eigen::Vector3i(const TUniform&, const Varying&)>;

/**
 * @brief Specifies which triangle faces to skip during rasterization.
 *
 * Backface culling is determined by the winding order of the triangle's
 * projected vertices in screen space.
 */
enum class CullMode { None, Clockwise, CounterClockwise };

/**
 * @brief Rendering settings for a single draw call.
 */
struct Options {
    CullMode cull_mode = CullMode::None;
};

/**
 * @brief Pairs a vertex/fragment shader with the caller-defined uniform
 * data they read.
 */
template <typename TUniform>
struct Program {
    VertexShader<TUniform>   vertex_shader;
    FragmentShader<TUniform> fragment_shader;
    TUniform                 uniform;
};
