#pragma once

#include "forms/mesh.h"
#include "display/frame_buffer.h"
#include <Eigen/Dense>

template<typename PositionType>
struct Triangle {
    Vertex<PositionType> vertex_A, vertex_B, vertex_C;
};

using Triangle2 = Triangle<Eigen::Vector2f>;
using Triangle3 = Triangle<Eigen::Vector3f>;

/**
 * @brief Rasterizes a screen-space triangle into the framebuffer using
 *        barycentric coordinates for per-vertex colour interpolation.
 *
 * @param frame_buffer  The pixel buffer to write into.
 * @param triangle      A screen-space triangle with 2D vertex positions and colours.
 */
void drawTriangle(FrameBuffer& frame_buffer, const Triangle2& triangle);

/**
 * @brief Computes the signed area of a triangle defined by three 2D points.
 *
 * The result is positive when A→B→C is counter-clockwise, negative when
 * clockwise, and zero when the points are collinear. Used as an edge function
 * for barycentric weight computation during rasterization.
 *
 * @param A  First vertex.
 * @param B  Second vertex.
 * @param C  Third vertex.
 * @return   Signed area (half the cross product magnitude).
 */
float signedTriangleArea(const Eigen::Vector2f& A, const Eigen::Vector2f& B, const Eigen::Vector2f& C);
