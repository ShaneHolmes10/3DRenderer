
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include <X11/Xlib.h> // Include X11 header


class Viewport { 
private:

    int width;
    int height;
    int x_pos;
    int y_pos;

    sf::Texture frame;
    sf::Texture frame_buffer;
    std::mutex frame_mutex;

    std::thread windowThread;

    void runWindow();

public:
    Viewport(int w = 800, int h = 600, int x = 500, int y = 500);
    
    static void init();

    void start();

    int update();

    int set_frame(sf::Image frame_buff);

    void join();
};

#endif
