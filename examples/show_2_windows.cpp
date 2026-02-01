#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <X11/Xlib.h>

void runWindow1() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Window 1");
    window.setPosition(sf::Vector2i(0, 0));
    
    int counter = 0;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Window 1 - Key: " << event.key.code << std::endl;
            }
        }
        
        window.clear(sf::Color(255, counter % 255, 0));
        window.display();
        
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void runWindow2() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Window 2");
    window.setPosition(sf::Vector2i(450, 0));
    
    int counter = 0;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Window 2 - Key: " << event.key.code << std::endl;
            }
        }
        
        window.clear(sf::Color(0, counter % 255, 255));
        window.display();
        
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

int main() {
    XInitThreads();
    
    std::thread t1(runWindow1);
    std::thread t2(runWindow2);
    
    t1.join();
    t2.join();
    
    return 0;
}