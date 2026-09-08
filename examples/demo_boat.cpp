#include "display/viewport.h"
#include "display/frame_buffer.h"
#include "display/depth_buffer.h"
#include "renderer/camera.h"
#include "forms/entity.h"
#include "forms/model.h"
#include "forms/mesh.h"
#include "utils/transform.h"
#include "utils/load_cobj_file.h"
#include "utils/load_texture.h"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>


// Create water related pipeline data structures
struct WaterUniform {
    const FrameBuffer* texture = nullptr;
    float time;
    Eigen::Matrix4f view_inverse;
}; 

struct WaterVarying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector2f uv = Eigen::Vector2f::Zero();
    VARYING(position, uv)
};

VertexShader<WaterUniform, WaterVarying> water_vertex_shader =
    [](const WaterUniform& u, const VertexAttributes& v) {
        WaterVarying out;

        const float amplitude = 30.0f;
        const float frequency = 0.02f;
        float wave_y = amplitude * std::sin(v.position.x() * frequency + u.time) *
                       std::cos(v.position.z() * frequency * 0.7f + u.time);

        out.position = Eigen::Vector4f(
            v.position.x(), v.position.y() + wave_y, v.position.z(), 1.0f);

        Eigen::Vector4f world_pos =
            u.view_inverse *
            Eigen::Vector4f(v.position.x(), v.position.y(), v.position.z(), 1.0f);
        const float uv_scale = 200.0f;
        out.uv = Eigen::Vector2f(world_pos.x() / uv_scale, world_pos.z() / uv_scale);

        return out;
    };


FragmentShader<WaterUniform, WaterVarying> water_fragment_shader =
    [](const WaterUniform& u, const WaterVarying& v) -> Eigen::Vector3i {
    float u_coord = v.uv.x() - std::floor(v.uv.x());
    float v_coord = v.uv.y() - std::floor(v.uv.y());

    size_t x = static_cast<size_t>(u_coord * (u.texture->width - 1));
    size_t y = static_cast<size_t>(v_coord * (u.texture->height - 1));

    size_t idx = (y * u.texture->width + x) * 4;
    return {u.texture->pixels[idx], u.texture->pixels[idx + 1],
            u.texture->pixels[idx + 2]};
};


// Generate grid mesh dynamically
Mesh build_grid(int n, float size) {
    Mesh mesh;
    float half = size / 2.0f;
    float step = size / n;

    for (int row = 0; row <= n; row++) {
        for (int col = 0; col <= n; col++) {
            Vertex3 v;
            v.position = Eigen::Vector3f(
                -half + col * step, 0.0f, -half + row * step);
            v.color = Eigen::Vector3i(255, 255, 255);
            mesh.addVertex(v);
        }
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int tl = row * (n + 1) + col;
            int tr = tl + 1;
            int bl = tl + (n + 1);
            int br = bl + 1;
            mesh.addFace({tl, bl, tr});
            mesh.addFace({tr, bl, br});
        }
    }

    return mesh;
}

int main() {

    // Initialize Viewport
    Viewport::init();

    int width = 1600;
    int height = 1200;
    Viewport view(width, height, 100, 100);

    // Create the world entity, root of the scene graph
    Entity world;


    // Create the water
    Entity water_entity;
    Model water_model;

    water_model.addMesh(build_grid(50, 5000.0f));
    water_entity.model = &water_model;

    water_entity.setTransform(
        Transform(
            Eigen::Vector3f(0, 0, 0),
            Eigen::Vector3f::Zero(),
            Eigen::Vector3f::Ones()
        )
    );

    world.addChild(water_entity);


    // Create the camera mount
    Entity camera_mount;
    world.addChild(camera_mount);

    Camera camera;
    camera.attachTo(camera_mount);
    camera.setFovLength(250);
    camera.setPictureWidthHeight(width, height);

    // Set initial camera mount position
    float cam_x = 0.0f;
    float cam_y = -150.0f;
    float cam_z = 300.0f;

    float rotation_x =  0.0f;
    float rotation_y =  M_PI;
    float rotation_z =  0.0f;

    float move_speed = 10.0f;
    float rotate_speed = 0.1f;

    // Set the key value callback
    view.setKeyCallback([&](Key key) {
        switch(key) {
            case W:  // Move forward
                cam_x += move_speed * std::sin(rotation_y);
                cam_z += move_speed * std::cos(rotation_y);
                break;
            case S:  // Move backward
                cam_x -= move_speed * std::sin(rotation_y);
                cam_z -= move_speed * std::cos(rotation_y);
                break;
            case D:  // Strafe right
                cam_x += move_speed * std::cos(rotation_y);
                cam_z -= move_speed * std::sin(rotation_y);
                break;
            case A:  // Strafe left
                cam_x -= move_speed * std::cos(rotation_y);
                cam_z += move_speed * std::sin(rotation_y);
                break;
            case Q:  // Move up
                cam_y += move_speed;
                break;
            case E:  // Move down
                cam_y -= move_speed;
                break;
            case Left:  // Rotate left
                rotation_y -= rotate_speed;
                break;
            case Right:  // Rotate right
                rotation_y += rotate_speed;
                break;
            case Up:  // Look up
                rotation_x += rotate_speed;
                break;
            case Down:  // Look down
                rotation_x -= rotate_speed;
                break;
            default:
                break;
        }
    });

    // Start the viewport
    view.start();

    FrameBuffer water_texture = load_texture(
        std::string(SRC_DIR) + "/data/textures/water_texture.jpg");

    Program<WaterUniform, WaterVarying> program;
    program.vertex_shader = water_vertex_shader;
    program.fragment_shader = water_fragment_shader;
    program.uniform.texture = &water_texture;

    Options options;
    options.cull_mode = CullMode::CounterClockwise;

    float time = 0.0f;

    // Define data buffers
    FrameBuffer frame_buffer(width, height);
    DepthBuffer depth_buffer(width, height);

    // Action loop
    while(true) {

        Transform t_cam(Eigen::Vector3f(cam_x, cam_y, cam_z),
                        Eigen::Vector3f(rotation_x, rotation_y, rotation_z));

        camera_mount.setTransform(t_cam);

        frame_buffer.clear();
        depth_buffer.clear();

        Buffers buffers{frame_buffer, depth_buffer};

        program.uniform.time = time;
        program.uniform.view_inverse = camera_mount.getWorldMatrix();
        time += 0.05f;

        camera.draw(&water_entity, program, options, buffers);

        view.setFrame(frame_buffer);
        view.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    view.join();

    return 0;
}
