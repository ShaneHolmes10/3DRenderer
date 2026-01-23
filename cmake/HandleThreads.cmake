# Find Threads
find_package(Threads REQUIRED)

if(NOT Threads_FOUND)
    message(FATAL_ERROR "Threads not found.")
endif()

message(STATUS "Found Threads")