#pragma once

#include <algorithm>
#include <array>
#include <cmath>

#include "renderer/types.h"

/**
 * @brief Rasterizes a screen-space triangle into the framebuffer using
 *        a caller-supplied fragment shader.
 *
 * Scans the triangle's bounding box and, for every pixel inside the
 * triangle that passes the depth test, interpolates a Varying from
 * the three vertex Varyings via barycentric weights and calls
 * shader(uniform, varying) to determine the fragment's color. Knows
 * nothing about meshes, entities, or the pipeline that produced this
 * triangle.
 *
 * @param triangle  Three per-vertex Varyings in screen space.
 * @param uniform   Data constant across every fragment of this
 * triangle.
 * @param shader    Computes a fragment's color from uniform and varying
 * data.
 * @param buffers   The frame and depth buffers to test and write into.
 */
template <typename TUniform>
void rasterize(const std::array<Varying, 3>& triangle,
               const TUniform& uniform,
               const FragmentShader<TUniform>& shader,
               Buffers& buffers) {
    // Computes the signed area of triangle ABC using the cross product.
    // Positive when vertices are counter-clockwise, negative when
    // clockwise.
    auto signedArea = [](const Eigen::Vector2f& A,
                         const Eigen::Vector2f& B,
                         const Eigen::Vector2f& C) {
        return (B.x() - A.x()) * (C.y() - A.y()) -
               (B.y() - A.y()) * (C.x() - A.x());
    };

    // Extract 2D screen-space positions from the Varying position.
    Eigen::Vector2f A = triangle[0].position.head<2>();
    Eigen::Vector2f B = triangle[1].position.head<2>();
    Eigen::Vector2f C = triangle[2].position.head<2>();

    // Compute the axis-aligned bounding box of the triangle.
    float left_side = std::min({A.x(), B.x(), C.x()});
    float right_side = std::max({A.x(), B.x(), C.x()});
    float bottom_side = std::min({A.y(), B.y(), C.y()});
    float top_side = std::max({A.y(), B.y(), C.y()});

    // Clamp bounding box to framebuffer dimensions to handle off-screen
    // geometry.
    int x_start = std::max(static_cast<int>(left_side), 0);
    int x_end = std::min(static_cast<int>(std::floor(right_side)) + 1,
                         static_cast<int>(buffers.frame.width));
    int y_start = std::max(static_cast<int>(bottom_side), 0);
    int y_end = std::min(static_cast<int>(std::floor(top_side)) + 1,
                         static_cast<int>(buffers.frame.height));

    float ABC_edge_area = signedArea(A, B, C);

    for (int x_pixel_ind = x_start; x_pixel_ind < x_end;
         x_pixel_ind++) {
        for (int y_pixel_ind = y_start; y_pixel_ind < y_end;
             y_pixel_ind++) {
            Eigen::Vector2f pixel(static_cast<float>(x_pixel_ind),
                                  static_cast<float>(y_pixel_ind));

            // Compute the signed area of each sub-triangle formed by
            // the pixel and each edge. A pixel is inside the triangle
            // when all three are non-negative (counter-clockwise
            // winding).
            float AB_edge_area = signedArea(A, B, pixel);
            float CA_edge_area = signedArea(C, A, pixel);
            float BC_edge_area = signedArea(B, C, pixel);

            if (AB_edge_area < 0 || CA_edge_area < 0 ||
                BC_edge_area < 0) {
                continue;
            }

            // Barycentric weights: each weight is the sub-triangle area
            // opposite to that vertex divided by the total triangle
            // area.
            float weight_A = BC_edge_area / ABC_edge_area;
            float weight_B = CA_edge_area / ABC_edge_area;
            float weight_C = AB_edge_area / ABC_edge_area;

            // Interpolate 1/w (stored in position.w) to get the
            // perspective- correct depth value for this pixel, then run
            // the depth test.
            float pixel_inv_depth =
                weight_A * triangle[0].position.w() +
                weight_B * triangle[1].position.w() +
                weight_C * triangle[2].position.w();

            size_t depth_idx =
                static_cast<size_t>(y_pixel_ind) * buffers.depth.width +
                static_cast<size_t>(x_pixel_ind);

            if (pixel_inv_depth <= buffers.depth.values[depth_idx]) {
                continue;
            }
            buffers.depth.values[depth_idx] = pixel_inv_depth;

            // Interpolate all Varying fields across the triangle using
            // the barycentric weights, producing the per-fragment
            // Varying.
            Varying varying;
            varying.position = {
                pixel.x(), pixel.y(),
                weight_A * triangle[0].position.z() +
                    weight_B * triangle[1].position.z() +
                    weight_C * triangle[2].position.z(),
                pixel_inv_depth};
            varying.color =
                (weight_A * triangle[0].color.cast<float>() +
                 weight_B * triangle[1].color.cast<float>() +
                 weight_C * triangle[2].color.cast<float>())
                    .cast<int>();

            // Call the fragment shader and write the result to the
            // framebuffer.
            Eigen::Vector3i fragment_color = shader(uniform, varying);

            buffers.frame.setPixel(
                static_cast<size_t>(x_pixel_ind),
                static_cast<size_t>(y_pixel_ind),
                static_cast<uint8_t>(fragment_color.x()),
                static_cast<uint8_t>(fragment_color.y()),
                static_cast<uint8_t>(fragment_color.z()));
        }
    }
}
