#include <Eigen/Dense>

#include "CppUnitLite/TestHarness.h"
#include "renderer/rasterizer/rasterizer.h"
#include "renderer/rasterizer/types.h"

Eigen::Vector3i getPixel(const FrameBuffer& fb, size_t x, size_t y) {
    size_t idx = (y * fb.width + x) * 4;
    return Eigen::Vector3i(fb.pixels[idx], fb.pixels[idx + 1],
                           fb.pixels[idx + 2]);
}

TEST(Rasterizer, InterpolatesVertexColors) {
    const size_t size = 500;

    FrameBuffer fb(size, size);
    DepthBuffer db(size, size);
    Buffers buffers{fb, db};

    // Red at top-left, green at top-right, blue at bottom
    Varying v0;
    v0.position = Eigen::Vector4f(100.0f, 100.0f, 0.0f, 1.0f);
    v0.color    = Eigen::Vector3i(255, 0, 0);

    Varying v1;
    v1.position = Eigen::Vector4f(350.0f, 100.0f, 0.0f, 1.0f);
    v1.color    = Eigen::Vector3i(0, 255, 0);

    Varying v2;
    v2.position = Eigen::Vector4f(250.0f, 400.0f, 0.0f, 1.0f);
    v2.color    = Eigen::Vector3i(0, 0, 255);

    RasterTriangle triangle{v0, v1, v2};

    Uniform uniform;
    Shader vertex_color_shader = [](const Uniform&, const Varying& varying) {
        return varying.color;
    };

    rasterize(triangle, uniform, vertex_color_shader, buffers);

    // Vertices should be close to their assigned colors
    CHECK(getPixel(fb, 100, 100) == Eigen::Vector3i(255, 0, 0));  // v0 — red
    CHECK(getPixel(fb, 350, 100) == Eigen::Vector3i(0, 255, 0));  // v1 — green
    CHECK(getPixel(fb, 250, 400) == Eigen::Vector3i(0, 0, 255));  // v2 — blue

    // Outside triangle should be untouched (black)
    CHECK(getPixel(fb, 0, 0) == Eigen::Vector3i(0, 0, 0));
}

int main() {
    TestResult tr;
    TestRegistry::runAllTests(tr);
    return 0;
}
