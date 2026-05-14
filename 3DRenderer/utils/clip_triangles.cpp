
#include "clip_triangles.h"
#include "forms/mesh.h"

namespace {

struct Plane {
    Eigen::Vector3f normal;
    float d;
};

static Vertex interpolate(const Vertex& a, const Vertex& b, float t) {
    Vertex result;
    result.position = a.position + t * (b.position - a.position);
    result.color    = (a.color.cast<float>() + t * (b.color - a.color).cast<float>()).cast<int>();
    return result;
}

static std::vector<Vertex> clipAgainstPlane(const std::vector<Vertex>& polygon, const Plane& plane) {
    std::vector<Vertex> output;

    for (size_t i = 0; i < polygon.size(); i++) {
        const Vertex& current = polygon[i];
        const Vertex& next    = polygon[(i + 1) % polygon.size()];

        float d_current = plane.normal.dot(current.position) + plane.d;
        float d_next    = plane.normal.dot(next.position)    + plane.d;

        if (d_next >= 0.0f) {
            if (d_current < 0.0f)
                output.push_back(interpolate(current, next, d_current / (d_current - d_next)));
            output.push_back(next);
        } else {
            if (d_current >= 0.0f)
                output.push_back(interpolate(current, next, d_current / (d_current - d_next)));
        }
    }

    return output;
}

static Eigen::Vector2f project(const Eigen::Vector3f& pos, float focal_length, float width, float height) {
    return Eigen::Vector2f(
        (pos.x() * focal_length / pos.z()) + width  / 2.0f,
        (pos.y() * focal_length / pos.z()) + height / 2.0f
    );
}

} // namespace

std::vector<Triangle2> clipAndProjectTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height,
    float near_z)
{
    std::vector<Vertex> polygon = {
        {triangle.vertex_A, triangle.color_A},
        {triangle.vertex_B, triangle.color_B},
        {triangle.vertex_C, triangle.color_C}
    };

    // Frustum planes in camera space — inside when plane.normal.dot(position) + d >= 0
    const Plane planes[] = {
        {{ 0.0f,           0.0f,          1.0f         }, -near_z },  // near
        {{ focal_length,   0.0f,          width  / 2.0f},  0.0f  },  // left
        {{-focal_length,   0.0f,          width  / 2.0f},  0.0f  },  // right
        {{ 0.0f,           focal_length,  height / 2.0f},  0.0f  },  // bottom
        {{ 0.0f,          -focal_length,  height / 2.0f},  0.0f  },  // top
    };

    for (const auto& plane : planes) {
        polygon = clipAgainstPlane(polygon, plane);
        if (polygon.empty()) return {};
    }

    // Fan triangulate and project to screen space
    std::vector<Triangle2> result;
    Eigen::Vector2f pos0 = project(polygon[0].position, focal_length, width, height);

    for (size_t i = 1; i + 1 < polygon.size(); i++) {
        Triangle2 tri;
        tri.vertex_A = pos0;
        tri.color_A  = polygon[0].color;
        tri.vertex_B = project(polygon[i].position,     focal_length, width, height);
        tri.color_B  = polygon[i].color;
        tri.vertex_C = project(polygon[i + 1].position, focal_length, width, height);
        tri.color_C  = polygon[i + 1].color;
        result.push_back(tri);
    }

    return result;
}
