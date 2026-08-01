#pragma once

#include <Eigen/Dense>
#include <vector>

/**
 * @brief A sampleable grid of RGB pixels.
 *
 * Row-major, top-to-bottom like FrameBuffer.
 */
struct Texture {
    std::vector<Eigen::Vector3i> pixels;
    size_t width = 0;
    size_t height = 0;
};
