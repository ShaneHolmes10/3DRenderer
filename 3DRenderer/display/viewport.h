
#ifndef VIEWPORT_H
#define VIEWPORT_H


#include "display/frame_buffer.h"
#include "display/key.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

/**
 * @brief This class is responsible for facilitating the display of the pixels to 
 * the screen. 
 * 
 * The view exists on a separate thread which allows us to have multiple views
 * as well as to facilitate the main rendering loop separate from the viewport.
 * 
 */
class Viewport { 
private:

    /**
     * @brief This is the width of the window on the screen.
     * 
     */
    int width;

    /**
     * @brief This is the height of the window on the screen.
     * 
     */
    int height;

    /**
     * @brief This is the x position of the window on the screen.
     * 
     */
    int x_pos;

    /**
     * @brief This is the y position of the window on the screen.
     * 
     */
    int y_pos;

    /**
     * @brief This is the frame that we are displaying to the window.
     * 
     */
    sf::Texture frame;

    /**
     * @brief This is the frame buffer that holds the next frame until 
     * we're ready.
     * 
     */
    sf::Texture frame_buffer;

    /**
     * @brief This is the frame mutex lock to prevent thread objects from 
     * simultaneously accessing shared thread resources, thus preventing
     * a race condition.
     * 
     */
    std::mutex frame_mutex;

    /**
     * @brief This is the actual window thread object. This thread runs 
     * in parallel to the main program thread, allowing the view to 
     * run separately to the main thread.
     * 
     */
    std::thread windowThread;

    /**
     * @brief This is the thread method that facilitates the window function.
     * 
     */
    void runWindow();

    /**
     * @brief This is the callback to call when events occur.
     * 
     */
    std::function<void(KeyCode)> key_callback;

public:

    /**
     * @brief Construct a new Viewport object.
     * 
     * @param w width of the window
     * @param h height of the window
     * @param x position of window on the screen
     * @param y position of window on the screen
     */
    Viewport(int w = 800, int h = 600, int x = 500, int y = 500);
    
    ~Viewport();

    /**
     * @brief This method needs to be called before hand to initialize the 
     * view object instance.
     * 
     */
    static void init();

    /**
     * @brief This method starts the thread that the view run on thus
     * beginning the drawing process.
     * 
     */
    void start();

    /**
     * @brief This updates the view with the image stored in the 
     * frame buffer.
     * 
     */
    void update();

    /**
     * @brief This method sets the frame buffer of the view to be what ever the input
     * image is. 
     * 
     * @param frame_buff Image to place in the frame buffer
     */
    void setFrame(const FrameBuffer& frame_buff);

    /**
     * @brief When done with the view we will need to join it back to the main thread.
     * 
     */
    void join();

    /**
     * @brief Set a callback function to handle window events
     */
    void setKeyCallback(std::function<void(KeyCode)> callback);
};

#endif
