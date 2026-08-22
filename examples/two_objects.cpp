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

/**!SECTION
 *
 * The objective of this file is to provide an interactive environment where there are 2
 * objects in the scene. This will highlight the shortcomings of a renderer with no depth buffer.
 *
 */
int main() {

    // Initialize Viewport
    Viewport::init();

    int width = 800;
    int height = 600;
    Viewport view(width, height, 100, 100);

    // Create the world entity, root of the scene graph
    Entity world;

    LoadCobjFile loader;
    std::string filename = std::string(SRC_DIR) + "/data/icosahedron.cobj";

    // Load the first scene object
    Entity entity_1;
    Model model_1;
    model_1.addMesh(loader.load(filename));
    entity_1.model = &model_1;
    entity_1.setTransform(Transform(Eigen::Vector3f(0, 30, 0), Eigen::Vector3f::Zero(), Eigen::Vector3f(150, 150, 150)));
    world.addChild(entity_1);

    // Load the second scene object
    Entity entity_2;
    Model model_2;
    model_2.addMesh(loader.load(filename));
    entity_2.model = &model_2;
    entity_2.setTransform(Transform(Eigen::Vector3f(400, 30, 0), Eigen::Vector3f::Zero(), Eigen::Vector3f(150, 150, 150)));
    world.addChild(entity_2);

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
                rotation_y += rotate_speed;
                break;
            case Right:  // Rotate right
                rotation_y -= rotate_speed;
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

    struct Varying {
        Eigen::Vector4f position = Eigen::Vector4f::Zero();
        Eigen::Vector3f color    = Eigen::Vector3f::Zero();
        VARYING(position, color)
    };

    struct SceneUniform {};
    Program<SceneUniform, Varying> program;
    program.vertex_shader = [](const SceneUniform&, const VertexAttributes& v) {
        Varying out;
        out.position = Eigen::Vector4f(v.position.x(), v.position.y(),
                                       v.position.z(), 1.0f);
        out.color = v.color.cast<float>();
        return out;
    };
    program.fragment_shader = [](const SceneUniform&, const Varying& v) {
        return v.color.cast<int>();
    };

    Options options;
    options.cull_mode = CullMode::None;

    FrameBuffer frame_buffer(width, height);
    DepthBuffer depth_buffer(width, height);

    while(true) {
        camera_mount.setTransform(Transform(
            Eigen::Vector3f(cam_x, cam_y, cam_z),
            Eigen::Vector3f(rotation_x, rotation_y, rotation_z)
        ));

        frame_buffer.clear();
        depth_buffer.clear();

        Buffers buffers{frame_buffer, depth_buffer};
        camera.draw(&entity_1, program, options, buffers);
        camera.draw(&entity_2, program, options, buffers);

        view.setFrame(frame_buffer);
        view.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    view.join();

    return 0;
}
