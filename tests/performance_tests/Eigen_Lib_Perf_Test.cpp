#include <iostream>
#include <Eigen/Dense>

/*
This test serves to verify that the performance tests directory is capable of seeing the eigan library
*/

int main() {
    std::cout << "PERFORMANCE TEST *STARTED*" << std::endl;
    std::cout << "TEST 1" << std::endl;
    std::cout << "We're just seeing if the program will crash" << std::endl;
    Eigen::MatrixXd A(2,2);
    Eigen::MatrixXd B(2,2);
    A << 1, 2, 3, 4;
    B << 5, 6, 7, 8;
    Eigen::MatrixXd C = A * B;
    std::cout << "A * B =\n" << C << std::endl;
    std::cout << "PERFORMANCE TEST *COMPLETED*" << std::endl;
    return 0;
}


