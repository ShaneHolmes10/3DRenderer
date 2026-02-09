#include "CppUnitLite/TestHarness.h"
#include "forms/entity.h"
#include <Eigen/Dense>


/*!SECTION
Test an entity with a model 
Test an entity without a model



*/


TEST(Entity, )
{
    std::vector<Vertex> verts;
    verts.push_back(Vertex{Eigen::Vector3f(0.0f, 0.0f, 0.0f), Eigen::Vector3d(1.0, 0.0, 0.0)});
    verts.push_back(Vertex{Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3d(0.0, 1.0, 0.0)});
    verts.push_back(Vertex{Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3d(0.0, 0.0, 1.0)});
    
    std::vector<Face> faces;
    faces.push_back(Face{0, 1, 2});
    
    Mesh mesh(verts, faces);
    
    CHECK(mesh.getVertexCount() == 3);
    CHECK(mesh.getFaceCount() == 1);
}


int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}
