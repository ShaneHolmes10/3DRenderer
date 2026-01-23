###############################################################################
# Find SFML

# Find SFML with required components
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found. Please install SFML 2.5 or later.")
endif()

# Get version
if(SFML_VERSION)
    set(RENDERER_SFML_VERSION "${SFML_VERSION}")
else()
    set(RENDERER_SFML_VERSION "Unknown")
endif()

message(STATUS "Found SFML version: ${RENDERER_SFML_VERSION}")
message(STATUS "  SFML Graphics: ${SFML_GRAPHICS_LIBRARY}")
message(STATUS "  SFML Window:   ${SFML_WINDOW_LIBRARY}")
message(STATUS "  SFML System:   ${SFML_SYSTEM_LIBRARY}")