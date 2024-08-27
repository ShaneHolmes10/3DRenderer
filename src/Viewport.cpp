

#include "Viewport.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include <X11/Xlib.h> // Include X11 header
#include <chrono>



void Viewport::runWindow() {
    // Create a window with a size of 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(width, height), "Window");
    window.setPosition(sf::Vector2i(x_pos, y_pos));
    window.clear(sf::Color::White);
    // Main loop
    while(window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user closes it
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
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
    : width(w),
      height(h),
      x_pos(x),
      y_pos(y) {
}

void Viewport::init() {
    XInitThreads();

}

void Viewport::start() {
    // Start the thread with the member function
    windowThread = std::thread(&Viewport::runWindow, this);
}

int Viewport::update() {
    {
        std::lock_guard<std::mutex> lock(frame_mutex);
        frame = frame_buffer;
    }
    return 0;
}

int Viewport::set_frame(sf::Image frame_buff) {
    {
        std::lock_guard<std::mutex> lock(frame_mutex);
        
        sf::Texture texture;
        if (!texture.loadFromImage(frame_buff)) {
            return -1;
        } 
        frame_buffer = texture;
    }
    
    return 0;
}

void Viewport::delay_ms(int delay_time) {

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));

}

void Viewport::join() {
    if (windowThread.joinable()) {
        windowThread.join();
    }
}



