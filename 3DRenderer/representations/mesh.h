
#pragma once

#include <Eigen/Dense>
#include <vector>


struct Vertex {
    Eigen::Vector3f position;
    // Eigen::Vector3f normal;
    // Eigen::Vector2f TexCoords;
};

struct Face {
    int v1, v2, v3;
};

class Mesh {

private:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;


public:

    Mesh(
        std::vector<Vertex> vertices,
        std::vector<Face> faces
        // vector<Texture> textures
    );

    // Getters for data access
    const std::vector<Vertex>& getVertices() const;
    const std::vector<Face>& getFaces() const;
    
    // Maybe utility methods
    size_t getVertexCount() const;
    size_t getFaceCount() const;

};
