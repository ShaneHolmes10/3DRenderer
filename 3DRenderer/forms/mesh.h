
#pragma once

#include <Eigen/Dense>
#include <vector>

/**
 * @brief Represents a single vertex in 3D space.
 * 
 * Contains position and color information for a vertex.
 */
struct Vertex {
    Eigen::Vector3f position;
    Eigen::Vector3d color;
    // Eigen::Vector3f normal;
    // Eigen::Vector2f TexCoords;
};

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
 * @brief Represents a 3D mesh composed of vertices and faces.
 * 
 * A Mesh is a collection of vertices and triangular faces that define
 * 3D geometry. The class ensures data integrity by validating face
 * indices when faces are added.
 */
class Mesh {


private:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;


public:

    /**
     * @brief Construct an empty Mesh.
     */
    Mesh() = default;

    /**
     * @brief Construct a Mesh with vertices and faces.
     * 
     * @param vertices Vector of vertices
     * @param faces Vector of faces (triangles)
     */
    Mesh(
        const std::vector<Vertex>& vertices,
        const std::vector<Face>& faces
    );

    // Getters for data access

    /**
     * @brief Get all vertices in the mesh.
     * 
     * @return const reference to the vertex vector
     */
    const std::vector<Vertex>& getVertices() const;

    /**
     * @brief Get all faces in the mesh.
     * 
     * @return const reference to the face vector
     */
    const std::vector<Face>& getFaces() const;
    
    // utility methods

    /**
     * @brief Get the number of vertices in the mesh.
     * 
     * @return Number of vertices
     */
    size_t getVertexCount() const;

    /**
     * @brief Get the number of faces in the mesh.
     * 
     * @return Number of faces
     */
    size_t getFaceCount() const;

    // Adder

    /**
     * @brief Add a vertex to the mesh.
     * 
     * @param vert Vertex to add
     */
    void addVertex(const Vertex& vert);

    /**
     * @brief Add a face to the mesh.
     * 
     * Validates that all vertex indices reference existing vertices.
     * 
     * @param face Face to add
     * @throws std::out_of_range if any vertex index is invalid
     */
    void addFace(const Face& face);

};
