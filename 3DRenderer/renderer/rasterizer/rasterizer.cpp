#include "renderer/rasterizer/rasterizer.h"

#include <algorithm>
#include <cmath>

namespace {

float signedArea(const Eigen::Vector2f& A, const Eigen::Vector2f& B,
                 const Eigen::Vector2f& C) {
    return (B.x() - A.x()) * (C.y() - A.y()) -
           (B.y() - A.y()) * (C.x() - A.x());
}

}  // namespace

void rasterize(const RasterTriangle& triangle, const Uniform& uniform,
               const FragmentShader& shader, Buffers& buffers) {
    Eigen::Vector2f A = triangle.v0.position.head<2>();
    Eigen::Vector2f B = triangle.v1.position.head<2>();
    Eigen::Vector2f C = triangle.v2.position.head<2>();

    float left_side = std::min({A.x(), B.x(), C.x()});
    float right_side = std::max({A.x(), B.x(), C.x()});
    float bottom_side = std::min({A.y(), B.y(), C.y()});
    float top_side = std::max({A.y(), B.y(), C.y()});

    // Clamp bounding box to framebuffer dimensions to handle off-screen
    // geometry
    int x_start = std::max(static_cast<int>(left_side), 0);
    int x_end = std::min(static_cast<int>(std::ceil(right_side)),
                         static_cast<int>(buffers.frame.width));
    int y_start = std::max(static_cast<int>(bottom_side), 0);
    int y_end = std::min(static_cast<int>(std::ceil(top_side)),
                         static_cast<int>(buffers.frame.height));

    float ABC_edge_area = signedArea(A, B, C);

    for (int x_pixel_ind = x_start; x_pixel_ind < x_end;
         x_pixel_ind++) {
        for (int y_pixel_ind = y_start; y_pixel_ind < y_end;
             y_pixel_ind++) {
            Eigen::Vector2f pixel(static_cast<float>(x_pixel_ind),
                                  static_cast<float>(y_pixel_ind));

            float AB_edge_area = signedArea(A, B, pixel);
            float CA_edge_area = signedArea(C, A, pixel);
            float BC_edge_area = signedArea(B, C, pixel);

            if (AB_edge_area < 0 || CA_edge_area < 0 ||
                BC_edge_area < 0) {
                continue;
            }

            float weight_A = BC_edge_area / ABC_edge_area;
            float weight_B = CA_edge_area / ABC_edge_area;
            float weight_C = AB_edge_area / ABC_edge_area;

            // Interpolate depth and reject fragments behind what's
            // already drawn
            float pixel_inv_depth =
                weight_A * triangle.v0.position.w() +
                weight_B * triangle.v1.position.w() +
                weight_C * triangle.v2.position.w();

            size_t depth_idx =
                static_cast<size_t>(y_pixel_ind) * buffers.depth.width +
                static_cast<size_t>(x_pixel_ind);

            if (pixel_inv_depth <= buffers.depth.values[depth_idx]) {
                continue;
            }
            buffers.depth.values[depth_idx] = pixel_inv_depth;

            // Interpolate all vertex Varyings to produce the
            // per-fragment Varying
            Varying varying;
            varying.position = {
                pixel.x(), pixel.y(),
                weight_A * triangle.v0.position.z() +
                    weight_B * triangle.v1.position.z() +
                    weight_C * triangle.v2.position.z(),
                pixel_inv_depth};
            varying.color =
                (weight_A * triangle.v0.color.cast<float>() +
                 weight_B * triangle.v1.color.cast<float>() +
                 weight_C * triangle.v2.color.cast<float>())
                    .cast<int>();

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
