
#include "display/viewport.h"

#include <X11/Xlib.h>  // Include X11 header for threads

#include <SFML/Graphics.hpp>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <thread>

#include "display/key.h"

void Viewport::runWindow() {
    // Create a window with a size of 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(width, height), "Window");
    window.setPosition(sf::Vector2i(x_pos, y_pos));
    window.clear(sf::Color::White);
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user closes it
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && key_callback) {
                Key key = static_cast<Key>(event.key.code);
                key_callback(key);
            }
        }
        window.clear(sf::Color::White);  // wipe the screen
        {
            std::lock_guard<std::mutex> lock(frame_mutex);
            sf::Sprite sprite(frame);
            window.draw(sprite);
        }
        // Display the contents of the window
        window.display();
    }
}

Viewport::Viewport(int w, int h, int x, int y)
    : width(w), height(h), x_pos(x), y_pos(y), key_callback(nullptr) {}

void Viewport::init() { XInitThreads(); }

void Viewport::start() {
    // Start the thread with the member function
    windowThread = std::thread(&Viewport::runWindow, this);
}

void Viewport::update() {
    std::lock_guard<std::mutex> lock(frame_mutex);
    frame = frame_buffer;
}

void Viewport::setFrame(const FrameBuffer& frame_buff) {
    std::lock_guard<std::mutex> lock(frame_mutex);

    sf::Image sfImage;
    sfImage.create(
        frame_buff.width, frame_buff.height,
        frame_buff.pixels.data()  // Direct pointer to pixel data
    );

    sf::Texture texture;
    if (!texture.loadFromImage(sfImage)) {
        throw std::runtime_error("Failed to load texture from image");
    }
    frame_buffer = texture;
}

void Viewport::join() {
    if (windowThread.joinable()) {
        windowThread.join();
    }
}

Viewport::~Viewport() { join(); }

void Viewport::setKeyCallback(std::function<void(Key)> callback) {
    key_callback = callback;
}
