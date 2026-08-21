#include <Eigen/Dense>
#include <algorithm>
#include <array>
#include <cmath>

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"
#include "display/viewport.h"
#include "renderer/rasterizer/rasterizer.h"
#include "renderer/types.h"

int main() {
    Viewport::init();

    const int width  = 500;
    const int height = 500;
    Viewport view(width, height, 100, 100);

    FrameBuffer fb(width, height);
    DepthBuffer db(width, height);
    Buffers buffers{fb, db};

    // Two triangles covering the full canvas so the shader
    // can paint every pixel procedurally
    Varying v0, v1, v2, v3, v4, v5;
    v0.position = Eigen::Vector4f(0,     0,      0.0f, 1.0f);
    v1.position = Eigen::Vector4f(width, 0,      0.0f, 1.0f);
    v2.position = Eigen::Vector4f(0,     height, 0.0f, 1.0f);
    v3.position = Eigen::Vector4f(width, 0,      0.0f, 1.0f);
    v4.position = Eigen::Vector4f(width, height, 0.0f, 1.0f);
    v5.position = Eigen::Vector4f(0,     height, 0.0f, 1.0f);

    std::array<Varying, 3> upper{v0, v1, v2};
    std::array<Varying, 3> lower{v3, v4, v5};

    struct SmileyUniform {};
    SmileyUniform uniform;
    FragmentShader<SmileyUniform> circle_shader = [&](const SmileyUniform&,
                                               const Varying& varying) {
        // Normalize to [-0.5, 0.5] centered UV coordinates
        float u =  varying.position.x() / width  - 0.5f;
        float v = -varying.position.y() / height + 0.5f;
        Eigen::Vector2f uv(u, v);

        auto smoothstep = [](float edge0, float edge1, float x) {
            float t = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
            return t * t * (3.0f - 2.0f * t);
        };

        auto circle = [&](Eigen::Vector2f center, float r, float blur) {
            return smoothstep(r, r - blur, (uv - center).norm());
        };

        // Face
        float mask = circle({0.0f, 0.0f}, 0.4f, 0.05f);

        // Eyes
        mask -= circle({-0.13f,  0.2f}, 0.07f, 0.01f);
        mask -= circle({ 0.13f,  0.2f}, 0.07f, 0.01f);

        // Mouth (crescent = big circle minus shifted circle)
        float mouth  = circle({0.0f,  0.0f}, 0.3f, 0.02f);
        mouth       -= circle({0.0f,  0.1f}, 0.3f, 0.02f);
        mask -= mouth;

        mask = std::clamp(mask, 0.0f, 1.0f);

        // Yellow face on black background
        return Eigen::Vector3i(
            static_cast<int>(255.0f * mask),
            static_cast<int>(255.0f * mask),
            0
        );
    };

    rasterize(upper, uniform, circle_shader, buffers);
    rasterize(lower, uniform, circle_shader, buffers);

    view.start();
    view.setFrame(fb);

    while (true) {
        view.update();
    }

    view.join();
    return 0;
}
