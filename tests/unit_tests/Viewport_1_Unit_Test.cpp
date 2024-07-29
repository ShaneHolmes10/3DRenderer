#include <iostream>
#include "Testing_Utils.h"
#include <vector>
#include <Eigen/Dense>
#include "Viewport.h"
#include <chrono>


/*
This test will confirm some basic functionality of the Viewport object class/

We want to be able to create a window with the default dimensions
We want to be able to create a window with parameter dimensions
We want to be able to create a window with parameter dimensions and a specific location
We want to be able to have two windows at the same time

*/


/*
    Test to see if the window was created
*/
void test_1() {

    Viewport::init();

    Viewport v1;
    v1.start();

    std::string answer;

    std::cout << "Did the window appear: ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    v1.join();

}

/*
    Test to see if the window was created with proper dimensions
*/
void test_2() {

    Viewport::init();

    Viewport v1(1000, 800);
    v1.start();

    std::string answer;

    std::cout << "Did the window appear with larger dimensions: ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    v1.join();

}

/*
    Test to see if the window was created with proper dimensions and in the right location
*/
void test_3() {

    Viewport::init();

    Viewport v1(800, 600, 0, 0);
    v1.start();

    std::string answer;

    std::cout << "Did the window appear with larger dimensions and in the right location: ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    v1.join();

}


/*
    Verify that can have more than one window at a time
*/
void test_4() {

    Viewport::init();

    Viewport v1(600, 400, 0, 0);
    v1.start();

    Viewport v2(600, 400, 400, 0);
    v2.start();


    std::string answer;

    std::cout << "Did both windows show up: ";
    std::cin >> answer;
    
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    v1.join();
    v2.join();

}



int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);
    TestUtils::perform_test(test_4);

    TestUtils::end_testing();

    return 0;
}