
#include "load_obj_file.h"

#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>

Mesh LoadObjFile::load(const std::string& filepath) {
    std::vector<Vertex3> vertices;
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
            Vertex3 vertex;
            iss >> vertex.position.x() >> vertex.position.y() >>
                vertex.position.z();
            vertices.push_back(vertex);
        } else if (prefix == "f") {
            std::array<int, 3> indices{};
            for (int& index : indices) {
                std::string token;
                iss >> token;
                index = std::stoi(token) - 1;
            }
            faces.push_back({indices[0], indices[1], indices[2]});
        }
    }

    return {vertices, faces};
}
