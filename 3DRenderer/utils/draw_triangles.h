#pragma once

#include "display/frame_buffer.h"
#include <Eigen/Dense>

struct Triangle2 {

    Eigen::Vector2f vertex_A;
    Eigen::Vector2f vertex_B;
    Eigen::Vector2f vertex_C;

    Eigen::Vector3i color_A;
    Eigen::Vector3i color_B;
    Eigen::Vector3i color_C;

};

void drawTriangle(FrameBuffer& frame_buffer, const Triangle2& triangle);

float signedTriangleArea(const Eigen::Vector2f& A, const Eigen::Vector2f& B, const Eigen::Vector2f& C);