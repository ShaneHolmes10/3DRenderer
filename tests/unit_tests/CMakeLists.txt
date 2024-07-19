# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name for unit tests
project(UnitTests)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Glob all test source files in this directory
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Include directories for headers from libraries and src
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SFML_INCLUDE_DIR})

# Optionally, link libraries from libraries directory
file(GLOB LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/*.cpp")

# Source files from src directory, excluding main.cpp
file(GLOB SRC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.cpp")
list(REMOVE_ITEM SRC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../../src/main.cpp")

# Set the output directory for unit test executables
set(TEST_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unit_tests)

# Iterate through each test source file
foreach(test_source ${TEST_SOURCES})
    # Get the base name of the test (without extension)
    get_filename_component(test_name ${test_source} NAME_WE)

    # Create an executable for each test file
    add_executable(${test_name} ${test_source} ${SRC_SOURCES})

    # Link the executable with the necessary libraries
    target_link_libraries(${test_name} ${LIBRARY_SOURCES} ${SDL2_LIBRARIES} sfml-system sfml-window sfml-graphics)

    # Set the output directory for the executable
    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR})

    # Set C++ standard if needed
    # set_property(TARGET ${test_name} PROPERTY CXX_STANDARD 11)

    # Add tests to CTest (optional)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

