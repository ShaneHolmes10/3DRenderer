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
    
    Viewport::init();
    
    int width = 800;
    int height = 600;
    Viewport view(width, height, 100, 100);
    
    Entity world;
    
    Entity tetrahedron_entity;
    Model tetrahedron_model;
    LoadCobjFile loader;
    std::string filename = std::string(SRC_DIR) + "/data/icosahedron.cobj";
    tetrahedron_model.addMesh(loader.load(filename));
    tetrahedron_entity.model = &tetrahedron_model;
    
    Transform t_tetra(Eigen::Vector3f(0, 30, 0), Eigen::Vector3f::Zero(), Eigen::Vector3f(150, 150, 150));
    tetrahedron_entity.setTransform(t_tetra);
    
    world.addChild(tetrahedron_entity);
    
    Entity camera_mount;
    world.addChild(camera_mount);
    
    Camera camera;
    camera.attachTo(camera_mount);
    camera.setFovLength(250);
    camera.setPictureWidthHeight(width, height);
    
    view.start();
    
    // Animation loop - orbit camera around tetrahedron
    float angle = 0;
    while(true) {
        
        float orbit_radius = 300.0f;
        float theta = angle * 0.05f;
        
        // Camera position (orbit in circle)
        float cam_x = orbit_radius * std::sin(theta);
        float cam_y = 50.0f;
        float cam_z = orbit_radius * std::cos(theta);
        
        // Camera rotation (look at origin where tetrahedron is)
        // Rotate around Y axis to face the center
        float rotation_y = theta + M_PI;  // Face inward toward origin
        
        Transform t_cam(Eigen::Vector3f(cam_x, cam_y, cam_z), 
                        Eigen::Vector3f(0, rotation_y, 0));
        camera_mount.setTransform(t_cam);
        
        FrameBuffer frame_buffer(width, height);
        
        DrawCommand cmd;
        cmd.entity = &tetrahedron_entity;
        cmd.cull_mode = CullMode::None;
        
        camera.draw(frame_buffer, cmd);
        
        view.setFrame(frame_buffer);
        view.update();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    
        angle += 1.0f;
    }
    
    std::cout << "Animation complete. Close window to exit.\n";
    
    view.join();
    
    return 0;
}