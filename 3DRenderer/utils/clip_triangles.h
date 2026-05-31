#pragma once

#include "draw_triangles_to_screen.h"
#include <vector>

/**
 * @brief Clips a camera-space triangle against the view frustum using the
 *        Sutherland-Hodgman algorithm, then fan-triangulates the result.
 *
 * Clips against five planes: near, left, right, bottom, and top. Any portion
 * of the triangle outside the frustum is discarded. The surviving polygon is
 * fan-triangulated from its first vertex, producing one Triangle3 per fan face.
 *
 * @param triangle      The camera-space triangle to clip.
 * @param focal_length  Camera focal length, used to derive the lateral frustum planes.
 * @param width         Framebuffer width in pixels.
 * @param height        Framebuffer height in pixels.
 * @param near_z        Near plane depth; vertices with z < near_z are clipped.
 * @return              A list of clipped camera-space triangles, or empty if
 *                      the triangle is entirely outside the frustum.
 */
std::vector<Triangle3> clipTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height,
    float near_z
);

/**
 * @brief Projects a camera-space triangle to screen space using perspective division.
 *
 * Applies the projection formula: x_screen = (x * focal / z) + width/2,
 * y_screen = (y * focal / z) + height/2. Vertex colours are carried through unchanged.
 *
 * @param triangle      A camera-space triangle with z > 0 for all vertices.
 * @param focal_length  Camera focal length.
 * @param width         Framebuffer width in pixels.
 * @param height        Framebuffer height in pixels.
 * @return              The projected screen-space triangle.
 */
Triangle2 projectTriangle(
    const Triangle3& triangle,
    float focal_length,
    float width,
    float height
);
