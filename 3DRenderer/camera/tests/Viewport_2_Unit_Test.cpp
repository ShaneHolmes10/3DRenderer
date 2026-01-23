#include <iostream>
#include "Testing_Utils.h"
#include <vector>
#include <Eigen/Dense>
#include "Viewport.h"
#include <chrono>


/*
This test will confirm some basic functionality of the Viewport object class/

We want to be able to set a value to the frame buffer
We want that image to be set to the window

*/




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


/*
    Test to see if the window was created and the frame was set properly
*/
void test_1() {

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

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    v1.join();

}


/*
    Test to see if the window was created
*/
void test_2() {

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

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    v1.join();

}



int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);

    TestUtils::end_testing();

    return 0;
}