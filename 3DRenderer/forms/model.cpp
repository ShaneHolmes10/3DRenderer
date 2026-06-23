
#include "forms/model.h"

#include "utils/load_obj_file.h"  // Should really use a generic loader in the future

Model::Model(const std::vector<Mesh>& meshes) : meshes(meshes) {}

void Model::loadMesh(const std::string& filepath) {
    LoadObjFile loader;
    meshes.push_back(loader.load(filepath));
}

const std::vector<Mesh>& Model::getMeshes() const { return meshes; }

void Model::addMesh(const Mesh& mesh) { meshes.push_back(mesh); }
