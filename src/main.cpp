
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











/**/
#include <SDL2/SDL.h>
#include <iostream>
#include "Viewport.h"



int main() {

    std::cout << "Entering Main code \n";
    Viewport v1;

    v1.start();
    std::cout << "Exiting Main Code \n";


    return 0;
}
