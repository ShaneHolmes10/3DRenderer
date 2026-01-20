#include <iostream>
#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include <vector>
#include <Eigen/Dense>
#include <random>



/*
    
*/
void test_1() {

    int size = 100;
    int lower_bound = 0;
    int upper_bound = 255;

    std::vector<int> R_channel_start = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);
    std::vector<int> G_channel_start = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);
    std::vector<int> B_channel_start = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);

    std::vector<int> R_channel_end = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);
    std::vector<int> G_channel_end = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);
    std::vector<int> B_channel_end = TestUtils::generate_random_vector_std(size, lower_bound, upper_bound);

    int N = 10000;


    TestUtils::start_stop_watch();
    for(int ind = 0; ind < size; ind++) {
        TestMeth::color_interpolation(
            {
                R_channel_start[ind], 
                G_channel_start[ind], 
                B_channel_start[ind]
            }, {
                R_channel_end[ind], 
                G_channel_end[ind],
                B_channel_end[ind]
            }, N);
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