# Build CppUnitLite
file(GLOB cppunitlite_headers "*.h")
file(GLOB cppunitlite_src "*.cpp")

add_library(CppUnitLite STATIC ${cppunitlite_src} ${cppunitlite_headers})

# Make headers available
target_include_directories(CppUnitLite PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

list(APPEND RENDERER_EXPORTED_TARGETS CppUnitLite)
set(RENDERER_EXPORTED_TARGETS "${RENDERER_EXPORTED_TARGETS}" PARENT_SCOPE)