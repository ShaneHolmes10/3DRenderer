#pragma once

#include "display/depth_buffer.h"
#include "display/frame_buffer.h"
#include "forms/entity.h"

/**
 * @brief Specifies which triangle faces to skip during rasterization.
 *
 * Backface culling is determined by the winding order of the triangle's
 * projected vertices in screen space.
 */
enum class CullMode { None, Clockwise, CounterClockwise };

/**
 * @brief Encapsulates rendering settings for a single draw call.
 *
 * A DrawCommand pairs an entity to render with rendering configuration
 * such as cull mode. This separates rendering settings from the scene
 * graph, allowing the same entity to be drawn with different settings.
 */
struct DrawCommand {
    Entity* entity;
    CullMode cull_mode = CullMode::None;
    ;
};

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
        width = w;
        height = h;
    }

    /**
     * @brief Render an entity to the frame buffer.
     *
     * Transforms all vertices of the entity's model through the full
     * rendering pipeline (model to world to camera to screen space),
     * then rasterizes each triangle with per vertex color
     * interpolation.
     *
     * @param frame_buffer The pixel buffer to render into
     * @param draw_command The entity and rendering settings to use
     */
    void draw(FrameBuffer& frame_buffer, DepthBuffer& depth_buffer,
              const DrawCommand& draw_command);
};
