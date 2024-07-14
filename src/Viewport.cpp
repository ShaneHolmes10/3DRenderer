
#include "Viewport.h"
#include <iostream>
#include <SDL2/SDL.h>


Viewport::Viewport(int w, int h) 
    : thread_life(false),
    width(w),
    height(h) {

    // Initialize frame_current and frame_buffer with zeros
    for (auto& channel : frame_current) {
        channel.resize(width);
        for (auto& row : channel) {
            row.resize(height, 0);
        }
    }

    for (auto& channel : frame_buffer) {
        channel.resize(width);
        for (auto& row : channel) {
            row.resize(height, 0);
        }
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

}

void Viewport::set_frame(std::array<std::vector<std::vector<int>>, 3> frame) {

    

}

void Viewport::thread_action() {
    
    // Create window
    window = SDL_CreateWindow("SDL Tutorial",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          width,
                                          height,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    // Get window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);


    // Event handler
    SDL_Event e;

    // Main loop
    while (thread_life) {
        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                thread_life = false;
            }
        }

        std::cout << "In main thread" << std::endl;
        // Fill the surface white again in case it's needed
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

        // Update the surface
        SDL_UpdateWindowSurface(window);
    }

}

bool Viewport::start() {
    thread_life = true;
    handler_thread = std::thread(&Viewport::thread_action, this);

    return true;
}

bool Viewport::kill() {
    thread_life = false;
    
    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return true;
}

bool Viewport::alive() {

    return thread_life;
}

bool Viewport::update() {

    return true;
}

// Destructor to join the thread
Viewport::~Viewport() {
    if (handler_thread.joinable()) {
        handler_thread.join();
    }
}




