# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name for performance tests
project(PerformanceTests)

# Glob all test source files in this directory
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Create an executable for performance tests
add_executable(performance_tests_exec ${TEST_SOURCES})

# Include directories for headers from libraries and src
target_include_directories(performance_tests_exec PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries)
target_include_directories(performance_tests_exec PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

# Optionally, link libraries from libraries directory
file(GLOB LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/*.cpp")
target_link_libraries(performance_tests_exec ${LIBRARY_SOURCES})

# Set C++ standard if needed
# set_property(TARGET performance_tests_exec PROPERTY CXX_STANDARD 11)

# Add tests to CTest (optional)
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_test(NAME ${test_name} COMMAND performance_tests_exec --gtest_filter=${test_name}:*)
endforeach()

