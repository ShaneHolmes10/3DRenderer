cmake_minimum_required(VERSION 3.10)
project(3DRenderer)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify build output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

