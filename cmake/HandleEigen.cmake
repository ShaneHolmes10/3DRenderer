###############################################################################
# Find Eigen3

# Find Eigen3 using config mode
find_package(Eigen3 CONFIG REQUIRED)

if(NOT TARGET Eigen3::Eigen)
    message(FATAL_ERROR "Eigen3 not found. Please install Eigen3.")
endif()

# Get version
if(EIGEN3_VERSION)
    set(RENDERER_EIGEN_VERSION "${EIGEN3_VERSION}")
else()
    set(RENDERER_EIGEN_VERSION "Unknown")
endif()

message(STATUS "Found Eigen version: ${RENDERER_EIGEN_VERSION}")