cmake_minimum_required(VERSION 3.10)
project(3DRenderer)

#Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Copy entire files directory to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/files DESTINATION ${CMAKE_BINARY_DIR})

#Add Google Test subdirectory
add_subdirectory(googletest)

#Subdirectories
add_subdirectory(libraries)
add_subdirectory(src)
add_subdirectory(tests)
