
#include "forms/entity.h"
#include "forms/mesh.h"
#include "display/frame_buffer.h"
#include "renderer/camera.h"
#include "utils/draw_triangles_to_screen.h"
#include "utils/clip_triangles.h"

#include <vector>

static constexpr float NEAR_Z = 0.1f;

void Camera::draw(FrameBuffer& frame_buffer, const DrawCommand& draw_command) {

    const Entity* target_entity = draw_command.entity;
    const std::vector<Mesh>& target_meshes = target_entity->model->getMeshes();

    for(const Mesh& mesh : target_meshes) {

        const std::vector<Vertex3>& vertices = mesh.getVertices();

        for(const Face& face : mesh.getFaces()) {

            // Get the vertices
            Eigen::Vector3f v1 = vertices[face.v1].position;
            Eigen::Vector3f v2 = vertices[face.v2].position;
            Eigen::Vector3f v3 = vertices[face.v3].position;
        
            // Convert to homogeneous (4D, w=1 for points)
            Eigen::Vector4f v1_homo(v1.x(), v1.y(), v1.z(), 1.0f);
            Eigen::Vector4f v2_homo(v2.x(), v2.y(), v2.z(), 1.0f);
            Eigen::Vector4f v3_homo(v3.x(), v3.y(), v3.z(), 1.0f);

            // Transform to camera space
            Eigen::Matrix4f view  = this->mount->getWorldMatrix().inverse();
            Eigen::Matrix4f model = target_entity->getWorldMatrix();

            Eigen::Vector4f v1_expressed = view * (model * v1_homo);
            Eigen::Vector4f v2_expressed = view * (model * v2_homo);
            Eigen::Vector4f v3_expressed = view * (model * v3_homo);

            // Build camera-space triangle, clip against frustum, and draw
            Triangle3 tri3;
            tri3.vertex_A.position = v1_expressed.head<3>();  tri3.vertex_A.color = vertices[face.v1].color;
            tri3.vertex_B.position = v2_expressed.head<3>();  tri3.vertex_B.color = vertices[face.v2].color;
            tri3.vertex_C.position = v3_expressed.head<3>();  tri3.vertex_C.color = vertices[face.v3].color;

            for (const Triangle3& clipped : clipTriangle(tri3, focal_length, width, height, NEAR_Z))
                drawTriangleToScreen(frame_buffer, projectTriangle(clipped, focal_length, width, height));

        }
    }
}
