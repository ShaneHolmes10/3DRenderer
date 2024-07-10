#include <Eigen/Dense>
#include <iostream>

#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include "Reference_Frame.h"
#include "Vector_Object.h"




// std::array<int, 3> start_1 = {237, 28, 36};
// std::array<int, 3> end_1 = {0, 162, 232};
// std::array<int, 3> start_1 = {34, 177, 76};


int main() {
    
    int N = 14;
    std::array<int, 3> start_1 = {0, 162, 232};
    std::array<int, 3> end_1 = {34, 177, 76};

    
    std::vector<std::array<int, 3>> values = TestMeth::color_interpolation(start_1, end_1, N);

    for(int x = 0; x < N-2; x++) {
        std::cout << values[0][x] << ", " << values[1][x] << ", " << values[2][x] << "\n";
    }

    return 0;
}

