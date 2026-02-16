
#include "load_data_file.h"
#include "forms/mesh.h"

/**
 * @brief Loads mesh data from Wavefront OBJ files.
 * 
 * This class implements the LoadDataFile interface to parse and load
 * 3D mesh data from OBJ format files. Currently supports vertices and
 * triangular faces.
 */
class LoadCobjFile : public LoadDataFile {

public:

    /**
     * @brief Load a mesh from an OBJ file.
     * 
     * @param filepath Path to the OBJ file
     * @return Mesh object containing the loaded geometry
     * @throws std::runtime_error if file cannot be opened or parsed
     */
    Mesh load(const std::string& filepath) override;

};
