#pragma once

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"
#include "geometry_types.h"

/**
 * @brief Rasterizes a screen-space triangle into the framebuffer using
 *        barycentric coordinates for per-vertex colour interpolation.
 *
 * Performs a depth test using the interpolated inverse-z value at each
 * pixel. Only fragments closer than what is already in the depth buffer
 * are written.
 *
 * @param frame_buffer  The pixel buffer to write into.
 * @param depth_buffer  The depth buffer to test and update.
 * @param triangle      A screen-space triangle with 2D vertex
 * positions, colours, and inverse-z values.
 */
void drawTriangleToScreen(FrameBuffer& frame_buffer,
                          DepthBuffer& depth_buffer,
                          const Triangle2& triangle);

/**
 * @brief Computes the signed area of a triangle defined by three 2D
 * points.
 *
 * The result is positive when A→B→C is counter-clockwise, negative when
 * clockwise, and zero when the points are collinear. Used as an edge
 * function for barycentric weight computation during rasterization.
 *
 * @param A  First vertex.
 * @param B  Second vertex.
 * @param C  Third vertex.
 * @return   Signed area (half the cross product magnitude).
 */
float signedTriangleArea(const Eigen::Vector2f& A,
                         const Eigen::Vector2f& B,
                         const Eigen::Vector2f& C);
