#include "display/viewport.h"
#include "display/frame_buffer.h"
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
    
    // Load the scene object
    Entity tetrahedron_entity;
    Model tetrahedron_model;
    LoadCobjFile loader;
    std::string filename = std::string(SRC_DIR) + "/data/icosahedron.cobj";
    tetrahedron_model.addMesh(loader.load(filename));
    tetrahedron_entity.model = &tetrahedron_model;
    
    Transform t_tetra(Eigen::Vector3f(0, 30, 0), Eigen::Vector3f::Zero(), Eigen::Vector3f(150, 150, 150));
    tetrahedron_entity.setTransform(t_tetra);
    
    world.addChild(tetrahedron_entity);
    
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
                std::cout << "W\n";
                break;
            case S:  // Move backward
                cam_x -= move_speed * std::sin(rotation_y);
                cam_z -= move_speed * std::cos(rotation_y);
                std::cout << "S\n";
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
                std::cout << "Left\n";
                break;
            case Right:  // Rotate right
                rotation_y -= rotate_speed;
                std::cout << "Right\n";
                break;
            case Up:  // Look up
                rotation_x += rotate_speed;
                std::cout << "Up\n";
                break;
            case Down:  // Look down
                rotation_x -= rotate_speed;
                std::cout << "Down\n";
                break;
            default:
                break;
        }
    });

    // Start the view port
    view.start();

    while(true) {
                
        Transform t_cam(Eigen::Vector3f(cam_x, cam_y, cam_z), 
                        Eigen::Vector3f(rotation_x, rotation_y, rotation_z));

        camera_mount.setTransform(t_cam);
        
        FrameBuffer frame_buffer(width, height);
        
        DrawCommand cmd;
        cmd.entity = &tetrahedron_entity;
        cmd.cull_mode = CullMode::None;
        
        camera.draw(frame_buffer, cmd);
        
        view.setFrame(frame_buffer);
        view.update();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));

    }
    
    std::cout << "Animation complete. Close window to exit.\n";
    
    view.join();
    
    return 0;
}