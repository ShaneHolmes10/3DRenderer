
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include <vector>
#include <array>
#include <thread>
#include <chrono>

class Viewport {
private:
    int width;
    int height;

    std::thread handler_thread;

    std::array<std::vector<std::vector<int>>, 3> frame_current;
    std::array<std::vector<std::vector<int>>, 3> frame_buffer;

    bool thread_life;

    void thread_action();

public:
    Viewport(int w = 500, int h = 200);

    void set_frame(std::array<std::vector<std::vector<int>>, 3> frame);
    bool start();
    bool kill();
    bool alive();
    bool update(); 

    ~Viewport();

};

#endif
