# Add all source files under src/
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Create executable named 'exec'
add_executable(exec ${SOURCES})

# Include the libraries directory if needed
target_include_directories(exec PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/../libraries/eigen/
${CMAKE_CURRENT_SOURCE_DIR}/../libraries)

# Link all libraries in the libraries directory
file(GLOB LIBRARY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../libraries/*.cpp")
foreach(LIBRARY_SRC ${LIBRARY_SOURCES})
    get_filename_component(LIB_NAME ${LIBRARY_SRC} NAME_WE)
    target_link_libraries(exec ${LIB_NAME})
endforeach()

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include SDL2 headers
target_include_directories(exec PUBLIC ${SDL2_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(exec ${SDL2_LIBRARIES})

