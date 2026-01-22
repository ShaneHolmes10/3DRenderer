# Tests

# Excluded tests (if any)
set(excluded_tests "")

# Add all tests matching test*.cpp pattern
projectAddTestsGlob(
    tests 
    "test*.cpp" 
    "${excluded_tests}" 
    "3drenderer_lib"
)