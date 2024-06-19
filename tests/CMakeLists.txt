cmake_minimum_required(VERSION 3.10)
project(3DRendererTests)

#Link Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#Enable testing
enable_testing()

#Function to add tests from a given directory
function(add_tests_from_directory test_type)
file(GLOB_RECURSE TEST_SOURCES ${test_type}/*.cpp)
if(TEST_SOURCES)
add_executable(run${test_type}Tests ${TEST_SOURCES})
target_link_libraries(run${test_type}Tests gtest gtest_main Fibonacci)
add_test(NAME run${test_type}Tests COMMAND run${test_type}Tests)
endif()
endfunction()

#Add unit tests
option(BUILD_UNIT_TESTS "Build unit tests" ON)
if(BUILD_UNIT_TESTS)
add_tests_from_directory(unit)
endif()

#Add integration tests
option(BUILD_INTEGRATION_TESTS "Build integration tests" ON)
if(BUILD_INTEGRATION_TESTS)
add_tests_from_directory(integration)
endif()

#Add performance tests
option(BUILD_PERFORMANCE_TESTS "Build performance tests" ON)
if(BUILD_PERFORMANCE_TESTS)
add_tests_from_directory(performance)
endif()
