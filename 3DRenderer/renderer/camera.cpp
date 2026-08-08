
#include "renderer/camera.h"

#include <vector>

#include "forms/entity.h"
#include "forms/mesh.h"

std::vector<Varying> Camera::process_vertices(
    const std::vector<VertexAttributes>& vertices, 
    const Program& program,
    const Options& options
    ) const {
    
    std::vector<Varying> processed_vertices;
    processed_vertices.reserve(vertices.size());
    
    for (const VertexAttributes& vertex : vertices) {
        processed_vertices.push_back(
            program.vertex_shader(program.uniform, vertex)
        );
    }
    
    return processed_vertices;
}

void Camera::process_triangles(
    const std::vector<RasterTriangle>& triangles, 
    const Program& program,
    const Options& options,
    Buffers& buffers
    ) const {

    for (const RasterTriangle& triangle : triangles) {
        rasterize(
            triangle, 
            program.uniform, 
            program.fragment_shader,
            buffers
        );
    }
}

void Camera::draw(
    Entity* entity, 
    const Program& program,
    const Options& options, 
    Buffers& buffers
    ) {
    
    for (const Mesh& mesh : entity->model->getMeshes()) {
        const std::vector<Vertex3>& mesh_vertices = mesh.getVertices();

        std::vector<VertexAttributes> vertex_attributes;
        vertex_attributes.reserve(mesh_vertices.size());
        
        for (const Vertex3& vertex : mesh_vertices) {
            vertex_attributes.push_back({vertex.position, vertex.color});
        }

        std::vector<Varying> processed_vertices =
            process_vertices(vertex_attributes, program, options);

        // TODO: assemble each Face in mesh.getFaces() into a triangle
        // from processed_vertices, clip + project it into a
        // RasterTriangle, then call process_triangles() with the
        // results and buffers.
    }
}
