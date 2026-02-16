
#include "forms/entity.h"
#include "forms/mesh.h"
#include "display/frame_buffer.h"
#include "renderer/camera.h"
#include "utils/draw_triangles.h"

#include <vector>

void Camera::draw(FrameBuffer& frame_buffer, const DrawCommand& draw_command) {

    const Entity* target_entity = draw_command.entity;
    const std::vector<Mesh>& target_meshes = target_entity->model->getMeshes();

    for(const Mesh& mesh : target_meshes) {

        const std::vector<Vertex>& vertices = mesh.getVertices();

        for(const Face& face : mesh.getFaces()) {

            // Get the vertices
            Eigen::Vector3f v1 = vertices[face.v1].position;
            Eigen::Vector3f v2 = vertices[face.v2].position;
            Eigen::Vector3f v3 = vertices[face.v3].position;
        
            // Convert to homogeneous (4D, w=1 for points)
            Eigen::Vector4f v1_homo(v1.x(), v1.y(), v1.z(), 1.0f);
            Eigen::Vector4f v2_homo(v2.x(), v2.y(), v2.z(), 1.0f);
            Eigen::Vector4f v3_homo(v3.x(), v3.y(), v3.z(), 1.0f);

            // Get expressed in cameras reference frame 
            Eigen::Vector4f v1_expressed = this->mount->getWorldMatrix().inverse() * (target_entity->getWorldMatrix() * v1_homo);
            Eigen::Vector4f v2_expressed = this->mount->getWorldMatrix().inverse() * (target_entity->getWorldMatrix() * v2_homo);
            Eigen::Vector4f v3_expressed = this->mount->getWorldMatrix().inverse() * (target_entity->getWorldMatrix() * v3_homo);

            // Future frustum check when we get to that point


            // Perspective projection
            float z1 = v1_expressed.z();
            float z2 = v2_expressed.z();
            float z3 = v3_expressed.z();

            float x1_screen = (v1_expressed.x() * (focal_length / z1)) + (width / 2);
            float y1_screen = (v1_expressed.y() * (focal_length / z1)) + (height / 2);

            float x2_screen = (v2_expressed.x() * (focal_length / z2)) + (width / 2);
            float y2_screen = (v2_expressed.y() * (focal_length / z2)) + (height / 2);

            float x3_screen = (v3_expressed.x() * (focal_length / z3)) + (width / 2);
            float y3_screen = (v3_expressed.y() * (focal_length / z3)) + (height / 2);

            // Create 2D triangle for rasterization
            Triangle2 tri_2d;
            tri_2d.vertex_A = Eigen::Vector2f(x1_screen, y1_screen);
            tri_2d.vertex_B = Eigen::Vector2f(x2_screen, y2_screen);
            tri_2d.vertex_C = Eigen::Vector2f(x3_screen, y3_screen);

            tri_2d.color_A = vertices[face.v1].color;
            tri_2d.color_B = vertices[face.v2].color;
            tri_2d.color_C = vertices[face.v3].color;

            drawTriangle(frame_buffer, tri_2d);

        }
    }
}
