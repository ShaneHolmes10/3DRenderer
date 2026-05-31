
#include "project_triangles.h"

namespace {

static Eigen::Vector2f project(const Eigen::Vector3f& pos, float focal_length, float width, float height) {
    return Eigen::Vector2f(
        (pos.x() * focal_length / pos.z()) + width  / 2.0f,
        (pos.y() * focal_length / pos.z()) + height / 2.0f
    );
}

} // namespace

Triangle2 projectTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height)
{
    Triangle2 tri;
    tri.vertex_A.position = project(triangle.vertex_A.position, focal_length, width, height);
    tri.vertex_A.color    = triangle.vertex_A.color;
    tri.vertex_B.position = project(triangle.vertex_B.position, focal_length, width, height);
    tri.vertex_B.color    = triangle.vertex_B.color;
    tri.vertex_C.position = project(triangle.vertex_C.position, focal_length, width, height);
    tri.vertex_C.color    = triangle.vertex_C.color;
    return tri;
}
