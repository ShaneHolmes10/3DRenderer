#include <Eigen/Dense>
#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"
#include "display/viewport.h"
#include "forms/entity.h"
#include "forms/mesh.h"
#include "forms/model.h"
#include "renderer/camera.h"
#include "renderer/types.h"
#include "utils/load_cobj_file.h"
#include "utils/transform.h"

struct Varying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector3f color    = Eigen::Vector3f::Zero();
    VARYING(position, color)
};

struct SceneUniform {
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f view  = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f proj  = Eigen::Matrix4f::Identity();
};

int main() {
    Viewport::init();

    int width  = 800;
    int height = 600;
    Viewport view(width, height, 100, 100);

    Entity world;

    Entity tetrahedron_entity;
    Model tetrahedron_model;
    LoadCobjFile loader;
    std::string filename = std::string(SRC_DIR) + "/data/icosahedron.cobj";
    tetrahedron_model.addMesh(loader.load(filename));
    tetrahedron_entity.model = &tetrahedron_model;

    Transform t_tetra(Eigen::Vector3f(0, 30, 0), Eigen::Vector3f::Zero(),
                      Eigen::Vector3f(150, 150, 150));
    tetrahedron_entity.setTransform(t_tetra);

    world.addChild(tetrahedron_entity);

    Entity camera_mount;
    world.addChild(camera_mount);

    Camera camera;
    camera.attachTo(camera_mount);
    camera.setFovLength(250);
    camera.setPictureWidthHeight(width, height);

    Program<SceneUniform, Varying> program;
    program.vertex_shader = [](const SceneUniform&,
                                const VertexAttributes& v) {
        Varying out;
        out.position = Eigen::Vector4f(v.position.x(), v.position.y(),
                                       v.position.z(), 1.0f);
        out.color    = v.color.cast<float>();
        return out;
    };
    program.fragment_shader = [](const SceneUniform&, const Varying& v) {
        return v.color.cast<int>();
    };

    Options options;
    options.cull_mode = CullMode::None;

    view.start();

    FrameBuffer frame_buffer(width, height);
    DepthBuffer depth_buffer(width, height);

    float angle = 0;
    while (true) {
        float orbit_radius = 300.0f;
        float theta        = angle * 0.05f;

        float cam_x = orbit_radius * std::sin(theta);
        float cam_y = 50.0f;
        float cam_z = orbit_radius * std::cos(theta);

        float rotation_y = theta + static_cast<float>(M_PI);

        Transform t_cam(Eigen::Vector3f(cam_x, cam_y, cam_z),
                        Eigen::Vector3f(0, rotation_y, 0));
        camera_mount.setTransform(t_cam);

        frame_buffer.clear();
        depth_buffer.clear();

        Buffers buffers{frame_buffer, depth_buffer};
        camera.draw(&tetrahedron_entity, program, options, buffers);

        view.setFrame(frame_buffer);
        view.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        angle += 1.0f;
    }

    std::cout << "Animation complete. Close window to exit.\n";
    view.join();

    return 0;
}
