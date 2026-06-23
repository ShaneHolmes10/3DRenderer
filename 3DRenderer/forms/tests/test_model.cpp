#include <Eigen/Dense>

#include "CppUnitLite/TestHarness.h"
#include "forms/mesh.h"
#include "forms/model.h"

TEST(Model, DefaultConstructor) {
    Model model;

    CHECK(model.getMeshes().empty());
}

TEST(Model, ConstructWithMeshes) {
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f),
                            Eigen::Vector3i(1.0, 0.0, 0.0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f),
                            Eigen::Vector3i(0.0, 1.0, 0.0)});
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f),
                            Eigen::Vector3i(0.0, 0.0, 1.0)});

    std::vector<Face> faces;
    faces.push_back(Face{0, 1, 2});

    Mesh mesh1(verts, faces);
    Mesh mesh2(verts, faces);

    std::vector<Mesh> meshes;
    meshes.push_back(mesh1);
    meshes.push_back(mesh2);

    Model model(meshes);

    CHECK(model.getMeshes().size() == 2);
}

TEST(Model, GetMeshesReturnsCorrectData) {
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 2.0f, 3.0f),
                            Eigen::Vector3i(1.0, 0.0, 0.0)});

    std::vector<Face> faces;

    Mesh mesh(verts, faces);

    std::vector<Mesh> meshes;
    meshes.push_back(mesh);

    Model model(meshes);

    const std::vector<Mesh>& retrievedMeshes = model.getMeshes();

    CHECK(retrievedMeshes.size() == 1);
    CHECK(retrievedMeshes[0].getVertexCount() == 1);
}

TEST(Model, LoadSingleMesh) {
    std::string filename =
        std::string(SRC_DIR) + "/data/tetrahedron.obj";

    Model model;
    model.loadMesh(filename);

    CHECK(model.getMeshes().size() == 1);
}

TEST(Model, LoadedMeshHasCorrectData) {
    std::string filename =
        std::string(SRC_DIR) + "/data/tetrahedron.obj";

    Model model;
    model.loadMesh(filename);

    const std::vector<Mesh>& meshes = model.getMeshes();

    CHECK(meshes.size() == 1);
    CHECK(meshes[0].getVertexCount() == 4);
    CHECK(meshes[0].getFaceCount() == 4);
}

TEST(Model, LoadMultipleMeshes) {
    std::string filename =
        std::string(SRC_DIR) + "/data/tetrahedron.obj";

    Model model;
    model.loadMesh(filename);
    model.loadMesh(filename);

    CHECK(model.getMeshes().size() == 2);
}

TEST(Model, LoadMultipleMeshesEachHasCorrectData) {
    std::string filename =
        std::string(SRC_DIR) + "/data/tetrahedron.obj";

    Model model;
    model.loadMesh(filename);
    model.loadMesh(filename);

    const std::vector<Mesh>& meshes = model.getMeshes();

    CHECK(meshes.size() == 2);
    CHECK(meshes[0].getVertexCount() == 4);
    CHECK(meshes[0].getFaceCount() == 4);
    CHECK(meshes[1].getVertexCount() == 4);
    CHECK(meshes[1].getFaceCount() == 4);
}

TEST(Model, ConstructWithMeshesAndLoadMore) {
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f),
                            Eigen::Vector3i(1.0, 0.0, 0.0)});

    std::vector<Face> faces;

    Mesh mesh(verts, faces);

    std::vector<Mesh> meshes;
    meshes.push_back(mesh);

    Model model(meshes);

    std::string filename =
        std::string(SRC_DIR) + "/data/tetrahedron.obj";
    model.loadMesh(filename);

    CHECK(model.getMeshes().size() == 2);
}

TEST(Model, EmptyModelGetMeshesReturnsEmptyVector) {
    Model model;

    const std::vector<Mesh>& meshes = model.getMeshes();

    CHECK(meshes.empty());
}

TEST(Model, ConstructedModelPreservesOriginalMeshData) {
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 2.0f, 3.0f),
                            Eigen::Vector3i(1.0, 0.0, 0.0)});
    verts.push_back(Vertex3{Eigen::Vector3f(4.0f, 5.0f, 6.0f),
                            Eigen::Vector3i(0.0, 1.0, 0.0)});

    std::vector<Face> faces;
    faces.push_back(Face{0, 1, 0});

    Mesh originalMesh(verts, faces);

    std::vector<Mesh> meshes;
    meshes.push_back(originalMesh);

    Model model(meshes);

    const Mesh& retrievedMesh = model.getMeshes()[0];

    CHECK(retrievedMesh.getVertexCount() == 2);
    CHECK(retrievedMesh.getFaceCount() == 1);

    const std::vector<Vertex3>& retrievedVerts =
        retrievedMesh.getVertices();
    CHECK(
        (retrievedVerts[0].position - Eigen::Vector3f(1.0f, 2.0f, 3.0f))
            .norm() < 0.01);
    CHECK(
        (retrievedVerts[1].position - Eigen::Vector3f(4.0f, 5.0f, 6.0f))
            .norm() < 0.01);
}

int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}