
#include "project_triangles.h"

namespace {

Eigen::Vector2f project(const Eigen::Vector3f& pos,
                               float focal_length, float width,
                               float height) {
    return {(pos.x() * focal_length / pos.z()) + width / 2.0f,
            (pos.y() * focal_length / pos.z()) + height / 2.0f};
}

}  // namespace

Triangle2 projectTriangle(const Triangle3& triangle, float focal_length,
                          float width, float height) {
    Triangle2 tri;
    tri.vertex_A.position = project(triangle.vertex_A.position,
                                    focal_length, width, height);
    tri.vertex_A.color = triangle.vertex_A.color;
    tri.vertex_a_inverse_z = 1.0f / triangle.vertex_A.position.z();
    tri.vertex_B.position = project(triangle.vertex_B.position,
                                    focal_length, width, height);
    tri.vertex_B.color = triangle.vertex_B.color;
    tri.vertex_b_inverse_z = 1.0f / triangle.vertex_B.position.z();
    tri.vertex_C.position = project(triangle.vertex_C.position,
                                    focal_length, width, height);
    tri.vertex_C.color = triangle.vertex_C.color;
    tri.vertex_c_inverse_z = 1.0f / triangle.vertex_C.position.z();
    return tri;
}
