
#include "load_obj_file.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Mesh LoadObjFile::load(const std::string& filepath) {
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        
        if (prefix == "v") {
            Vertex vertex;
            iss >> vertex.position.x() >> vertex.position.y() >> vertex.position.z();
            vertices.push_back(vertex);
        }
        else if (prefix == "f") {
            Face face;
            iss >> face.v1 >> face.v2 >> face.v3;
            // OBJ indices are 1-based, convert to 0-based
            face.v1--;
            face.v2--;
            face.v3--;
            faces.push_back(face);
        }
    }
    
    return Mesh(vertices, faces);
}
