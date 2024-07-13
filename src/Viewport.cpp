
#include "Viewport.h"
#include <iostream>


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

}

void Viewport::set_frame(std::array<std::vector<std::vector<int>>, 3> frame) {


}

void Viewport::thread_action() {
    
    int count = 10;
    while(thread_life) {
        std::cout << "Thread" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } 

}

bool Viewport::start() {
    thread_life = true;
    handler_thread = std::thread(&Viewport::thread_action, this);

    return true;
}

bool Viewport::kill() {
    thread_life = false;

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




