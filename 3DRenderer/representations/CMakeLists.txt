# Install headers
file(GLOB representation_headers "*.h")
install(FILES ${math_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/3DRenderer/representations)

# Build tests (if tests subdirectory exists)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests AND IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    add_subdirectory(tests)
endif()