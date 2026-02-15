
#include "draw_triangles.h"
#include <algorithm>

float signedTriangleArea(const Eigen::Vector2f& A, const Eigen::Vector2f& B, const Eigen::Vector2f& C) {

    return ((B[0] - A[0]) * (C[1] - A[1]) - (B[1] - A[1]) * (C[0] - A[0]));
}

void drawTriangle(FrameBuffer& frame_buffer, const Triangle2& triangle) {

    // First get the bounding box of the triangle
    Eigen::Vector2f A = triangle.vertex_A;
    Eigen::Vector2f B = triangle.vertex_B;
    Eigen::Vector2f C = triangle.vertex_C;

    Eigen::Vector3i color_A = triangle.color_A;
    Eigen::Vector3i color_B = triangle.color_B;
    Eigen::Vector3i color_C = triangle.color_C;

    float left_side = std::min({A[0], B[0], C[0]});
    float right_side = std::max({A[0], B[0], C[0]});
    float bottom_side = std::min({A[1], B[1], C[1]});
    float top_side = std::max({A[1], B[1], C[1]});

    float ABC_edge_area = signedTriangleArea(A, B, C);

    // Scan through all the pixels in the bounding box
    for(int x_pixel_ind = left_side; x_pixel_ind < right_side; x_pixel_ind++) {
        for(int y_pixel_ind = bottom_side; y_pixel_ind < top_side; y_pixel_ind++) {

            float AB_edge_area = signedTriangleArea(A, B, {(float)x_pixel_ind, (float)y_pixel_ind});
            float CA_edge_area = signedTriangleArea(C, A, {(float)x_pixel_ind, (float)y_pixel_ind});
            float BC_edge_area = signedTriangleArea(B, C, {(float)x_pixel_ind, (float)y_pixel_ind});

            float weight_A = (BC_edge_area / ABC_edge_area);
            float weight_B = (CA_edge_area / ABC_edge_area);
            float weight_C = (AB_edge_area / ABC_edge_area);

            // Determine if the pixel we're looking at is inside the triangle
            if(AB_edge_area >= 0 &&
               CA_edge_area >= 0 &&
               BC_edge_area >= 0) {

                int pixel_r = (int)(color_A[0]*weight_A + color_B[0]*weight_B + color_C[0]*weight_C); 
                int pixel_g = (int)(color_A[1]*weight_A + color_B[1]*weight_B + color_C[1]*weight_C); 
                int pixel_b = (int)(color_A[2]*weight_A + color_B[2]*weight_B + color_C[2]*weight_C); 
            
                frame_buffer.setPixel(x_pixel_ind, y_pixel_ind, pixel_r, pixel_g, pixel_b);
            }
        }
    }

}
