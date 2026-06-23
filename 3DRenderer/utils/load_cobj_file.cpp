#include "load_cobj_file.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

Mesh LoadCobjFile::load(const std::string& filepath) {
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

            float r;
            float g;
            float b;
            if (iss >> r >> g >> b) {
                vertex.color =
                    Eigen::Vector3i(static_cast<int>(r * 255),
                                    static_cast<int>(g * 255),
                                    static_cast<int>(b * 255));
            }

            vertices.push_back(vertex);
        } else if (prefix == "f") {
            Face face;
            iss >> face.v1 >> face.v2 >> face.v3;
            face.v1--;
            face.v2--;
            face.v3--;
            faces.push_back(face);
        }
    }

    return {vertices, faces};
}