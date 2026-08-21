#include "renderer/project_triangles.h"

namespace {

Eigen::Vector2f project(const Eigen::Vector3f& pos, float focal_length,
                        float width, float height) {
    return {(pos.x() * focal_length / pos.z()) + width / 2.0f,
            (pos.y() * focal_length / pos.z()) + height / 2.0f};
}

}  // namespace

std::array<Varying, 3> projectTriangle(
    const std::array<Varying, 3>& triangle, float focal_length,
    float width, float height) {
    std::array<Varying, 3> result;

    for (int i = 0; i < 3; i++) {
        Eigen::Vector3f cam_pos = triangle[i].position.head<3>();
        Eigen::Vector2f screen =
            project(cam_pos, focal_length, width, height);
        float inv_z = 1.0f / cam_pos.z();

        result[i].position = {screen.x(), screen.y(), inv_z, inv_z};
        result[i].color = triangle[i].color;
    }

    return result;
}
