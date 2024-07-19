




#include "Viewport.h"
#include <iostream>
#include <SDL2/SDL.h>


Viewport::Viewport(int w, int h, int x, int y) 
    : thread_life(false),
    width(w),
    height(h),
    x_loc(x),
    y_loc(y),
    window(nullptr),
    screenSurface(nullptr) {


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

void Viewport::set_frame_buffer(std::array<std::vector<std::vector<int>>, 3> frame) {
    frame_buffer = frame;

}

void Viewport::thread_action() {
    
    // Create window
    window = SDL_CreateWindow("SDL Tutorial",
                                          x_loc,
                                          y_loc,
                                          width,
                                          height,
                                          SDL_WINDOW_SHOWN);
    
    
    if (window == NULL) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Get window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    if (screenSurface == NULL) {
        std::cerr << "Could not get window surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return; // Early return on error
    }
    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    // Update the surface
    SDL_UpdateWindowSurface(window);
    // Event handler
    SDL_Event e;
    // Main loop

    thread_life = true;
    while (true) {
        
        if(!thread_life) {
            break;
        }
        
        // Handle events on the queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                thread_life = false;
            }
        }
        // Fill the surface white again in case it's needed
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
        // Update the surface
        SDL_UpdateWindowSurface(window);


    }
}

bool Viewport::start() {
    handler_thread = std::thread(&Viewport::thread_action, this);

    return true;
}

bool Viewport::kill() {
    
    thread_life = false;


    if (handler_thread.joinable()) {
        handler_thread.join();
    }
    
    
    // Destroy window and quit SDL subsystems
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
    

    return true;
}

bool Viewport::alive() {
    return thread_life;

}

bool Viewport::update() {

    frame_current = frame_buffer;

    if (!screenSurface) {
        std::cerr << "Screen surface not initialized!" << std::endl;
        return false;
    }

    // Lock the surface for direct access
    SDL_LockSurface(screenSurface);

    Uint32* pixels = (Uint32*)screenSurface->pixels;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Uint32 r = frame_current[0][x][y];
            Uint32 g = frame_current[1][x][y];
            Uint32 b = frame_current[2][x][y];
            pixels[(y * screenSurface->w) + x] = (r << 16) | (g << 8) | b;
        }
    }

    // Unlock the surface
    SDL_UnlockSurface(screenSurface);

    // Update the surface
    SDL_UpdateWindowSurface(window);

    return true;
}

// Destructor to join the thread
Viewport::~Viewport() {
    kill();

}




