#include "CppUnitLite/TestHarness.h"
#include "forms/mesh.h"
#include <Eigen/Dense>


TEST(Mesh, ConstructWithVerticesAndFaces)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 0, 255)});
    
    std::vector<Face> faces;
    faces.push_back(Face{0, 1, 2});
    
    Mesh mesh(verts, faces);
    
    CHECK(mesh.getVertexCount() == 3);
    CHECK(mesh.getFaceCount() == 1);
}


TEST(Mesh, ConstructEmptyMesh)
{
    std::vector<Vertex3> verts;
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    CHECK(mesh.getVertexCount() == 0);
    CHECK(mesh.getFaceCount() == 0);
}


TEST(Mesh, GetVerticesReturnsCorrectData)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 2.0f, 3.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(4.0f, 5.0f, 6.0f), Eigen::Vector3i(0, 255, 0)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    const std::vector<Vertex3>& retrievedVerts = mesh.getVertices();
    
    CHECK(retrievedVerts.size() == 2);
    CHECK((retrievedVerts[0].position - Eigen::Vector3f(1.0f, 2.0f, 3.0f)).norm() < 0.01);
    CHECK((retrievedVerts[1].position - Eigen::Vector3f(4.0f, 5.0f, 6.0f)).norm() < 0.01);
}


TEST(Mesh, GetFacesReturnsCorrectData)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 0, 255)});
    
    std::vector<Face> faces;
    faces.push_back(Face{0, 1, 2});
    faces.push_back(Face{2, 1, 0});
    
    Mesh mesh(verts, faces);
    
    const std::vector<Face>& retrievedFaces = mesh.getFaces();
    
    CHECK(retrievedFaces.size() == 2);
    CHECK(retrievedFaces[0].v1 == 0);
    CHECK(retrievedFaces[0].v2 == 1);
    CHECK(retrievedFaces[0].v3 == 2);
    CHECK(retrievedFaces[1].v1 == 2);
    CHECK(retrievedFaces[1].v2 == 1);
    CHECK(retrievedFaces[1].v3 == 0);
}


TEST(Mesh, AddVertexIncreasesCount)
{
    std::vector<Vertex3> verts;
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    Vertex3 v{Eigen::Vector3f(1.0f, 2.0f, 3.0f), Eigen::Vector3i(255, 0, 0)};
    mesh.addVertex(v);
    
    CHECK(mesh.getVertexCount() == 1);
}


TEST(Mesh, AddMultipleVertices)
{
    std::vector<Vertex3> verts;
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    mesh.addVertex(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    mesh.addVertex(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    mesh.addVertex(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 1.0f), Eigen::Vector3i(0, 0, 255)});
    
    CHECK(mesh.getVertexCount() == 3);
}


TEST(Mesh, AddedVertexIsRetrievable)
{
    std::vector<Vertex3> verts;
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    Vertex3 v{Eigen::Vector3f(7.0f, 8.0f, 9.0f), Eigen::Vector3i(128, 128, 128)};
    mesh.addVertex(v);
    
    const std::vector<Vertex3>& retrievedVerts = mesh.getVertices();
    
    CHECK((retrievedVerts[0].position - Eigen::Vector3f(7.0f, 8.0f, 9.0f)).norm() < 0.01);
    CHECK(retrievedVerts[0].color == Eigen::Vector3i(128, 128, 128));
}


TEST(Mesh, AddFaceWithValidIndices)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 0, 255)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    mesh.addFace(Face{0, 1, 2});
    
    CHECK(mesh.getFaceCount() == 1);
}


TEST(Mesh, AddMultipleFaces)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 0, 255)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 1.0f, 0.0f), Eigen::Vector3i(255, 255, 0)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    mesh.addFace(Face{0, 1, 2});
    mesh.addFace(Face{1, 3, 2});
    
    CHECK(mesh.getFaceCount() == 2);
}


TEST(Mesh, AddedFaceIsRetrievable)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 0, 255)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    mesh.addFace(Face{0, 1, 2});
    
    const std::vector<Face>& retrievedFaces = mesh.getFaces();
    
    CHECK(retrievedFaces[0].v1 == 0);
    CHECK(retrievedFaces[0].v2 == 1);
    CHECK(retrievedFaces[0].v3 == 2);
}


TEST(Mesh, AddFaceWithNegativeIndexThrows)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    bool exceptionThrown = false;
    try {
        mesh.addFace(Face{-1, 0, 0});
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    
    CHECK(exceptionThrown);
}


TEST(Mesh, AddFaceWithOutOfBoundsIndexThrows)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    bool exceptionThrown = false;
    try {
        mesh.addFace(Face{0, 1, 5});  // Index 5 doesn't exist
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    
    CHECK(exceptionThrown);
}


TEST(Mesh, VertexColorPersistence)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 0, 255)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    const std::vector<Vertex3>& retrievedVerts = mesh.getVertices();
    
    CHECK(retrievedVerts[0].color == Eigen::Vector3i(255, 0, 0));
    CHECK(retrievedVerts[1].color == Eigen::Vector3i(0, 255, 0));
    CHECK(retrievedVerts[2].color == Eigen::Vector3i(0, 0, 255));
}


TEST(Mesh, CreateCubeMesh)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(-1.0f, -1.0f, -1.0f), Eigen::Vector3i(0, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f( 1.0f, -1.0f, -1.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f( 1.0f,  1.0f, -1.0f), Eigen::Vector3i(255, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(-1.0f,  1.0f, -1.0f), Eigen::Vector3i(0, 255, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(-1.0f, -1.0f,  1.0f), Eigen::Vector3i(0, 0, 255)});
    verts.push_back(Vertex3{Eigen::Vector3f( 1.0f, -1.0f,  1.0f), Eigen::Vector3i(255, 0, 255)});
    verts.push_back(Vertex3{Eigen::Vector3f( 1.0f,  1.0f,  1.0f), Eigen::Vector3i(255, 255, 255)});
    verts.push_back(Vertex3{Eigen::Vector3f(-1.0f,  1.0f,  1.0f), Eigen::Vector3i(0, 255, 255)});
    
    std::vector<Face> faces;
    faces.push_back(Face{0, 1, 2});
    faces.push_back(Face{0, 2, 3});
    faces.push_back(Face{1, 5, 6});
    faces.push_back(Face{1, 6, 2});
    faces.push_back(Face{5, 4, 7});
    faces.push_back(Face{5, 7, 6});
    faces.push_back(Face{4, 0, 3});
    faces.push_back(Face{4, 3, 7});
    faces.push_back(Face{3, 2, 6});
    faces.push_back(Face{3, 6, 7});
    faces.push_back(Face{4, 5, 1});
    faces.push_back(Face{4, 1, 0});
    
    Mesh cube(verts, faces);
    
    CHECK(cube.getVertexCount() == 8);
    CHECK(cube.getFaceCount() == 12);
}


TEST(Mesh, MixConstructionAndAdding)
{
    std::vector<Vertex3> verts;
    verts.push_back(Vertex3{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3i(255, 0, 0)});
    verts.push_back(Vertex3{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3i(0, 255, 0)});
    
    std::vector<Face> faces;
    
    Mesh mesh(verts, faces);
    
    mesh.addVertex(Vertex3{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3i(0, 0, 255)});
    mesh.addFace(Face{0, 1, 2});
    
    CHECK(mesh.getVertexCount() == 3);
    CHECK(mesh.getFaceCount() == 1);
}

int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}