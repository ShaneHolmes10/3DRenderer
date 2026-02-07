#include "CppUnitLite/TestHarness.h"
#include "display/Viewport.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


sf::Image create_circle_image(int x, int y, int r) {
    sf::RenderTexture renderTexture;
    renderTexture.create(800, 600);

    sf::CircleShape circle(r);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x, y);

    renderTexture.clear(sf::Color::White);
    renderTexture.draw(circle);
    renderTexture.display();

    sf::Texture texture = renderTexture.getTexture();
    sf::Image image_1 = texture.copyToImage();

    return image_1;
}


TEST(Viewport, SetFrameDisplaysGreenCircle)
{
    int width = 600;
    int height = 400;

    Viewport::init();

    Viewport v1(width, height);
    v1.start();

    v1.set_frame(create_circle_image(width / 2, height / 2, 100));
    v1.update();

    std::string answer;
    std::cout << "Did the screen show a green circle: ";
    std::cin >> answer;

    CHECK(answer == "y");

    v1.join();
}


TEST(Viewport, AnimatedCircleMovesDownward)
{
    int width = 600;
    int height = 400;

    Viewport::init();

    Viewport v1(width, height);
    v1.start();

    for(int n = 0; n < 50; n++) {
        v1.set_frame(create_circle_image(width / 2, height / 2 + n*4, 100));
        v1.update();
    }

    std::string answer;
    std::cout << "Did the screen show a green circle animation: ";
    std::cin >> answer;

    CHECK(answer == "y");

    v1.join();
}


int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}