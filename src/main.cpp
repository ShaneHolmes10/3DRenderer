#include <iostream>
#include <Eigen/Dense>

int main() {
    Eigen::MatrixXd A(2,2);
    Eigen::MatrixXd B(2,2);
    A << 1, 2, 3, 4;
    B << 5, 6, 7, 8;
    Eigen::MatrixXd C = A * B;
    std::cout << "A * B =\n" << C << std::endl;
    return 0;
}
