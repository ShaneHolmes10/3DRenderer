###############################################################################
# Find X11

# Find X11 (required for multi-threaded SFML on Linux)
find_package(X11 REQUIRED)

if(NOT X11_FOUND)
    message(FATAL_ERROR "X11 not found. Please install X11 development libraries (libx11-dev on Debian/Ubuntu).")
endif()

# X11 libraries found
if(X11_LIBRARIES)
    message(STATUS "Found X11 libraries: ${X11_LIBRARIES}")
else()
    message(STATUS "Found X11")
endif()