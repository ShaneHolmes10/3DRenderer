# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name for unit tests
project(UnitTests)

# Glob all test source files in this directory
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Iterate through each test source file
foreach(test_source ${TEST_SOURCES})
    # Get the base name of the test (without extension)
    get_filename_component(test_name ${test_source} NAME_WE)

    # Create an executable for each test file
    add_executable(${test_name} ${test_source})

    # Include directories for headers from libraries and src
    target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries)
    target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

    # Optionally, link libraries from libraries directory
    file(GLOB LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/*.cpp")
    target_link_libraries(${test_name} ${LIBRARY_SOURCES})

    # Set C++ standard if needed
    # set_property(TARGET ${test_name} PROPERTY CXX_STANDARD 11)

    # Add tests to CTest (optional)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

