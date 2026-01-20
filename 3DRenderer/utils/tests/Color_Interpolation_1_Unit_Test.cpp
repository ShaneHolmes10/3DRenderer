#include <iostream>
#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include <vector>
#include <Eigen/Dense>
#include <random>


/*
    
*/
void test_1() {

    std::vector<std::array<int, 3>> compare = {
        {210, 42, 57},
        {184, 57, 79},
        {158, 72, 101},
        {131, 87, 123},
        {105, 102, 144},
        {79, 117, 166},
        {52, 132, 188},
        {26, 147, 210}
    };

    
    int N = 10;
    std::array<int, 3> start_1 = {237, 28, 36};
    std::array<int, 3> end_1 = {0, 162, 232};

    TestUtils::pass_or_fail_printout(
        compare == TestMeth::color_interpolation(start_1, end_1, N)
    );
}


int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}