cmake_minimum_required(VERSION 3.10)

# Set the version number for the library
set(RENDERER_VERSION_MAJOR 1)
set(RENDERER_VERSION_MINOR 0)
set(RENDERER_VERSION_PATCH 0)
set(RENDERER_VERSION_STRING "${RENDERER_VERSION_MAJOR}.${RENDERER_VERSION_MINOR}.${RENDERER_VERSION_PATCH}")

project(3DRenderer
        LANGUAGES CXX
        VERSION "${RENDERER_VERSION_MAJOR}.${RENDERER_VERSION_MINOR}.${RENDERER_VERSION_PATCH}")

###############################################################################
# Gather information, perform checks, set defaults

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

# Load build type flags and default to Debug mode
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()


include(ProjectTesting)

# Add examples target
add_custom_target(examples)

# Build options
option(BUILD_EXAMPLES "Build examples" ON)

###############################################################################
# Handle dependencies

include(HandleEigen)
include(HandleSFML)
include(HandleX11)
include(HandleThreads)

###############################################################################
# Add components

# Build main library
add_subdirectory(3DRenderer)

# Build examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Build tests
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

###############################################################################
# Print configuration variables
include(HandlePrintConfiguration)