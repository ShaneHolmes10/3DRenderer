#include "display/viewport.h"
#include "display/frame_buffer.h"
#include "utils/draw_triangles.h"
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
    
    view.start();
    
    // Animation loop
    float angle = 0;
    while(true) {
        
        FrameBuffer frame_buffer(width, height);
        
        // Center of rotation
        float center_x = width / 2.0f;
        float center_y = height / 2.0f;
        
        // Triangle vertices relative to center
        float radius = 200.0f;
        
        // Rotate vertices around center
        // Clockwise rotation (negate angle)
        float theta = -angle * 0.05f;  // Negative for clockwise
        
        Triangle tri;
        
        // Vertex A (top)
        tri.vertex_A = Eigen::Vector2f(
            center_x + radius * std::cos(theta),
            center_y + radius * std::sin(theta)
        );
        
        // Vertex B (bottom right)
        float b_angle = theta + (2.0f * M_PI / 3.0f);
        tri.vertex_B = Eigen::Vector2f(
            center_x + radius * std::cos(theta + 2.0f * M_PI / 3.0f),
            center_y + radius * std::sin(theta + 2.0f * M_PI / 3.0f)
        );
        
        // Vertex C (bottom left)
        float c_angle = theta + (4.0f * M_PI / 3.0f);
        tri.vertex_C = Eigen::Vector2f(
            center_x + radius * std::cos(theta + 4.0f * M_PI / 3.0f),
            center_y + radius * std::sin(theta + 4.0f * M_PI / 3.0f)
        );
        
        tri.color_A = Eigen::Vector3i(255, 0, 0);
        tri.color_B = Eigen::Vector3i(0, 255, 0);
        tri.color_C = Eigen::Vector3i(0, 0, 255);
        
        drawTriangle(frame_buffer, tri);
        
        view.setFrame(frame_buffer);
        view.update();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    
        angle += 0.5f;

    }
    
    std::cout << "Animation complete. Close window to exit.\n";
    
    view.join();
    
    return 0;
}