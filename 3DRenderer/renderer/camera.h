#pragma once

#include <array>
#include <vector>

#include "forms/entity.h"
#include "forms/mesh.h"
#include "renderer/clip_triangles.h"
#include "renderer/project_triangles.h"
#include "renderer/rasterizer/rasterizer.h"
#include "renderer/types.h"

/**
 * @brief Handles the rendering pipeline from world space to screen
 * space.
 *
 * The Camera uses composition rather than inheritance. It does not
 * exist in the scene graph directly, but mounts to an Entity to inherit
 * its world transformation. This enables camera rigs where the camera
 * follows a moving entity (e.g., attached to a vehicle or character).
 *
 * The rendering pipeline transforms vertices through these stages:
 * 1. Model space (raw vertex positions from mesh)
 * 2. World space (entity world matrix applied)
 * 3. Camera space (inverse of mount's world matrix applied)
 * 4. Screen space (perspective projection and rasterization)
 */
class Camera {
   private:
    /**
     * @brief The entity this camera is mounted to.
     *
     * The camera uses this entity's world matrix to determine its
     * position and orientation in the scene. The inverse of this
     * matrix serves as the view matrix.
     */
    Entity* mount;

    /**
     * @brief Distance from the camera origin to the projection plane.
     *
     * Controls the strength of the perspective effect. Larger values
     * produce a narrower field of view (more telephoto), smaller
     * values produce a wider field of view.
     */
    float focal_length;

    /**
     * @brief Width of the output image in pixels.
     */
    int width;

    /**
     * @brief Height of the output image in pixels.
     */
    int height;

    /**
     * @brief Runs the vertex shader over every vertex, producing the
     * TVaryings the rest of the pipeline works with.
     */
    template <typename TUniform, typename TVarying>
    std::vector<TVarying> process_vertices(
        const std::vector<VertexAttributes>& vertices,
        const Program<TUniform, TVarying>& program) const {
        std::vector<TVarying> out;
        out.reserve(vertices.size());
        for (const VertexAttributes& v : vertices) {
            out.push_back(program.vertex_shader(program.uniform, v));
        }
        return out;
    }

    /**
     * @brief Rasterizes each triangle with the program's fragment shader.
     */
    template <typename TUniform, typename TVarying>
    void process_triangles(
        const std::vector<std::array<TVarying, 3>>& triangles,
        const Program<TUniform, TVarying>& program,
        Buffers& buffers) const {
        for (const std::array<TVarying, 3>& tri : triangles) {
            rasterize(tri, program.uniform, program.fragment_shader, buffers);
        }
    }

   public:
    /**
     * @brief Construct a default Camera.
     */
    Camera() {}

    /**
     * @brief Mount the camera to an entity in the scene graph.
     *
     * @param entity The entity to attach to
     */
    void attachTo(Entity& entity) { mount = &entity; }

    /**
     * @brief Get the entity this camera is mounted to.
     *
     * @return Pointer to the mount entity
     */
    Entity* getMount() const { return mount; }

    /**
     * @brief Set the focal length for perspective projection.
     *
     * @param length Focal length in world units
     */
    void setFovLength(float length) { focal_length = length; }

    /**
     * @brief Set the output image dimensions.
     *
     * @param w Width in pixels
     * @param h Height in pixels
     */
    void setPictureWidthHeight(int w, int h) {
        width  = w;
        height = h;
    }

    /**
     * @brief Render an entity to the frame buffer.
     *
     * Transforms all vertices of the entity's model through the full
     * rendering pipeline (model to world to camera to screen space),
     * then rasterizes each triangle with the program's shaders.
     *
     * @param entity  The entity to render
     * @param program The vertex/fragment shaders and uniform to render with
     * @param options Rendering settings for this draw call
     * @param buffers The frame and depth buffers to test and write into
     */
    template <typename TUniform, typename TVarying>
    void draw(Entity* entity, const Program<TUniform, TVarying>& program,
              const Options& options, Buffers& buffers) {
        static constexpr float NEAR_Z = 0.1f;

        Eigen::Matrix4f view  = mount->getWorldMatrix().inverse();
        Eigen::Matrix4f model = entity->getWorldMatrix();

        for (const Mesh& mesh : entity->model->getMeshes()) {
            const std::vector<Vertex3>& mesh_vertices = mesh.getVertices();

            std::vector<VertexAttributes> vertex_attributes;
            vertex_attributes.reserve(mesh_vertices.size());
            for (const Vertex3& v : mesh_vertices) {
                Eigen::Vector4f cam_pos =
                    view * model *
                    Eigen::Vector4f(v.position.x(), v.position.y(),
                                    v.position.z(), 1.0f);
                vertex_attributes.push_back({cam_pos.head<3>(), v.color});
            }

            std::vector<TVarying> processed_vertices =
                process_vertices(vertex_attributes, program);

            std::vector<std::array<TVarying, 3>> raster_triangles;
            for (const Face& face : mesh.getFaces()) {
                std::array<TVarying, 3> cam_tri = {
                    processed_vertices[face.v1],
                    processed_vertices[face.v2],
                    processed_vertices[face.v3],
                };
                for (const std::array<TVarying, 3>& clipped :
                     clip_triangle(cam_tri, focal_length, width, height, NEAR_Z)) {
                    raster_triangles.push_back(
                        project_triangle(clipped, focal_length, width, height));
                }
            }

            process_triangles(raster_triangles, program, buffers);
        }
    }
};
