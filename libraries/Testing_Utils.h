

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
#include <chrono>
#include <vector>
#include <random>

namespace TestUtils {

/*
    Tracking Variables
*/

int test_counter_testUtils = 1;
int correct_counter_testUtils = 0;

std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> start_testUtils;
std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> end_testUtils;

double total_time_testUtils;

bool is_track_time_testUtils;
std::vector<double> time_tracker_testUtils;

/*
    Comparisons
*/

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

/*
    Generation
*/

inline std::vector<int> generate_random_vector_std(int n, int A, int B) {
    // Initialize random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(A, B);

    // Generate random vector
    std::vector<int> vec;
    for (int i = 0; i < n; ++i) {
        vec.push_back(dis(gen));
    }
    return vec;
}

/*
    Timing
*/
inline void start_track_time() {
    is_track_time_testUtils = true;

}

inline void end_clear_track_time() {
    is_track_time_testUtils = false;
    time_tracker_testUtils.clear();

}

inline void start_stop_watch() {
    start_testUtils = std::chrono::high_resolution_clock::now();

}

inline void end_stop_watch() {
    end_testUtils = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_testUtils - start_testUtils);
    total_time_testUtils = duration.count();

    if(is_track_time_testUtils) {
        time_tracker_testUtils.push_back(total_time_testUtils);
    }

}

inline void time_result(float maximum_allowable_time_ms) {
    if(total_time_testUtils <= maximum_allowable_time_ms) {
        std::cout << GREEN << "[TEST SUCCESSFUL]" << RESET << std::endl;
        correct_counter_testUtils++;
    } else {
        std::cout << RED << "[TEST FAILED]" << RESET << std::endl;
    }
    
    std::cout << "Time taken: " << total_time_testUtils << " ms" << std::endl;
    std::cout << "Allowed time: " << maximum_allowable_time_ms << " ms" << std::endl;
    
    if(is_track_time_testUtils) {
        for (size_t i = 0; i < time_tracker_testUtils.size(); ++i) {
            std::cout << time_tracker_testUtils[i];
            if (i != time_tracker_testUtils.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
}


/*
    Support Code
*/

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
