#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    std::cout << "Showing one window" << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed: " << event.key.code << std::endl;
            }
        }
        
        window.clear(sf::Color::White);
        window.display();
    }
    
    return 0;
}