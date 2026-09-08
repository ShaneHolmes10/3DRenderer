#include "display/viewport.h"
#include "display/frame_buffer.h"
#include "display/depth_buffer.h"
#include "renderer/camera.h"
#include "forms/entity.h"
#include "forms/model.h"
#include "forms/mesh.h"
#include "utils/transform.h"
#include "utils/load_cobj_file.h"
#include "utils/load_obj_file.h"
#include "utils/load_texture.h"
#include <Eigen/Dense>
#include <array>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>


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


struct BoatUniform {
    const FrameBuffer* texture = nullptr;
};

struct BoatVarying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector2f uv = Eigen::Vector2f::Zero();
    VARYING(position, uv)
};

Mesh load_boat_mesh(const std::string& path) {
    std::vector<Eigen::Vector3f> raw_verts;
    std::vector<std::array<int, 3>> raw_faces;

    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "v") {
            Eigen::Vector3f pos;
            iss >> pos.x() >> pos.y() >> pos.z();
            raw_verts.push_back(pos);
        } else if (prefix == "f") {
            std::array<int, 3> f;
            for (int i = 0; i < 3; i++) {
                std::string token;
                iss >> token;
                f[i] = std::stoi(token) - 1;
            }
            raw_faces.push_back(f);
        }
    }

    Eigen::Vector3f centroid = Eigen::Vector3f::Zero();
    for (auto& p : raw_verts) centroid += p;
    centroid /= static_cast<float>(raw_verts.size());
    for (auto& p : raw_verts) p -= centroid;

    const Eigen::Vector3i uv_slots[3] = {
        {0, 0, 0}, {255, 0, 0}, {0, 255, 0}};

    Mesh mesh;
    int idx = 0;
    for (auto& f : raw_faces) {
        for (int i = 0; i < 3; i++) {
            Vertex3 v;
            v.position = raw_verts[f[i]];
            v.color = uv_slots[i];
            mesh.addVertex(v);
        }
        mesh.addFace({idx, idx + 1, idx + 2});
        idx += 3;
    }
    return mesh;
}

VertexShader<BoatUniform, BoatVarying> boat_vertex_shader =
    [](const BoatUniform&, const VertexAttributes& v) {
        BoatVarying out;
        out.position = Eigen::Vector4f(
            v.position.x(), v.position.y(), v.position.z(), 1.0f);
        out.uv = Eigen::Vector2f(
            v.color.x() / 255.0f, v.color.y() / 255.0f);
        return out;
    };

FragmentShader<BoatUniform, BoatVarying> boat_fragment_shader =
    [](const BoatUniform& u, const BoatVarying& v) -> Eigen::Vector3i {
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

    Entity boat;
    Entity hull;
    Model hull_model;
    hull_model.addMesh(load_boat_mesh(std::string(SRC_DIR) + "/data/simple_boat.obj"));
    hull.model = &hull_model;
    hull.setTransform(Transform(
        Eigen::Vector3f(0, 0, 0),
        Eigen::Vector3f(M_PI / 2, 0, 0),
        Eigen::Vector3f(70, 70, 70)));
    boat.addChild(hull);
    world.addChild(boat);


    // Create the camera mount
    Entity camera_mount;
    world.addChild(camera_mount);

    Camera camera;
    camera.attachTo(camera_mount);
    camera.setFovLength(500);
    camera.setPictureWidthHeight(width, height);

    // Set initial camera mount position
    float cam_x = 0.0f;
    float cam_y = -150.0f;
    float cam_z = 0.0f;

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

    FrameBuffer wood_texture = load_texture(
        std::string(SRC_DIR) + "/data/textures/wood_texture.jpg");

    Program<BoatUniform, BoatVarying> boat_program;
    boat_program.vertex_shader = boat_vertex_shader;
    boat_program.fragment_shader = boat_fragment_shader;
    boat_program.uniform.texture = &wood_texture;

    Options options;
    options.cull_mode = CullMode::CounterClockwise;

    Options boat_options;
    boat_options.cull_mode = CullMode::CounterClockwise;

    float time = 0.0f;
    float boat_angle = 0.0f;
    const float orbit_radius = 1200.0f;
    const float orbit_speed = 0.002f;

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

        float boat_x = orbit_radius * std::sin(boat_angle);
        float boat_z = orbit_radius * std::cos(boat_angle);
        boat.setTransform(Transform(
            Eigen::Vector3f(boat_x, -550, boat_z),
            Eigen::Vector3f(0, boat_angle, 0)));
        boat_angle += orbit_speed;

        program.uniform.time = time;
        program.uniform.view_inverse = camera_mount.getWorldMatrix();
        time += 0.05f;

        camera.draw(&water_entity, program, options, buffers);
        camera.draw(&hull, boat_program, boat_options, buffers);

        view.setFrame(frame_buffer);
        view.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    view.join();

    return 0;
}
