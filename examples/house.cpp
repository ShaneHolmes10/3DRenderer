#include "display/viewport.h"
#include "display/frame_buffer.h"
#include "display/depth_buffer.h"
#include "renderer/camera.h"
#include "forms/entity.h"
#include "forms/model.h"
#include "forms/mesh.h"
#include "utils/transform.h"
#include "utils/load_cobj_file.h"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

int main() {

    // Initialize Viewport
    Viewport::init();

    int width = 800;
    int height = 600;
    Viewport view(width, height, 100, 100);

    // Create the world entity, root of the scene graph
    Entity world;

    // Load the house model
    Entity house_entity;
    Model house_model;
    LoadCobjFile loader;
    std::string filename = std::string(SRC_DIR) + "/data/simple_house.cobj";
    house_model.addMesh(loader.load(filename));
    house_entity.model = &house_model;

    Transform t_house(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f(-M_PI / 2, 0, M_PI), Eigen::Vector3f(30, 30, 30));
    house_entity.setTransform(t_house);

    world.addChild(house_entity);

    // Create the camera mount
    Entity camera_mount;
    world.addChild(camera_mount);

    Camera camera;
    camera.attachTo(camera_mount);
    camera.setFovLength(250);
    camera.setPictureWidthHeight(width, height);

    // Set initial camera mount position
    float cam_x = 0.0f;
    float cam_y = 50.0f;
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

    FrameBuffer frame_buffer(width, height);
    DepthBuffer depth_buffer(width, height);

    while(true) {

        Transform t_cam(Eigen::Vector3f(cam_x, cam_y, cam_z),
                        Eigen::Vector3f(rotation_x, rotation_y, rotation_z));

        camera_mount.setTransform(t_cam);

        frame_buffer.clear();
        depth_buffer.clear();

        DrawCommand cmd;
        cmd.entity = &house_entity;
        cmd.cull_mode = CullMode::None;

        camera.draw(frame_buffer, depth_buffer, cmd);

        view.setFrame(frame_buffer);
        view.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    view.join();

    return 0;
}
