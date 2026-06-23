
#include "forms/mesh.h"

#include <stdexcept>

Mesh::Mesh(const std::vector<Vertex3>& vertices,
           const std::vector<Face>& faces)
    : vertices(vertices), faces(faces) {}

const std::vector<Vertex3>& Mesh::getVertices() const {
    return vertices;
}

const std::vector<Face>& Mesh::getFaces() const { return faces; }

size_t Mesh::getVertexCount() const { return vertices.size(); }

size_t Mesh::getFaceCount() const { return faces.size(); }

void Mesh::addVertex(const Vertex3& vert) { vertices.push_back(vert); }

void Mesh::addFace(const Face& face) {
    size_t vertCount = getVertexCount();

    if (face.v1 < 0 || face.v2 < 0 || face.v3 < 0 ||
        face.v1 >= vertCount || face.v2 >= vertCount ||
        face.v3 >= vertCount) {
        throw std::out_of_range(
            "Vertex3 referenced by face does not exist");
    }

    faces.push_back(face);
}
