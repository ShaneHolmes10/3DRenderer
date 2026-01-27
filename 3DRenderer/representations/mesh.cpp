#include "mesh.h"

Mesh::Mesh(
    std::vector<Vertex> vertices, 
    std::vector<Face> indicies
    ) : vertices(vertices), faces(indicies) {

}

const std::vector<Vertex>& Mesh::getVertices() const {
    return vertices;
}


const std::vector<Face>& Mesh::getFaces() const {
    return indicies;
}

size_t Mesh::getVertexCount() const {
    return vertices.size();
}

size_t Mesh::getFaceCount() const {
    return indicies.size()
}
