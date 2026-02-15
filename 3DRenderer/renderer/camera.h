#pragma once

#include "forms/entity.h"
#include "display/frame_buffer.h"


enum class CullMode {
    None,
    Clockwise,
    CounterClockwise
};

struct DrawCommand {

    Entity* entity;
    CullMode cull_mode = CullMode::None;;

};

class Camera {

private:

    Entity* mount;

    float fov_length;
    int width;
    int height;

    // void generateFovNormals(); // Ignore the Frustum for the moment

public:

    Camera() { }

    void attachTo(Entity& entity) { mount = &entity; }

    Entity* getMount() const { return mount; }

    void setFovLength(float length) { fov_length = length; }

    void setPictureWidthHeight(int w, int h) { width = w; height = h; }

    void draw(FrameBuffer& frame_buffer, const DrawCommand& draw_command);

};
