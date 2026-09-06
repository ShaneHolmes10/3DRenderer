#pragma once

#include <SFML/Graphics/Image.hpp>
#include <stdexcept>
#include <string>

#include "display/frame_buffer.h"

/**
 * @brief Loads a PNG from disk into a FrameBuffer.
 *
 * @param path  Path to the image file.
 * @return      FrameBuffer populated with the image's RGBA pixels.
 * @throws      std::runtime_error if the file cannot be loaded.
 */
inline FrameBuffer load_texture(const std::string& path) {
    sf::Image image;
    if (!image.loadFromFile(path)) {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    size_t w = image.getSize().x;
    size_t h = image.getSize().y;
    FrameBuffer fb(w, h);

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            sf::Color c = image.getPixel(x, y);
            fb.setPixel(x, y, c.r, c.g, c.b, c.a);
        }
    }

    return fb;
}
