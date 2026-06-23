#include <CppUnitLite/TestHarness.h>

#include <fstream>

#include "forms/mesh.h"
#include "load_obj_file.h"

void create_test_obj_file(const std::string& filename,
                          const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

void delete_test_file(const std::string& filename) {
    std::remove(filename.c_str());
}

TEST(ObjLoader, LoadSimpleTriangle) {
    std::string filename = "test_triangle.obj";
    std::string content =
        "v 0.0 0.0 0.0\n"
        "v 1.0 0.0 0.0\n"
        "v 0.5 1.0 0.0\n"
        "f 1 2 3\n";

    create_test_obj_file(filename, content);

    LoadObjFile loader;
    Mesh m1 = loader.load(filename);

    CHECK_EQUAL(3, m1.getVertexCount());
    CHECK_EQUAL(1, m1.getFaceCount());

    delete_test_file(filename);
}

TEST(ObjLoader, LoadTetrahedron) {
    std::string filename =
        std::string(SRC_DIR) + "/data/tetrahedron.obj";

    LoadObjFile loader;
    Mesh m1 = loader.load(filename);

    CHECK_EQUAL(4, m1.getVertexCount());
    CHECK_EQUAL(4, m1.getFaceCount());
}

int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}