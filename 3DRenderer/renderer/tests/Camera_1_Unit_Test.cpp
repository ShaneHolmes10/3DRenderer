#include <chrono>
#include <cmath>
#include <iostream>

#include "Camera.h"
#include "Stage.h"
#include "Testing_Utils.h"
#include "Vector_Object.h"
#include "Viewport.h"

/*
    For testing, we need to adjust the camera
    position
    orientation
    FOV
    photo dimensions
    play around with a cube animation
    ensure that vectors aren’t projected out of bounds(behind photo
   plane, outside FOV).

*/

/*
    Baseline check, ensure that we can see the dots in the grid
*/
void test_1() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(0, 0, -200);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did you see 9 red dots in a grid in the center of "
                 "the screen? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Check for the changes in position, We do this by shifting the camera
   to the side by 1000 units
*/
void test_2() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(0, 1000, -200);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did the dots move up? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Check for the changes in position, We do this by shifting the camera
   to the side by 1000 units
*/
void test_3() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(1000, 0, -200);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did the dots move to the left? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Check for the changes in orientation, rotate the camera 22.5 deg
   about the X axis
*/
void test_4() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(0, 0, -200, (M_PI / 8), 0, 0);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did the dots move downward and spread? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Check for the changes in orientation, rotate the camera 22.5 deg
   about the Y axis
*/
void test_5() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(0, 0, -200, 0, (M_PI / 8), 0);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did the dots move to the left and spread? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Check for the changes in orientation, rotate the camera 22.5 deg
   about the Z axis
*/
void test_6() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(0, 0, -200, 0, 0, (M_PI / 8));

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did the dots rotate a little bit? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Check for the changes in FOV, making it larger
*/
void test_7() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(0, 0, -200);
    c1.set_FOV_length(150);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did the dot grid appear to expand? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Check for the changes in FOV, making it smaller
*/
void test_8() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

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

    Camera c1(0, 0, -200);
    c1.set_FOV_length(50);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::string answer;

    std::cout << "Did the dot grid appear to compress? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Rotate the camera around a cube
*/
void test_9() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

    Stage s1;

    VectorObject v1(800, 800, 800);
    VectorObject v2(800, -800, 800);
    VectorObject v3(-800, 800, 800);
    VectorObject v4(-800, -800, 800);

    VectorObject v5(800, 800, 2400);
    VectorObject v6(800, -800, 2400);
    VectorObject v7(-800, 800, 2400);
    VectorObject v8(-800, -800, 2400);

    s1.add(&v1);
    s1.add(&v2);
    s1.add(&v3);
    s1.add(&v4);

    s1.add(&v5);
    s1.add(&v6);
    s1.add(&v7);
    s1.add(&v8);

    Camera c1(0, 0, -200, 0, 0, 0);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    // float n = 13;
    for (float n = 0; n < 200; n++) {
        // std::cout << n << "\n";

        c1.set_ox(1800 * cos(((n / 100) * 2 * M_PI) - (M_PI / 2)));
        c1.set_oz(1800 * sin(((n / 100) * 2 * M_PI) - (M_PI / 2)) +
                  1600);

        c1.set_ay(-((n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();

        // std::cout << c1.get_placement_vector() << std::endl;
        // std::cout << c1.get_angles() << std::endl;

        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    view1.join();

    std::string answer;

    std::cout << "Do the dots appear to form a cube, and is that cube "
                 "rotating? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

/*
    Rotate the camera around a cube
*/
void test_10() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

    Stage s1;

    VectorObject v1(800, 800, 800);
    VectorObject v2(800, -800, 800);
    VectorObject v3(-800, 800, 800);
    VectorObject v4(-800, -800, 800);

    VectorObject v5(800, 800, 2400);
    VectorObject v6(800, -800, 2400);
    VectorObject v7(-800, 800, 2400);
    VectorObject v8(-800, -800, 2400);

    s1.add(&v1);
    s1.add(&v2);
    s1.add(&v3);
    s1.add(&v4);

    s1.add(&v5);
    s1.add(&v6);
    s1.add(&v7);
    s1.add(&v8);

    Camera c1(0, 0, -200, 0, 0, 0);

    c1.set_stage(s1);

    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    // float n = 13;
    for (float n = 0; n < 200; n++) {
        c1.set_ay(-((n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();
    }

    view1.join();

    std::string answer;

    std::cout << "Do the dots appear to form a cube, is the cube "
                 "orbiting the camera? ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));
}

int main() {
    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);
    TestUtils::perform_test(test_4);
    TestUtils::perform_test(test_5);
    TestUtils::perform_test(test_6);
    TestUtils::perform_test(test_7);
    TestUtils::perform_test(test_8);
    TestUtils::perform_test(test_9);
    TestUtils::perform_test(test_10);

    TestUtils::end_testing();

    return 0;
}