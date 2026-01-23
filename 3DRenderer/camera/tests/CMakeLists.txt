# Excluded tests (if any)
set(excluded_tests "")

# Add all tests from this directory
projectAddTestsGlob(
    camera_tests 
    "test*.cpp" 
    "${excluded_tests}" 
    "3drenderer_lib"
)