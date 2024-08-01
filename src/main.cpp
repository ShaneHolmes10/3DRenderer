



#include <iostream>
#include "Camera.h"
#include "Vector_Object.h"
#include "Stage.h"
#include "Viewport.h"


int main() {

    Stage s1;

    VectorObject v1(800, 0, 800);
    VectorObject v2(800, 800, 800);
    VectorObject v3(800, -800, 800);

    VectorObject v4(0, 0, 800);
    VectorObject v5(0, 800, 800);
    VectorObject v6(0, -800, 800);

    VectorObject v7(-800, 0, 800);
    VectorObject v8(-800, 800, 800);
    VectorObject v9(-800, -800, 800);


    s1.add(&v1);
    s1.add(&v2);
    s1.add(&v3);

    s1.add(&v4);
    s1.add(&v5);
    s1.add(&v6);
    
    s1.add(&v7);
    s1.add(&v8);
    s1.add(&v9);



    Camera c1(0, 0, -100);

    c1.set_stage(s1);

    
    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::cout << "Done taking a picture\n"; 


    return 0;
}



/*
#include <iostream>
#include "Viewport.h"

sf::Image create_circle_image(int x, int y, int r) {

    // Create an off-screen render target
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600); // Size of the render texture

    // Create shapes
    sf::CircleShape circle(r); // Circle with radius of 100
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x, y); // Position of the circle

    // Draw shapes to the render texture
    renderTexture.clear(sf::Color::White); // Clear with white background
    renderTexture.draw(circle);
    renderTexture.display(); // Display the result

    // Create a texture from the render texture
    sf::Texture texture = renderTexture.getTexture();

    // Create an image from the texture
    sf::Image image_1 = texture.copyToImage();

    return image_1;
}


int main() {
    // Initialize X11 threading system
    //XInitThreads();

    Viewport::init();

    Viewport v1(800, 600, 0, 0);
    Viewport v2(600, 400, 800, 0);

    
    v1.start();
    v2.start();

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    v1.set_frame(create_circle_image(400, 300, 100));
    v1.update();

    for(int n = 0; n < 200; n++) {
        v1.set_frame(create_circle_image(400, 100 + 5*n, 100));
        v1.update();
        std::cout << "This is in the main thread\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    v1.join();
    v2.join();

    return 0;
}
*/


/*
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include <X11/Xlib.h> // Include X11 header


class WindowManager { 
private:

    int width;
    int height;
    int x_pos;
    int y_pos;

    sf::Texture frame;
    sf::Texture frame_buffer;
    std::mutex frame_mutex; // Mutex for locking

    std::thread windowThread;

    void runWindow() {
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

public:
    WindowManager(int w, int h, int x, int y) 
        : width(w),
          height(h),
          x_pos(x),
          y_pos(y) {

    };

    void start() {
        // Start the thread with the member function
        windowThread = std::thread(&WindowManager::runWindow, this);
    }

    int update() {
        {
            std::lock_guard<std::mutex> lock(frame_mutex);
            frame = frame_buffer;
        }

        return 0;
    }

    int set_frame(sf::Image frame_buff) {
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

    void join() {
        if (windowThread.joinable()) {
            windowThread.join();
        }
    }
};


sf::Image create_circle_image(int x, int y, int r) {

    // Create an off-screen render target
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600); // Size of the render texture

    // Create shapes
    sf::CircleShape circle(r); // Circle with radius of 100
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x, y); // Position of the circle

    // Draw shapes to the render texture
    renderTexture.clear(sf::Color::White); // Clear with white background
    renderTexture.draw(circle);
    renderTexture.display(); // Display the result

    // Create a texture from the render texture
    sf::Texture texture = renderTexture.getTexture();

    // Create an image from the texture
    sf::Image image_1 = texture.copyToImage();

    return image_1;
}


int main() {
    // Initialize X11 threading system
    XInitThreads();

    WindowManager w1(800, 600, 0, 0);
    //WindowManager w2(600, 400, 800, 0);

    
    w1.start();
    //w2.start();

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    w1.set_frame(create_circle_image(400, 300, 100));
    w1.update();

    for(int n = 0; n < 200; n++) {
        w1.set_frame(create_circle_image(400, 100 + 5*n, 100));
        w1.update();
        std::cout << "This is in the main thread\n";
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    w1.join();
    //w2.join();

    return 0;
}
*/



      







/*
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <X11/Xlib.h> // Include X11 headers for XInitThreads

// Function to initialize X11 threading
void initializeX11() {
    // Call XInitThreads() to initialize X11 threading support
    XInitThreads();
}

// Function to create and manage a single window
void runWindow(const std::string& title, int x, int y) {
    // Initialize X11 threading
    initializeX11();

    // Create a window with a size of 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(800, 600), title);

    // Set the position of the window
    window.setPosition(sf::Vector2i(x, y));

    // Create a circle shape with a radius of 50 pixels
    sf::CircleShape circle(50);

    // Set the fill color to green
    circle.setFillColor(sf::Color::Green);

    // Set the position of the circle in the window
    circle.setPosition(375, 275); // Centered in the window

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user closes it
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw the circle
        window.draw(circle);

        // Display the contents of the window
        window.display();
    }
}

int main() {
    // Start two threads for two windows
    std::thread windowThread1(runWindow, "SFML Window 1", 100, 100);
    std::thread windowThread2(runWindow, "SFML Window 2", 950, 100);

    // Wait for both threads to finish
    windowThread1.join();
    windowThread2.join();

    return 0;
}
*/



/*
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

class WindowManager { 
private:
    std::thread windowThread;

    void runWindow() {
        // Create a window with a size of 800x600 pixels
        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

        // Create a circle shape with a radius of 50 pixels
        sf::CircleShape circle(50);

        // Set the fill color to green
        circle.setFillColor(sf::Color::Green);

        // Set the position of the circle in the window
        circle.setPosition(375, 275); // Centered in the window

        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                // Close the window if the user closes it
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            // Clear the window with a black color
            window.clear(sf::Color::Black);

            // Draw the circle
            window.draw(circle);

            // Display the contents of the window
            window.display();
        }
    }

public:
    WindowManager() = default;

    void start() {
        // Start the thread with the member function
        windowThread = std::thread(&WindowManager::runWindow, this);
    }

    void join() {
        if (windowThread.joinable()) {
            windowThread.join();
        }
    }
};

int main() {
    WindowManager w1;
    WindowManager w2;

    w1.start();
    w2.start();


    w1.join();
    w2.join();

    return 0;
}
*/



/*
#include <SFML/Graphics.hpp>

int main() {
    // Create a window with a size of 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Create a circle shape with a radius of 50 pixels
    sf::CircleShape circle(50);
    
    // Set the fill color to green
    circle.setFillColor(sf::Color::Green);
    
    // Set the position of the circle in the window
    circle.setPosition(375, 275); // Centered in the window

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window if the user closes it
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw the circle
        window.draw(circle);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
*/


/*
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

class Window {
public:
    Window(int width, int height, const std::string& title, int x = 0, int y = 0)
        : window(sf::VideoMode(width, height), title, sf::Style::Default)
        , thread(&Window::run, this) {
        window.setPosition(sf::Vector2i(x, y));
    }

    ~Window() {
        if (thread.joinable()) {
            window.close();
            thread.join();
        }
    }

private:
    void run() {
        window.setActive(true); // Ensure context is active for this thread

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color::Black);

            // Example drawing
            sf::CircleShape shape(50);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(375, 275);
            window.draw(shape);

            window.display();
        }
    }

    sf::RenderWindow window;
    std::thread thread;
};

int main() {
    try {
        Window window1(800, 600, "Window 1", 100, 100);
        //Window window2(800, 600, "Window 2", 950, 100);

        // Let windows run for some time
        std::this_thread::sleep_for(std::chrono::seconds(10));
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

*/

