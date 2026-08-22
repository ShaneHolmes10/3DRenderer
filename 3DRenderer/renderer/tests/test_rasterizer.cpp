#include <Eigen/Dense>
#include <array>
#include <cmath>

#include "CppUnitLite/TestHarness.h"
#include "renderer/rasterizer/rasterizer.h"
#include "renderer/types.h"

Eigen::Vector3i getPixel(const FrameBuffer& fb, size_t x, size_t y) {
    size_t idx = (y * fb.width + x) * 4;
    return {fb.pixels[idx], fb.pixels[idx + 1], fb.pixels[idx + 2]};
}

struct Varying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector3f color    = Eigen::Vector3f::Zero();
    VARYING(position, color)
};

struct TestUniform {};

TEST(Rasterizer, InterpolatesVertexColors) {
    const size_t size = 500;

    FrameBuffer fb(size, size);
    DepthBuffer db(size, size);
    Buffers buffers{fb, db};

    // Red at top-left, green at top-right, blue at bottom
    Varying v0;
    v0.position = Eigen::Vector4f(100.0f, 100.0f, 0.0f, 1.0f);
    v0.color = Eigen::Vector3f(255, 0, 0);

    Varying v1;
    v1.position = Eigen::Vector4f(350.0f, 100.0f, 0.0f, 1.0f);
    v1.color = Eigen::Vector3f(0, 255, 0);

    Varying v2;
    v2.position = Eigen::Vector4f(250.0f, 400.0f, 0.0f, 1.0f);
    v2.color = Eigen::Vector3f(0, 0, 255);

    std::array<Varying, 3> triangle{v0, v1, v2};

    TestUniform uniform;
    FragmentShader<TestUniform, Varying> vertex_color_shader =
        [](const TestUniform&, const Varying& varying) {
            return varying.color.cast<int>();
        };

    rasterize(triangle, uniform, vertex_color_shader, buffers);

    // Vertices should be close to their assigned colors
    CHECK(getPixel(fb, 100, 100) ==
          Eigen::Vector3i(255, 0, 0));  // v0 — red
    CHECK(getPixel(fb, 350, 100) ==
          Eigen::Vector3i(0, 255, 0));  // v1 — green
    CHECK(getPixel(fb, 250, 400) ==
          Eigen::Vector3i(0, 0, 255));  // v2 — blue

    // Outside triangle should be untouched (white — framebuffer
    // default)
    CHECK(getPixel(fb, 0, 0) == Eigen::Vector3i(255, 255, 255));
}

TEST(Rasterizer, DrawsCircleWithProceduralShader) {
    const size_t size = 500;
    const float cx = size / 2.0f;
    const float cy = size / 2.0f;
    const float radius = 100.0f;

    FrameBuffer fb(size, size);
    DepthBuffer db(size, size);
    Buffers buffers{fb, db};

    // Two triangles covering the full canvas
    Varying v0;
    Varying v1;
    Varying v2;
    Varying v3;
    Varying v4;
    Varying v5;
    v0.position = Eigen::Vector4f(0, 0, 0.0f, 1.0f);
    v1.position = Eigen::Vector4f(size, 0, 0.0f, 1.0f);
    v2.position = Eigen::Vector4f(0, size, 0.0f, 1.0f);
    v3.position = Eigen::Vector4f(size, 0, 0.0f, 1.0f);
    v4.position = Eigen::Vector4f(size, size, 0.0f, 1.0f);
    v5.position = Eigen::Vector4f(0, size, 0.0f, 1.0f);

    std::array<Varying, 3> upper{v0, v1, v2};
    std::array<Varying, 3> lower{v3, v4, v5};

    TestUniform uniform;
    FragmentShader<TestUniform, Varying> circle_shader =
        [&](const TestUniform&, const Varying& varying) {
            float x = varying.position.x();
            float y = varying.position.y();
            float dist =
                std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
            return dist < radius ? Eigen::Vector3i(0, 0, 0)
                                 : Eigen::Vector3i(255, 255, 255);
        };

    rasterize(upper, uniform, circle_shader, buffers);
    rasterize(lower, uniform, circle_shader, buffers);

    CHECK(getPixel(fb, 250, 250) ==
          Eigen::Vector3i(0, 0, 0));  // center — inside
    CHECK(getPixel(fb, 349, 250) ==
          Eigen::Vector3i(0, 0, 0));  // distance 99 — inside
    CHECK(getPixel(fb, 351, 250) ==
          Eigen::Vector3i(255, 255, 255));  // distance 101 — outside
    CHECK(getPixel(fb, 0, 0) ==
          Eigen::Vector3i(255, 255, 255));  // far corner — outside
}

int main() {
    TestResult tr;
    TestRegistry::runAllTests(tr);
    return 0;
}
