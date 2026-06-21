#include "display/depth_buffer.h"

DepthBuffer::DepthBuffer(size_t w, size_t h)
    : width(w), height(h), values(w * h, 0.0f) {}

void DepthBuffer::clear() {
    std::fill(values.begin(), values.end(), 0.0f);
}
