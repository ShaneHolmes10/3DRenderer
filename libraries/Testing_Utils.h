

#ifndef TESTING_UTILS_H
#define TESTING_UTILS_H

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#include <Eigen/Dense>
#include <iostream>

namespace TestUtils {

int test_counter_testUtils = 1;
int correct_counter_testUtils = 0;

inline bool check_matrix_3_similarity(const Eigen::Matrix3d& m1, const Eigen::Matrix3d& m2) {

    return ( 0.1 > (m1 - m2).norm()) ;
}

inline bool check_matrix_4_similarity(const Eigen::Matrix4d& m1, const Eigen::Matrix4d& m2) {

    return ( 0.1 > (m1 - m2).norm()) ;
}

inline bool check_vector_3_similarity(const Eigen::Vector3d& v1, const Eigen::Vector3d& v2) {

    return ( 0.1 > (v1 - v2).norm()) ;
}

inline bool check_std_vector_similarity(const std::vector<int>& v1, const std::vector<int>& v2) {

    return v1 == v2;
}

inline void pass_or_fail_printout(bool value) {
    if(value) {
        std::cout << GREEN << "[TEST SUCCESSFUL]" << RESET << std::endl;
        correct_counter_testUtils++;
    } else {
        std::cout << RED << "[TEST FAILED]" << RESET << std::endl;

    }
}

inline void start_testing() {
    std::cout << CYAN << "********************" << RESET << std::endl;
    std::cout << BLUE << "[TESTING STARTED]" << RESET << std::endl;
    std::cout << CYAN << "********************" << RESET << std::endl;
}

inline void perform_test(std::function<void(void)> func) {
    std::cout << BLUE << "**TEST " << test_counter_testUtils << "**" << RESET << std::endl;
    func();
    test_counter_testUtils++;
}

inline void end_testing() {
    std::cout << CYAN << "********************" << RESET << std::endl;
    std::cout << BLUE << "[TESTING ENDED]" << RESET << std::endl;
    std::cout << "TEST RESULTS " << correct_counter_testUtils << " / " << test_counter_testUtils-1 << std::endl;
    std::cout << CYAN << "********************" << RESET << std::endl;
}

} 

#endif 
