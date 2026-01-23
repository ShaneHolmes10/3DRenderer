# This file defines macros for easily adding groups of tests for the project.

###############################################################################
# Macro: projectAddTestsGlob
#
# Add a group of unit tests. Tests are assigned into a group name so they can
# easily be run independently with a make target. Running 'make check' builds
# and runs all tests.
#
# Usage example:
#   projectAddTestsGlob(unit_tests "*.cpp" "" "3drenderer_lib")
#
# Arguments:
#   groupName:     A name for this group of tests (e.g., 'unit_tests')
#   globPatterns:  File glob patterns (e.g., "*.cpp" or "*Unit_Test.cpp")
#   excludedFiles: Files to exclude (e.g., "testBroken.cpp"), use "" for none
#   linkLibraries: Libraries to link against (e.g., "3drenderer_lib")
macro(projectAddTestsGlob groupName globPatterns excludedFiles linkLibraries)
    # Add group target if it doesn't already exist
    if(NOT TARGET check.${groupName})
        add_custom_target(check.${groupName} 
            COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
            COMMENT "Running ${groupName} tests"
        )
    endif()

    # Get all test files matching the pattern
    file(GLOB test_files ${globPatterns})

    # Remove excluded files from the list
    if(NOT "${excludedFiles}" STREQUAL "")
        file(GLOB excludedFilePaths ${excludedFiles})
        if(NOT "${excludedFilePaths}" STREQUAL "")
            list(REMOVE_ITEM test_files ${excludedFilePaths})
        endif()
    endif()

    # Create an executable for each test file
    foreach(test_file IN ITEMS ${test_files})
        # Get test name from filename
        get_filename_component(test_name ${test_file} NAME_WE)

        # Add executable
        add_executable(${test_name} ${test_file})
        
        # Link libraries
        target_link_libraries(${test_name} ${linkLibraries})

        # Include directories
        target_include_directories(${test_name} PRIVATE
            ${CMAKE_SOURCE_DIR}/3DRenderer/math
            ${CMAKE_SOURCE_DIR}/3DRenderer/camera
            ${CMAKE_SOURCE_DIR}/3DRenderer/utils
        )

        # Register with CTest
        add_test(NAME ${test_name} COMMAND ${test_name})

        # Add dependencies
        add_dependencies(check.${groupName} ${test_name})
        add_dependencies(check ${test_name})

        # Set output directory
        set_target_properties(${test_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${groupName}
        )

        # Exclude from 'make all'
        set_target_properties(${test_name} PROPERTIES EXCLUDE_FROM_ALL ON)
    endforeach()
endmacro()


###############################################################################
# Setup testing

# Enable CTest
enable_testing()

# Add option for building tests
option(BUILD_TESTS "Enable/Disable building of tests" ON)

# Create main 'check' target that runs all tests
if(BUILD_TESTS)
    add_custom_target(check 
        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
        COMMENT "Running all tests"
    )
endif()