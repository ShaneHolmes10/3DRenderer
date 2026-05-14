#pragma once

#include "forms/mesh.h"
#include "display/frame_buffer.h"
#include <Eigen/Dense>

template<typename PositionType>
struct Triangle {
    Vertex<PositionType> vertex_A, vertex_B, vertex_C;
};

using Triangle2 = Triangle<Eigen::Vector2f>;
using Triangle3 = Triangle<Eigen::Vector3f>;

void drawTriangle(FrameBuffer& frame_buffer, const Triangle2& triangle);

float signedTriangleArea(const Eigen::Vector2f& A, const Eigen::Vector2f& B, const Eigen::Vector2f& C);
