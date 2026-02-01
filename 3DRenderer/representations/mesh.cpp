
#include "representations/mesh.h"
#include <stdexcept>

Mesh::Mesh(
    const std::vector<Vertex>& vertices, 
    const std::vector<Face>& indicies
    ) : vertices(vertices), faces(indicies) {

}

const std::vector<Vertex>& Mesh::getVertices() const {
    return vertices;
}

const std::vector<Face>& Mesh::getFaces() const {
    return faces;
}

size_t Mesh::getVertexCount() const {
    return vertices.size();
}

size_t Mesh::getFaceCount() const {
    return faces.size();
}

void Mesh::addVertex(const Vertex& vert) {
    vertices.push_back(vert);
}


void Mesh::addFace(const Face& face) {

    size_t vertCount = getVertexCount();

    if(
        face.v1 < 0 ||
        face.v2 < 0 ||
        face.v3 < 0 ||
        face.v1 >= vertCount ||
        face.v2 >= vertCount ||
        face.v3 >= vertCount 
    ) {
        throw std::out_of_range("Vertex referenced by face does not exist");
    }

    faces.push_back(face);
}
