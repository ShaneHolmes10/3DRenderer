
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include <vector>
#include <array>
#include <thread>
#include <chrono>
#include <mutex> 
#include <atomic>
#include <SDL2/SDL.h>

class Viewport {
private:
    int width;
    int height;

    int x_loc;
    int y_loc;

    std::thread handler_thread;

    SDL_Window* window;
    SDL_Surface* screenSurface;

    std::array<std::vector<std::vector<int>>, 3> frame_current;
    std::array<std::vector<std::vector<int>>, 3> frame_buffer;

    std::atomic<bool> thread_life;

    std::mutex mutex_thread_life;

    void thread_action();

public:
    Viewport(int w = 500, int h = 200, int x = SDL_WINDOWPOS_UNDEFINED, int y = SDL_WINDOWPOS_UNDEFINED);

    void set_frame_buffer(std::array<std::vector<std::vector<int>>, 3> frame);
    bool start();
    bool kill();
    bool alive();
    bool update(); 

    ~Viewport();

};

#endif
