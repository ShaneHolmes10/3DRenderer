#pragma once

#include <array>

#include <Eigen/Dense>

inline Eigen::Vector2f project(const Eigen::Vector3f& pos, float focal_length,
                               float width, float height) {
    return {(pos.x() * focal_length / pos.z()) + width / 2.0f,
            (pos.y() * focal_length / pos.z()) + height / 2.0f};
}

/**
 * @brief Projects a camera-space triangle to screen space using perspective
 * division. Copies all TVarying fields from the input, then overwrites
 * position with screen-space coordinates and 1/z for depth testing.
 *
 * @param triangle      A camera-space triangle as three TVaryings with z > 0.
 * @param focal_length  Camera focal length.
 * @param width         Framebuffer width in pixels.
 * @param height        Framebuffer height in pixels.
 * @return              The projected screen-space triangle as three TVaryings.
 */
template <typename TVarying>
std::array<TVarying, 3> project_triangle(const std::array<TVarying, 3>& triangle,
                                        float focal_length, float width,
                                        float height) {
    std::array<TVarying, 3> result = triangle;

    for (int i = 0; i < 3; i++) {
        Eigen::Vector3f cam_pos = triangle[i].position.template head<3>();
        Eigen::Vector2f screen  = project(cam_pos, focal_length, width, height);
        float inv_z             = 1.0f / cam_pos.z();
        result[i].position      = Eigen::Vector4f(screen.x(), screen.y(), inv_z, inv_z);
    }

    return result;
}
