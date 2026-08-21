#include <Eigen/Dense>

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

    struct TriangleUniform {};
    TriangleUniform uniform;
    FragmentShader<TriangleUniform> vertex_color_shader = [](const TriangleUniform&,
                                                      const Varying& varying) {
        return varying.color;
    };

    rasterize(triangle, uniform, vertex_color_shader, buffers);

    view.start();
    view.setFrame(fb);

    while (true) {
        view.update();
    }

    view.join();
    return 0;
}
