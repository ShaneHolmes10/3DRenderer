# Examples

# Get all example files
file(GLOB example_files "*.cpp")

# Create an executable for each example file
foreach(example_file IN ITEMS ${example_files})
    # Get example name from filename
    get_filename_component(example_name ${example_file} NAME_WE)
    
    # Add executable
    add_executable(${example_name} ${example_file})
    
    # Link against the 3drenderer library
    target_link_libraries(${example_name} 3drenderer_lib)
    
    # Set output directory
    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
    )
    
    # Add to examples target
    add_dependencies(examples ${example_name})
    
    message(STATUS "Added example: ${example_name}")
endforeach()