
#include "draw_triangles_to_screen.h"

#include <algorithm>

#include "display/depth_buffer.h"

float signedTriangleArea(const Eigen::Vector2f& A,
                         const Eigen::Vector2f& B,
                         const Eigen::Vector2f& C) {
    return ((B[0] - A[0]) * (C[1] - A[1]) -
            (B[1] - A[1]) * (C[0] - A[0]));
}

void drawTriangleToScreen(FrameBuffer& frame_buffer,
                          DepthBuffer& depth_buffer,
                          const Triangle2& triangle) {
    // First get the bounding box of the triangle
    Eigen::Vector2f A = triangle.vertex_A.position;
    Eigen::Vector2f B = triangle.vertex_B.position;
    Eigen::Vector2f C = triangle.vertex_C.position;

    Eigen::Vector3i color_A = triangle.vertex_A.color;
    Eigen::Vector3i color_B = triangle.vertex_B.color;
    Eigen::Vector3i color_C = triangle.vertex_C.color;

    float left_side = std::min({A[0], B[0], C[0]});
    float right_side = std::max({A[0], B[0], C[0]});
    float bottom_side = std::min({A[1], B[1], C[1]});
    float top_side = std::max({A[1], B[1], C[1]});

    // Clamp bounding box to framebuffer dimensions to handle off-screen
    // geometry
    int x_start = std::max((int)left_side, 0);
    int x_end =
        std::min((int)std::ceil(right_side), (int)frame_buffer.width);
    int y_start = std::max((int)bottom_side, 0);
    int y_end =
        std::min((int)std::ceil(top_side), (int)frame_buffer.height);

    float ABC_edge_area = signedTriangleArea(A, B, C);

    // Scan through all the pixels in the bounding box
    for (int x_pixel_ind = x_start; x_pixel_ind < x_end;
         x_pixel_ind++) {
        for (int y_pixel_ind = y_start; y_pixel_ind < y_end;
             y_pixel_ind++) {
            float AB_edge_area = signedTriangleArea(
                A, B, {(float)x_pixel_ind, (float)y_pixel_ind});
            float CA_edge_area = signedTriangleArea(
                C, A, {(float)x_pixel_ind, (float)y_pixel_ind});
            float BC_edge_area = signedTriangleArea(
                B, C, {(float)x_pixel_ind, (float)y_pixel_ind});

            float weight_A = (BC_edge_area / ABC_edge_area);
            float weight_B = (CA_edge_area / ABC_edge_area);
            float weight_C = (AB_edge_area / ABC_edge_area);

            // Determine if the pixel we're looking at is inside the
            // triangle
            if (AB_edge_area >= 0 && CA_edge_area >= 0 &&
                BC_edge_area >= 0) {
                // Depth test: interpolate inverse-z and reject
                // fragments behind what's already drawn
                float pixel_inv_depth =
                    weight_A * triangle.vertex_a_inverse_z +
                    weight_B * triangle.vertex_b_inverse_z +
                    weight_C * triangle.vertex_c_inverse_z;

                size_t depth_idx =
                    y_pixel_ind * depth_buffer.width + x_pixel_ind;

                if (pixel_inv_depth <= depth_buffer.values[depth_idx])
                    continue;

                depth_buffer.values[depth_idx] = pixel_inv_depth;

                int pixel_r = (int)(color_A[0] * weight_A +
                                    color_B[0] * weight_B +
                                    color_C[0] * weight_C);
                int pixel_g = (int)(color_A[1] * weight_A +
                                    color_B[1] * weight_B +
                                    color_C[1] * weight_C);
                int pixel_b = (int)(color_A[2] * weight_A +
                                    color_B[2] * weight_B +
                                    color_C[2] * weight_C);

                frame_buffer.setPixel(x_pixel_ind, y_pixel_ind, pixel_r,
                                      pixel_g, pixel_b);
            }
        }
    }
}
