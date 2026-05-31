
#include "clip_triangles.h"

namespace {

struct Plane {
    Eigen::Vector3f normal;
    float d;
};

static Vertex3 interpolate(const Vertex3& a, const Vertex3& b, float t) {
    Vertex3 result;
    result.position = a.position + t * (b.position - a.position);
    result.color    = (a.color.cast<float>() + t * (b.color - a.color).cast<float>()).cast<int>();
    return result;
}

static std::vector<Vertex3> clipAgainstPlane(const std::vector<Vertex3>& polygon, const Plane& plane) {
    std::vector<Vertex3> output;

    for (size_t i = 0; i < polygon.size(); i++) {
        const Vertex3& current = polygon[i];
        const Vertex3& next    = polygon[(i + 1) % polygon.size()];

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

} // namespace

std::vector<Triangle3> clipTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height,
    float near_z)
{
    std::vector<Vertex3> polygon = {
        triangle.vertex_A,
        triangle.vertex_B,
        triangle.vertex_C
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

    // Fan triangulate — produces n-2 triangles for an n-vertex polygon
    std::vector<Triangle3> result;
    for (size_t i = 1; i + 1 < polygon.size(); i++) {
        Triangle3 tri;
        tri.vertex_A = polygon[0];
        tri.vertex_B = polygon[i];
        tri.vertex_C = polygon[i + 1];
        result.push_back(tri);
    }

    return result;
}

