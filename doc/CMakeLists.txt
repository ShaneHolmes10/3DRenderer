###############################################################################
# Doxygen documentation

find_package(Doxygen REQUIRED)

# Configure Doxygen file
set(DOXYGEN_INPUT_DIR "${CMAKE_SOURCE_DIR}/3DRenderer")
set(DOXYGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/docs")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    @ONLY
)

# Add custom target to build documentation
add_custom_target(docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)

message(STATUS "Doxygen documentation target 'docs' created")
message(STATUS "  Run 'make docs' to generate documentation")
message(STATUS "  Output will be in: ${DOXYGEN_OUTPUT_DIR}")