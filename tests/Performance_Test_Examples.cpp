#include <iostream>
#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include <vector>
#include <Eigen/Dense>


int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

/*
    This technique tracks the amount of time it takes to execute one command
*/
void test_1() {

    TestUtils::start_stop_watch();

    std::cout << fib(35) << std::endl;

    TestUtils::end_stop_watch();

    TestUtils::time_result(500);

}

/*
    This technique tracks the amount of time it takes to execute several commands and then prints it to console. 
*/
void test_2() {

    TestUtils::start_track_time();

    for(int x = 0; x < 45; x++) {
        TestUtils::start_stop_watch();
        std::cout << fib(x) << std::endl;
        TestUtils::end_stop_watch();
    }

    TestUtils::time_result(500);
    TestUtils::end_clear_track_time();

}

int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);

    TestUtils::end_testing();

    return 0;
}