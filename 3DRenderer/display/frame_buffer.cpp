// FrameBuffer.cpp
#include "display/frame_buffer.h"

FrameBuffer::FrameBuffer(size_t w, size_t h) 
    : width(w), height(h), pixels(w * h * 3, 0) {}

void FrameBuffer::setPixel(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b) {
    
    if (x >= width || y >= height) {
        throw std::out_of_range("Pixel coordinates out of bounds");
    }

    size_t index = (y * width + x) * 3;
    pixels[index + 0] = r;
    pixels[index + 1] = g;
    pixels[index + 2] = b;
}