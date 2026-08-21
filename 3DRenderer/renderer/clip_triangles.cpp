#include "renderer/clip_triangles.h"

namespace {

struct Plane {
    Eigen::Vector3f normal;
    float d;
};

Varying interpolate(const Varying& a, const Varying& b, float t) {
    Varying result;
    result.position = a.position + t * (b.position - a.position);
    result.color =
        (a.color.cast<float>() + t * (b.color - a.color).cast<float>())
            .cast<int>();
    return result;
}

std::vector<Varying> clipAgainstPlane(const std::vector<Varying>& polygon,
                                      const Plane& plane) {
    std::vector<Varying> output;

    for (size_t i = 0; i < polygon.size(); i++) {
        const Varying& current = polygon[i];
        const Varying& next    = polygon[(i + 1) % polygon.size()];

        float d_current = plane.normal.dot(current.position.head<3>()) + plane.d;
        float d_next    = plane.normal.dot(next.position.head<3>()) + plane.d;

        if (d_next >= 0.0f) {
            if (d_current < 0.0f) {
                output.push_back(
                    interpolate(current, next, d_current / (d_current - d_next)));
            }
            output.push_back(next);
        } else {
            if (d_current >= 0.0f) {
                output.push_back(
                    interpolate(current, next, d_current / (d_current - d_next)));
            }
        }
    }

    return output;
}

}  // namespace

std::vector<std::array<Varying, 3>> clipTriangle(
    const std::array<Varying, 3>& triangle,
    float focal_length, float width, float height, float near_z) {

    std::vector<Varying> polygon = {triangle[0], triangle[1], triangle[2]};

    // Frustum planes in camera space — inside when
    // plane.normal.dot(position.xyz) + d >= 0
    // NOLINTNEXTLINE(modernize-avoid-c-arrays)
    const Plane planes[] = {
        {{0.0f, 0.0f, 1.0f}, -near_z},                 // near
        {{focal_length, 0.0f, width / 2.0f}, 0.0f},    // left
        {{-focal_length, 0.0f, width / 2.0f}, 0.0f},   // right
        {{0.0f, focal_length, height / 2.0f}, 0.0f},   // bottom
        {{0.0f, -focal_length, height / 2.0f}, 0.0f},  // top
    };

    for (const auto& plane : planes) {
        polygon = clipAgainstPlane(polygon, plane);
        if (polygon.empty()) {
            return {};
        }
    }

    // Fan triangulate — produces n-2 triangles for an n-vertex polygon
    std::vector<std::array<Varying, 3>> result;
    for (size_t i = 1; i + 1 < polygon.size(); i++) {
        result.push_back({polygon[0], polygon[i], polygon[i + 1]});
    }

    return result;
}
