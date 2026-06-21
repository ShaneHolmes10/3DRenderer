#pragma once

#include <vector>
#include <cstddef>

// TODO: Add cross compatibility between the framebuffer and the depth buffer for viewport display
// want to be able to display depth buffer to viewport

/**
 * @brief A per-pixel depth buffer holding one inverse-z value per pixel.
 *
 * Stores 1/z (inverse camera-space depth) rather than raw z. This allows
 * correct linear barycentric interpolation in screen space and keeps the
 * depth test a simple > comparison (closer fragments have larger 1/z).
 *
 * Initialized to 0.0f per pixel, representing 1/infinity (nothing drawn yet).
 * Call clear() once at the start of each frame before rendering.
 */
struct DepthBuffer {
    std::vector<float> values;
    size_t width;
    size_t height;

    DepthBuffer(size_t w, size_t h);

    /**
     * @brief Reset all depth values to 0.0f for the start of a new frame.
     */
    void clear();
};
