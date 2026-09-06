#include <Eigen/Dense>
#include <chrono>
#include <cmath>
#include <thread>

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"
#include "display/viewport.h"
#include "forms/entity.h"
#include "forms/model.h"
#include "renderer/camera.h"
#include "renderer/types.h"
#include "utils/load_cobj_file.h"
#include "utils/load_texture.h"
#include "utils/transform.h"

struct TextureVarying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector2f uv = Eigen::Vector2f::Zero();
    VARYING(position, uv)
};

struct TextureUniform {
    const FrameBuffer* texture = nullptr;
    Eigen::Matrix4f view_inv = Eigen::Matrix4f::Identity();
};

int main() {
    Viewport::init();

    int width = 800;
    int height = 600;
    Viewport view(width, height, 100, 100);

    Entity icosahedron_entity;
    Model icosahedron_model;
    LoadCobjFile loader;
    std::string mesh_path = std::string(SRC_DIR) + "/data/icosahedron.cobj";
    icosahedron_model.addMesh(loader.load(mesh_path));
    icosahedron_entity.model = &icosahedron_model;
    icosahedron_entity.setTransform(Transform(
        Eigen::Vector3f(0, 30, 0), Eigen::Vector3f::Zero(),
        Eigen::Vector3f(150, 150, 150)));

    Entity camera_mount;
    Camera camera;
    camera.attachTo(camera_mount);
    camera.setFovLength(250);
    camera.setPictureWidthHeight(width, height);

    std::string texture_path =
        std::string(SRC_DIR) + "/data/textures/wood_texture.jpg";
    FrameBuffer texture = load_texture(texture_path);

    Program<TextureUniform, TextureVarying> program;
    program.uniform.texture = &texture;

    // Planar UV: map camera-space x/y to texture coordinates.
    // Dividing by scale tiles the texture across the surface.
    program.vertex_shader = [](const TextureUniform& u,
                                const VertexAttributes& v) {
        const float scale = 100.0f;
        TextureVarying out;
        out.position = Eigen::Vector4f(v.position.x(), v.position.y(),
                                       v.position.z(), 1.0f);
        Eigen::Vector4f world_pos =
            u.view_inv *
            Eigen::Vector4f(v.position.x(), v.position.y(), v.position.z(),
                            1.0f);
        out.uv = Eigen::Vector2f(world_pos.x() / scale,
                                 world_pos.y() / scale);
        return out;
    };

    // Sample the texture at the interpolated UV, wrapping with fmod.
    program.fragment_shader = [](const TextureUniform& u,
                                  const TextureVarying& v) -> Eigen::Vector3i {
        float u_coord = std::fmod(std::abs(v.uv.x()), 1.0f);
        float v_coord = std::fmod(std::abs(v.uv.y()), 1.0f);

        size_t x = static_cast<size_t>(u_coord * (u.texture->width - 1));
        size_t y = static_cast<size_t>(v_coord * (u.texture->height - 1));

        size_t idx = (y * u.texture->width + x) * 4;
        return {u.texture->pixels[idx], u.texture->pixels[idx + 1],
                u.texture->pixels[idx + 2]};
    };

    float cam_x = 0.0f;
    float cam_y = 50.0f;
    float cam_z = 300.0f;
    float rotation_x = 0.0f;
    float rotation_y = M_PI;
    const float move_speed = 10.0f;
    const float rotate_speed = 0.1f;

    view.setKeyCallback([&](Key key) {
        switch (key) {
            case W:
                cam_x += move_speed * std::sin(rotation_y);
                cam_z += move_speed * std::cos(rotation_y);
                break;
            case S:
                cam_x -= move_speed * std::sin(rotation_y);
                cam_z -= move_speed * std::cos(rotation_y);
                break;
            case D:
                cam_x += move_speed * std::cos(rotation_y);
                cam_z -= move_speed * std::sin(rotation_y);
                break;
            case A:
                cam_x -= move_speed * std::cos(rotation_y);
                cam_z += move_speed * std::sin(rotation_y);
                break;
            case Q:
                cam_y += move_speed;
                break;
            case E:
                cam_y -= move_speed;
                break;
            case Left:
                rotation_y += rotate_speed;
                break;
            case Right:
                rotation_y -= rotate_speed;
                break;
            case Up:
                rotation_x += rotate_speed;
                break;
            case Down:
                rotation_x -= rotate_speed;
                break;
            default:
                break;
        }
    });

    Options options;
    options.cull_mode = CullMode::CounterClockwise;

    view.start();

    FrameBuffer frame_buffer(width, height);
    DepthBuffer depth_buffer(width, height);

    while (true) {
        camera_mount.setTransform(Transform(
            Eigen::Vector3f(cam_x, cam_y, cam_z),
            Eigen::Vector3f(rotation_x, rotation_y, 0)));

        program.uniform.view_inv = camera_mount.getWorldMatrix();

        frame_buffer.clear();
        depth_buffer.clear();

        Buffers buffers{frame_buffer, depth_buffer};
        camera.draw(&icosahedron_entity, program, options, buffers);

        view.setFrame(frame_buffer);
        view.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    view.join();
    return 0;
}
