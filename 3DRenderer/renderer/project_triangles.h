#pragma once

#include <array>

#include "renderer/types.h"

/**
 * @brief Projects a camera-space triangle to screen space using perspective
 *        division.
 *
 * Applies the projection formula: x_screen = (x * focal / z) + width/2,
 * y_screen = (y * focal / z) + height/2. Stores 1/z in position.z and
 * position.w for depth testing and perspective-correct interpolation.
 *
 * @param triangle      A camera-space triangle as three Varyings with z > 0.
 * @param focal_length  Camera focal length.
 * @param width         Framebuffer width in pixels.
 * @param height        Framebuffer height in pixels.
 * @return              The projected screen-space triangle as three Varyings.
 */
std::array<Varying, 3> projectTriangle(
    const std::array<Varying, 3>& triangle,
    float focal_length,
    float width,
    float height
);
