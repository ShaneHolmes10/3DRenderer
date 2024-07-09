#include <iostream>
#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include <vector>
#include <Eigen/Dense>
#include <random>


/*
    Measure the time it takes to 
*/
void test_1() {

    int size = 3*3000;
    int lower_bound = -100;
    int upper_bound = 100;

    std::vector<int> x1_list = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);
    std::vector<int> y1_list = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);
    std::vector<int> x2_list = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);
    std::vector<int> y2_list = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);


    TestUtils::start_stop_watch();
    for(int ind = 0; ind < size-1; ind++) {
        
        TestMeth::Bresenham(x1_list[ind], y1_list[ind], x2_list[ind], y2_list[ind]);
        
    }
    TestUtils::end_stop_watch();

    TestUtils::time_result(50);
    

}


int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}