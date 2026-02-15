#include "display/viewport.h"
#include "display/frame_buffer.h"
#include "renderer/camera.h"
#include "forms/entity.h"
#include "forms/model.h"
#include "forms/mesh.h"
#include "utils/transform.h"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>

int main() {
    
    Viewport::init();
    
    int width = 800;
    int height = 600;
    Viewport view(width, height, 100, 100);
    
    // Create world root entity
    Entity world;
    
    // ==== Create tetrahedron entity ====
    Entity tetrahedron_entity;

    Model tetrahedron_model;
    std::string filename = std::string(SRC_DIR) + "/data/tetrahedron.obj";
    tetrahedron_model.loadMesh(filename);

    tetrahedron_entity.model = &tetrahedron_model;
    
    Transform t_tetra(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    tetrahedron_entity.setTransform(t_tetra);
    
    world.addChild(tetrahedron_entity);
    
    // ==== Create camera mount entity ====
    Entity camera_mount;
    Transform t_cam(Eigen::Vector3f(0, 50, -300), Eigen::Vector3f::Zero());
    std::cout << "t_cam world coordinate " << t_cam.getMatrix() << "\n";
    camera_mount.setTransform(t_cam);
    
    world.addChild(camera_mount);
    
    // ==== Create camera ====
    Camera camera;
    camera.attachTo(camera_mount);
    camera.setFovLength(200);
    camera.setPictureWidthHeight(width, height);
    
    // Render
    FrameBuffer frame_buffer(width, height);
    
    DrawCommand cmd;
    cmd.entity = &tetrahedron_entity;
    cmd.cull_mode = CullMode::None;
    
    camera.draw(frame_buffer, cmd);
    
    // Display
    view.start();
    view.setFrame(frame_buffer);
    view.update();
    
    std::cout << "Tetrahedron rendered. Close window to exit.\n";
    std::cout << "Root world coordinate " << world.getWorldMatrix() << "\n";
    std::cout << "Tetra world coordinate " << tetrahedron_entity.getWorldMatrix() << "\n";
    std::cout << "Camera world coordinate " << camera_mount.getWorldMatrix() << "\n";
    
    view.join();
    
    return 0;
}