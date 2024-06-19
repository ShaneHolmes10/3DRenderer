# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name for tests
project(3DRendererTests)

# Add each type of tests
add_subdirectory(unit_tests)
add_subdirectory(integration_tests)
add_subdirectory(performance_tests)

