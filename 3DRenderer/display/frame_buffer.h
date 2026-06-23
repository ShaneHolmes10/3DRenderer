// FrameBuffer.h
#pragma once

#include <cstdint>
#include <vector>
struct FrameBuffer {
    std::vector<uint8_t> pixels;
    size_t width;
    size_t height;

    FrameBuffer(size_t w, size_t h);
    void setPixel(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b,
                  uint8_t a = 255);

    /**
     * @brief Reset all pixels to white (255) for the start of a new
     * frame.
     */
    void clear();
};