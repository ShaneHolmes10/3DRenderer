#pragma once

#include <array>
#include <vector>

#include <Eigen/Dense>

#include "renderer/tuple_helper.h"

/**
 * @brief A plane in camera space defined by a normal vector and offset.
 * A point p is inside the plane when normal.dot(p) + d >= 0.
 */
struct Plane {
    Eigen::Vector3f normal;
    float d;
};

/**
 * @brief Linearly interpolates between two TVaryings by factor t.
 * All VARYING fields are blended as (1-t)*a + t*b.
 *
 * @param a  Start varying (t=0).
 * @param b  End varying (t=1).
 * @param t  Interpolation factor in [0, 1].
 * @return   The interpolated TVarying.
 */
template <typename TVarying>
TVarying lerp_varying(const TVarying& a, const TVarying& b, float t) {
    return interpolate_fragment_data(a, b, b, 1.0f - t, t, 0.0f);
}

/**
 * @brief Clips a convex polygon against a single plane using
 * Sutherland-Hodgman, returning the surviving vertices.
 *
 * @param polygon  Input polygon as an ordered list of TVaryings.
 * @param plane    The plane to clip against.
 * @return         The clipped polygon, or empty if fully outside.
 */
template <typename TVarying>
std::vector<TVarying> clip_triangle_against_plane(const std::vector<TVarying>& polygon,
                                        const Plane& plane) {
    std::vector<TVarying> output;

    for (size_t i = 0; i < polygon.size(); i++) {
        const TVarying& current = polygon[i];
        const TVarying& next    = polygon[(i + 1) % polygon.size()];

        float d_current =
            plane.normal.dot(current.position.template head<3>()) + plane.d;
        float d_next = plane.normal.dot(next.position.template head<3>()) + plane.d;

        if (d_next >= 0.0f) {
            if (d_current < 0.0f) {
                output.push_back(lerp_varying(
                    current, next, d_current / (d_current - d_next)));
            }
            output.push_back(next);
        } else {
            if (d_current >= 0.0f) {
                output.push_back(lerp_varying(
                    current, next, d_current / (d_current - d_next)));
            }
        }
    }

    return output;
}

/**
 * @brief Clips a camera-space triangle against the view frustum using
 * the Sutherland-Hodgman algorithm, then fan-triangulates the result.
 *
 * Clips against five planes: near, left, right, bottom, and top. Any
 * portion of the triangle outside the frustum is discarded. The
 * surviving polygon is fan-triangulated from its first vertex,
 * producing one TVarying triple per fan face.
 *
 * TVarying must have a position field whose xyz holds camera-space position.
 *
 * @param triangle      The camera-space triangle as three TVaryings.
 * @param focal_length  Camera focal length, used to derive lateral planes.
 * @param width         Framebuffer width in pixels.
 * @param height        Framebuffer height in pixels.
 * @param near_z        Near plane depth; vertices with z < near_z are clipped.
 * @return              Clipped camera-space triangles, or empty if fully culled.
 */
template <typename TVarying>
std::vector<std::array<TVarying, 3>> clip_triangle(
    const std::array<TVarying, 3>& triangle, float focal_length, float width,
    float height, float near_z) {
    std::vector<TVarying> polygon = {triangle[0], triangle[1], triangle[2]};

    // Frustum planes in camera space — inside when
    // plane.normal.dot(position.xyz) + d >= 0
    // NOLINTNEXTLINE(modernize-avoid-c-arrays)
    const Plane planes[] = {
        {{0.0f, 0.0f, 1.0f}, -near_z},
        {{focal_length, 0.0f, width / 2.0f}, 0.0f},
        {{-focal_length, 0.0f, width / 2.0f}, 0.0f},
        {{0.0f, focal_length, height / 2.0f}, 0.0f},
        {{0.0f, -focal_length, height / 2.0f}, 0.0f},
    };

    for (const auto& plane : planes) {
        polygon = clip_triangle_against_plane(polygon, plane);
        if (polygon.empty()) {
            return {};
        }
    }

    // Fan triangulate — produces n-2 triangles for an n-vertex polygon
    std::vector<std::array<TVarying, 3>> result;
    for (size_t i = 1; i + 1 < polygon.size(); i++) {
        result.push_back({polygon[0], polygon[i], polygon[i + 1]});
    }

    return result;
}
