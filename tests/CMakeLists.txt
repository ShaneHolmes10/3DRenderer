# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Test source files
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Add test executable
add_executable(3DRendererTests ${TEST_SOURCES})

# Link test executable against renderer_lib
target_link_libraries(3DRendererTests renderer_lib)

