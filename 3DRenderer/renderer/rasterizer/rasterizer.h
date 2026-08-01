#pragma once

#include "renderer/rasterizer/types.h"

/**
 * @brief Three per-vertex Varyings defining the triangle fed to
 * rasterize().
 */
struct RasterTriangle {
    Varying v0, v1, v2;
};

/**
 * @brief Rasterizes a screen-space triangle into the framebuffer using
 *        a caller-supplied fragment shader.
 *
 * Scans the triangle's bounding box and, for every pixel inside the
 * triangle that passes the depth test, interpolates a Varying from
 * the three vertex Varyings via barycentric weights and calls
 * shader(uniform, varying) to determine the fragment's color. Knows
 * nothing about meshes, entities, or the pipeline that produced this
 * triangle.
 *
 * @param triangle  Three per-vertex Varyings in screen space.
 * @param uniform   Data constant across every fragment of this
 * triangle.
 * @param shader    Computes a fragment's color from uniform and varying
 * data.
 * @param buffers   The frame and depth buffers to test and write into.
 */
void rasterize(const RasterTriangle& triangle, const Uniform& uniform,
               const Shader& shader, Buffers& buffers);
