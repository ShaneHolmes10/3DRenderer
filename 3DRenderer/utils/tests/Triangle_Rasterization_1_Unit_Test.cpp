#include <Eigen/Dense>
#include <iostream>
#include <random>
#include <vector>

#include "Testing_Methods.h"
#include "Testing_Utils.h"
#include "Viewport.h"

/*
    Confirm that triangle rasterization works
*/

/*
    Draw a triangle and display it
*/
void test_1() {
    int width = 800;
    int height = 600;

    // Create an image
    sf::Image image;
    image.create(width, height,
                 sf::Color::White);  // Create an image object to color

    Viewport::init();

    Viewport view1(width, height, 0, 0);
    view1.start();

    for (float ind = 0; ind < 200; ind++) {
        image.create(width, height, sf::Color::White);
        TestMeth::create_triangle(image, {163, 277}, {793, 280},
                                  {458, 462 - ind}, {255, 0, 0},
                                  {0, 255, 0}, {0, 0, 255});
        view1.set_frame(image);
        view1.update();
    }

    view1.join();
}

int main() {
    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}