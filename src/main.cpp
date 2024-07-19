#include <SFML/Graphics.hpp>
#include <string>

class WindowManager {
public:
    WindowManager(int width, int height, const std::string& title)
        : m_window(sf::VideoMode(width, height), title), m_title(title) {
        // Initialize the window or other settings if needed
        m_window.setVerticalSyncEnabled(true);
    }

    void setTitle(const std::string& title) {
        m_window.setTitle(title);
    }

    void setSize(int width, int height) {
        m_window.setSize(sf::Vector2u(width, height));
    }

    void draw(const sf::Drawable& drawable) {
        m_window.clear(sf::Color::Black);
        m_window.draw(drawable);
        m_window.display();
    }

    void handleEvents() {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            // Handle other events if needed
        }
    }

    bool isOpen() const {
        return m_window.isOpen();
    }

private:
    sf::RenderWindow m_window;
    std::string m_title;
};

int main() {
    WindowManager window1(800, 600, "Window 1");
    WindowManager window2(1024, 768, "Window 2");

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);

    while (window1.isOpen() || window2.isOpen()) {
        if (window1.isOpen()) {
            window1.handleEvents();
            window1.draw(shape);
        }

        if (window2.isOpen()) {
            window2.handleEvents();
            window2.draw(shape);
        }
    }

    return 0;
}







/*

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <SDL2/SDL.h>

std::atomic<bool> gRunning(true); // Global atomic variable to control the main loop
std::mutex gMutex; // Mutex for synchronization
std::condition_variable gCV; // Condition variable for synchronization

// Function to handle the SDL window and rendering
void sdlThreadFunc() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        gRunning = false;
        return;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL White Screen",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        gRunning = false;
        SDL_Quit();
        return;
    }

    // Create a renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        gRunning = false;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Main rendering loop
    while (gRunning) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gRunning = false; // Exit the main loop when the window is closed
                break;
            }
        }

        // Set render draw color to white (255, 255, 255)
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // Delay to manage CPU usage
        SDL_Delay(10);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    // Create a thread for SDL operations
    std::thread sdlThreadObj(sdlThreadFunc);

    // Main application loop (not blocking SDL operations)
    for(int x = 0; x < 100; x++) {
        // Example of work done in the main thread
        std::cout << "Hello from the main thread!" << std::endl;
        
        // Delay to simulate other tasks
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Example of doing other tasks in the main thread
        // This loop can be used for any non-SDL-related work
    }

    // Signal SDL thread to exit
    {
        std::lock_guard<std::mutex> lock(gMutex);
        gRunning = false;
    }
    gCV.notify_one();

    // Join the SDL thread
    if (sdlThreadObj.joinable()) {
        sdlThreadObj.join();
    }

    return 0;
}
*/











/*
#include <SDL2/SDL.h>
#include <iostream>
#include "Viewport.h"
#include <chrono>


int main() {

    int width = 600;
    int height = 400;

    // Initialize the frame buffer with proper dimensions
    std::array<std::vector<std::vector<int>>, 3> frame;
    for (auto& channel : frame) {
        channel.resize(width);
        for (auto& row : channel) {
            row.resize(height, 0); // Initialize all values to 0
        }
    }

    // Set the image to red
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            frame[0][x][y] = 255; // Red channel
            frame[1][x][y] = 0;   // Green channel
            frame[2][x][y] = 0;   // Blue channel
        }
    }

    //Viewport v1;
    //v1.start();

    //Viewport v2;
    //v2.start();

    return 0;
}
*/


