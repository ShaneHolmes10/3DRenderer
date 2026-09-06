#pragma once

#include <Eigen/Dense>

#include "renderer/types.h"

/**
 * @brief Default interpolated vertex data for standard color rendering.
 */
struct DefaultVarying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector3f color = Eigen::Vector3f::Zero();
    VARYING(position, color)
};
