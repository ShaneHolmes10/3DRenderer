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


/*
    Test to see if the window was created
*/
void test_1() {

    int width = 600;
    int height = 400;

    // Initialize the frame buffer with proper dimensions
    std::array<std::vector<std::vector<int>>, 3> frame;
    for (auto& channel : frame) {
        channel.resize(width);
        for (auto& row : channel) {
            row.resize(height, 0); // Initialize all values to 0
        }
    }

    // Set the image to red
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            frame[0][x][y] = 255; // Red channel
            frame[1][x][y] = 0;   // Green channel
            frame[2][x][y] = 0;   // Blue channel
        }
    }



    Viewport v1(width, height);
    v1.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    v1.set_frame_buffer(frame);

    v1.update();


    std::string answer;
    std::cout << "Did the screen change to red: ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

}




int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}