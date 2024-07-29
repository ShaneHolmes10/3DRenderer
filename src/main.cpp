


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
        sf::RenderWindow window(sf::VideoMode(width, height), "Test Window");

        window.setPosition(sf::Vector2i(x_pos, y_pos));
        window.clear(sf::Color::White);


        // Main loop
        while (window.isOpen()) {
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            sf::Event event;
            while (window.pollEvent(event)) {
                // Close the window if the user closes it
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }



            {
                std::cout << "In Loop lock\n";
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
        
        /*
        sf::Texture texture;
        if (!texture.loadFromImage(frame_buffer)) {
            return -1;
        } 

        sf::Sprite sprite(texture);
        */

        {
            std::cout << "In update lock\n";
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

int main() {
    // Initialize X11 threading system
    XInitThreads();

    WindowManager w1(800, 600, 0, 0);
    //WindowManager w2(600, 400, 800, 0);



    // Create an off-screen render target
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600); // Size of the render texture

    // Create shapes
    sf::CircleShape circle(100); // Circle with radius of 100
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(200, 150); // Position of the circle

    sf::RectangleShape rectangle(sf::Vector2f(300, 200)); // Rectangle with width 300 and height 200
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(400, 300); // Position of the rectangle

    // Draw shapes to the render texture
    renderTexture.clear(sf::Color::White); // Clear with white background
    renderTexture.draw(circle);
    renderTexture.draw(rectangle);
    renderTexture.display(); // Display the result

    // Create a texture from the render texture
    sf::Texture texture = renderTexture.getTexture();

    // Create an image from the texture
    sf::Image image_1 = texture.copyToImage();

    
    

    w1.start();
    //w2.start();

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    w1.set_frame(image_1);
    w1.update();

    for(int n = 0; n < 100; n++) {
        std::cout << "This is in the main thread\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    w1.join();
    //w2.join();

    return 0;
}




      







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

