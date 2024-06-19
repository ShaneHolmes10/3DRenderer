# Get all source files in the libraries directory
file(GLOB LIBRARY_SOURCES "*.cpp")

foreach(LIBRARY_SRC ${LIBRARY_SOURCES})
    get_filename_component(LIB_NAME ${LIBRARY_SRC} NAME_WE)
    add_library(${LIB_NAME} STATIC ${LIBRARY_SRC})
    target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

