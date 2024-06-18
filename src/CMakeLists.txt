# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Add executable
add_executable(3DRenderer ${SOURCES})

# Link SDL2 library
target_link_libraries(3DRenderer ${SDL2_LIBRARIES})

# Make sources available for other targets
add_library(renderer_lib ${SOURCES})
target_link_libraries(renderer_lib ${SDL2_LIBRARIES})

