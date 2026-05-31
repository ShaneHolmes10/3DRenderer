#pragma once

#include "draw_triangles_to_screen.h"

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
