#pragma once

#include <Eigen/Dense>
#include <functional>
#include <tuple>

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"

/**
 * @brief Registers the fields of a user-defined Varying struct for automatic
 * per-fragment barycentric interpolation by the rasterizer.
 *
 * Must include at minimum the position field. Example:
 *   struct MyVarying {
 *       Eigen::Vector4f position;
 *       Eigen::Vector3i color;
 *       VARYING(position, color)
 *   };
 */
#define VARYING(...)                                  \
    auto _reflect() { return std::tie(__VA_ARGS__); } \
    auto _reflect() const { return std::tie(__VA_ARGS__); }

// Checks whether type T has a .position member.
// Fallback specialization — evaluates to false for any T by default.
template <typename T, typename = void>
struct has_position : std::false_type {};
// Winning specialization — chosen when T().position compiles. If it doesn't,
// SFINAE discards this silently and the fallback above is used instead.
template <typename T>
struct has_position<T, std::void_t<decltype(std::declval<T>().position)>>
    : std::true_type {};

// Checks whether type T has a ._reflect() method (i.e. used the VARYING macro).
// Same two-specialization SFINAE pattern as has_position above.
template <typename T, typename = void>
struct has_reflect : std::false_type {};
template <typename T>
struct has_reflect<T, std::void_t<decltype(std::declval<T>()._reflect())>>
    : std::true_type {};


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
 * @brief Specifies which triangle faces to skip during rasterization.
 */
enum class CullMode { None, Clockwise, CounterClockwise };

/**
 * @brief Rendering settings for a single draw call.
 */
struct Options {
    CullMode cull_mode = CullMode::None;
};

/**
 * @brief Transforms a vertex's attributes into a user-defined Varying.
 */
template <typename TUniform, typename TVarying>
using VertexShader =
    std::function<TVarying(const TUniform&, const VertexAttributes&)>;

/**
 * @brief Computes a fragment's color from uniform and interpolated Varying.
 */
template <typename TUniform, typename TVarying>
using FragmentShader =
    std::function<Eigen::Vector3i(const TUniform&, const TVarying&)>;

/**
 * @brief Pairs vertex/fragment shaders with caller-defined uniform and Varying
 * types. TVarying must have a Vec4 position field and define VARYING(...).
 */
template <typename TUniform, typename TVarying>
struct Program {
    static_assert(has_position<TVarying>::value,
                  "Output of Vertex Stage needs Vec4 position!");
    static_assert(has_reflect<TVarying>::value,
                  "Output of Vertex Stage needs interpolated fields. "
                  "Did you forget the VARYING(...) macro?");

    VertexShader<TUniform, TVarying> vertex_shader;
    FragmentShader<TUniform, TVarying> fragment_shader;
    TUniform uniform;
};
