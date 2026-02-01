project(3drenderer LANGUAGES CXX)

# We split the library into separate subfolders, each containing
# tests and an optional convenience library.
# The following variable is the master list of subdirs to add
set(3drenderer_subdirs
    math
    camera
    utils
    representations
)

set(3drenderer_srcs)

# To exclude a source from the library build (in any subfolder)
# Add the full name to this list, as in the following example
# Sources to remove from builds
set(excluded_sources "")

set(excluded_headers "")

# Common headers
file(GLOB 3drenderer_core_headers "*.h")
install(FILES ${3drenderer_core_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/3DRenderer)

# Assemble core libraries
foreach(subdir ${3drenderer_subdirs})
    # Build convenience libraries
    file(GLOB_RECURSE subdir_srcs "${subdir}/*.cpp" "${subdir}/*.h") # Include header files so they show up in Visual Studio
    list(REMOVE_ITEM subdir_srcs ${excluded_sources})
    file(GLOB subdir_test_files "${subdir}/tests/*")
    list(REMOVE_ITEM subdir_srcs ${subdir_test_files}) # Remove test files from sources compiled into library
    set(${subdir}_srcs ${subdir_srcs})

    # Build local library and tests
    message(STATUS "Building ${subdir}")
    add_subdirectory(${subdir})
endforeach(subdir)

# To add additional sources to 3drenderer when building the full library (static or shared)
# append the subfolder with _srcs appended to the end to this list
set(3drenderer_srcs)
foreach(subdir ${3drenderer_subdirs})
    list(APPEND 3drenderer_srcs ${${subdir}_srcs})
endforeach(subdir)
list(APPEND 3drenderer_srcs ${3drenderer_core_headers})

# Versions
set(3drenderer_version   ${RENDERER_VERSION_STRING})
set(3drenderer_soversion ${RENDERER_VERSION_MAJOR})
message(STATUS "3DRenderer Version: ${3drenderer_version}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

# Build shared and static versions of the library
message(STATUS "Building 3DRenderer - as a STATIC library")

# BUILD_SHARED_LIBS automatically defines static/shared libs
# Here we ensure we control which type of library 3drenderer is specifically
add_library(3drenderer_lib STATIC ${3drenderer_srcs})
target_link_libraries(3drenderer_lib PUBLIC Eigen3::Eigen)
target_link_libraries(3drenderer_lib PUBLIC 
    sfml-graphics
    sfml-window
    sfml-system
    ${X11_LIBRARIES}
    Threads::Threads
)

set_target_properties(3drenderer_lib PROPERTIES
    OUTPUT_NAME         3drenderer
    CLEAN_DIRECT_OUTPUT 1
    VERSION             ${3drenderer_version}
    SOVERSION           ${3drenderer_soversion}
    LINKER_LANGUAGE     CXX)

# Add includes for source directories 'BEFORE' boost and any system include
# paths so that the compiler uses 3DRenderer headers in our source directory instead
# of any previously installed 3DRenderer headers.
target_include_directories(3drenderer_lib BEFORE PUBLIC
  # main 3drenderer includes:
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/3DRenderer>
  $<INSTALL_INTERFACE:include/>
)

if(WIN32) # Add 'lib' prefix to static library to avoid filename collision with shared library
    set_target_properties(3drenderer_lib PROPERTIES PREFIX "lib")
endif()

install(
    TARGETS 3drenderer_lib
    EXPORT 3DRenderer-exports
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

list(APPEND RENDERER_EXPORTED_TARGETS 3drenderer_lib)
set(RENDERER_EXPORTED_TARGETS "${RENDERER_EXPORTED_TARGETS}" PARENT_SCOPE)