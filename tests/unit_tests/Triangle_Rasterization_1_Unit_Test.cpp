#include <iostream>
#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include <vector>
#include <Eigen/Dense>
#include <random>
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

    

    Viewport::init();

    Viewport view1(width, height, 0, 0);
    view1.start();


    for(int ind = 0; ind < 100; ind++) {
        sf::Image image = TestMeth::create_triangle(width, height, {163,277-ind}, {793,280}, {458,462}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255});
        view1.set_frame(image);
        view1.update();

        view1.delay_ms(100);
    }

    //image = TestMeth::create_triangle(width, height, {163,210}, {793,280}, {458,462}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255});
    //view1.set_frame(image);
    //view1.update();


    std::cout << "Delay has occurred\n";

    view1.join();


}


int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}