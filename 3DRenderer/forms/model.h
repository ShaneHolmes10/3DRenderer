
#pragma once

#include <string>
#include <vector>

#include "mesh.h"

/**
 * @brief Represents a 3D model containing one or more meshes.
 *
 * A Model is a container for meshes that can be loaded from files
 * or constructed programmatically. Multiple meshes can be added to
 * a single model.
 */
class Model {
   private:
    std::vector<Mesh> meshes;

   public:
    /**
     * @brief Construct an empty Model.
     */
    Model() = default;

    /**
     * @brief Construct a Model with a collection of meshes.
     *
     * @param meshes Vector of meshes to initialize the model with
     */
    Model(const std::vector<Mesh>& meshes);

    /**
     * @brief Load a mesh from a file and add it to the model.
     *
     * @param filepath Path to the mesh file (e.g., OBJ file)
     * @throws std::runtime_error if file cannot be loaded or parsed
     */
    void loadMesh(const std::string& filepath);

    /**
     * @brief Get all meshes in the model.
     *
     * @return const reference to the vector of meshes
     */
    const std::vector<Mesh>& getMeshes() const;

    /**
     * @brief Add a mesh to the model.
     *
     * @param mesh Mesh to add
     */
    void addMesh(const Mesh& mesh);
};
