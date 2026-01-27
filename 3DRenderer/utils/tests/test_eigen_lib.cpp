#include <CppUnitLite/TestHarness.h>
#include <Eigen/Dense>


TEST(EigenLib, MatrixMultiplication) {
    Eigen::MatrixXd A(2, 2);
    Eigen::MatrixXd B(2, 2);
    
    A << 1, 2, 3, 4;
    B << 5, 6, 7, 8;
    
    Eigen::MatrixXd C = A * B;
    
    // Expected result: [19, 22; 43, 50]
    CHECK_EQUAL(19, C(0, 0));
    CHECK_EQUAL(22, C(0, 1));
    CHECK_EQUAL(43, C(1, 0));
    CHECK_EQUAL(50, C(1, 1));
}


TEST(EigenLib, MatrixCreation) {
    Eigen::MatrixXd M(3, 3);
    M << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    
    CHECK_EQUAL(1, M(0, 0));
    CHECK_EQUAL(5, M(1, 1));
    CHECK_EQUAL(9, M(2, 2));
}


int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}