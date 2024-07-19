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
We want to be able to check if the object is still alive
We want to be able to kill the object
We want to be able to have two windows at the same time

*/


/*
    Test to see if the window was created
*/
void test_1() {

    Viewport v1;
    v1.start();

    std::string answer;

    std::cout << "Did the window appear: ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

}

/*
    Test to see if the window was created with proper dimensions
*/
void test_2() {

    Viewport v1(800, 600);
    v1.start();

    std::string answer;

    std::cout << "Did the window appear with larger dimensions: ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

}

/*
    Test to see if the window was created with proper dimensions and in the right location
*/
void test_3() {

    Viewport v1(800, 600, 0, 0);
    v1.start();

    std::string answer;

    std::cout << "Did the window appear with larger dimensions and in the right location: ";
    std::cin >> answer;

    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

}

/*
    Verify that the alive method worked, Because they're on different threads when we check alive, it may not actually be alive yet; so we must delay
*/
void test_4() {

    Viewport v1(800, 600, 0, 0);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    TestUtils::pass_or_fail_printout(!v1.alive());

}

/*
    Verify that the alive method worked, Because they're on different threads when we check alive, it may not actually be alive yet; so we must delay
*/
void test_5() {

    Viewport v1(800, 600, 0, 0);
    v1.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    TestUtils::pass_or_fail_printout(v1.alive());

}



/*
    Verify that the kill method worked
*/
void test_6() {

    Viewport v1(800, 600, 0, 0);
    v1.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    v1.kill();

    std::string answer;

    std::cout << "Did the window terminate: ";
    std::cin >> answer;
    
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

}

/*
    Verify that can have more than one window at a time
*/
void test_7() {

    Viewport v1(600, 400, 0, 0);
    v1.start();

    Viewport v2(600, 400, 400, 0);
    v2.start();


    std::string answer;

    std::cout << "Did both windows show up: ";
    std::cin >> answer;
    
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

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

    TestUtils::end_testing();

    return 0;
}