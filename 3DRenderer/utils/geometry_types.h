#pragma once

#include <Eigen/Dense>

/**
 * @brief Represents a single vertex with a position and color.
 *
 * Templated on PositionType so the same struct covers both 2D screen-space
 * vertices (Vertex2 = Vertex<Eigen::Vector2f>) and 3D world/camera-space
 * vertices (Vertex3 = Vertex<Eigen::Vector3f>).
 */
template<typename PositionType>
struct Vertex {
    PositionType    position = PositionType::Zero();
    Eigen::Vector3i color    = Eigen::Vector3i(0, 0, 0);
};

using Vertex2 = Vertex<Eigen::Vector2f>;
using Vertex3 = Vertex<Eigen::Vector3f>;

/**
 * @brief Represents a triangular face using vertex indices.
 *
 * A face references three vertices by their indices in the mesh's
 * vertex array.
 */
struct Face {
    int v1, v2, v3;
};

/**
 * @brief A triangle defined by three vertices.
 *
 * Templated on PositionType to cover both 2D screen-space triangles
 * (Triangle2 = Triangle<Eigen::Vector2f>) and 3D camera-space triangles
 * (Triangle3 = Triangle<Eigen::Vector3f>).
 */
template<typename PositionType>
struct Triangle {
    Vertex<PositionType> vertex_A, vertex_B, vertex_C;
};

/**
 * @brief A triangle defined by three vertices with additional fields for depth information.
 *
 * This struct inherits from the Triangle struct so it contains the same 
 * fields as that but with the addition of the depth information per vertex.  
 */
template<typename PositionType>
struct DepthTriangle : Triangle<PositionType> {
    float vertex_a_inverse_z, vertex_b_inverse_z, vertex_c_inverse_z;
};

using Triangle2 = DepthTriangle<Eigen::Vector2f>;
using Triangle3 = Triangle<Eigen::Vector3f>;
