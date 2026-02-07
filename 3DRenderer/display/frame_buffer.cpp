// FrameBuffer.cpp
#include "display/frame_buffer.h"
#include <stdexcept>

FrameBuffer::FrameBuffer(size_t w, size_t h) 
    : width(w), height(h), pixels(w * h * 4, 0) {}

void FrameBuffer::setPixel(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    
    if (x >= width || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }

    size_t index = (y * width + x) * 4;
    pixels[index + 0] = r;
    pixels[index + 1] = g;
    pixels[index + 2] = b;
    pixels[index + 3] = a;
}