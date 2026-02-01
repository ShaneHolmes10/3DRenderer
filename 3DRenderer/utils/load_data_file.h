#pragma once

#include "representations/mesh.h"
#include <string>

/**
 * @brief Abstract base class for loading 3D model data from files.
 * 
 * This class defines the interface for file loaders that read various
 * 3D model formats and convert them into Mesh objects. Concrete
 * implementations should handle specific file formats (OBJ, STL, etc.).
 */
class LoadDataFile {

public:

    /**
     * @brief Virtual destructor.
     */
    virtual ~LoadDataFile() = default;

    /**
     * @brief Load a mesh from a file.
     * 
     * Pure virtual function that must be implemented by derived classes
     * to handle specific file formats.
     * 
     * @param filepath Path to the model file
     * @return Mesh object containing the loaded geometry
     * @throws std::runtime_error if file cannot be loaded or parsed
     */
    virtual Mesh load(const std::string& filepath) = 0;

};


