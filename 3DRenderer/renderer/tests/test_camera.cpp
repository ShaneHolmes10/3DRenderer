#include "CppUnitLite/TestHarness.h"
#include "renderer/camera.h"
#include "forms/entity.h"
#include "forms/model.h"
#include "forms/mesh.h"
#include "display/frame_buffer.h"
#include "utils/transform.h"
#include <Eigen/Dense>
#include <cmath>

// ============================================================
// Helper Functions
// ============================================================

Mesh buildTriangleMesh(
    Eigen::Vector3f a,
    Eigen::Vector3f b,
    Eigen::Vector3f c,
    Eigen::Vector3i col
) {
    Vertex3 v0;
    v0.position = a;
    v0.color = col;

    Vertex3 v1;
    v1.position = b;
    v1.color = col;

    Vertex3 v2;
    v2.position = c;
    v2.color = col;

    std::vector<Vertex3> verts = {v0, v1, v2};
    std::vector<Face> faces = {{0, 1, 2}};
    return Mesh(verts, faces);
}

bool hasDrawnPixels(const FrameBuffer& fb) {
    for (size_t i = 0; i < fb.pixels.size(); i += 4) {
        if (fb.pixels[i] != 255 || fb.pixels[i+1] != 255 || fb.pixels[i+2] != 255) {
            return true;
        }
    }
    return false;
}

int countDrawnPixels(const FrameBuffer& fb) {
    int count = 0;
    for (size_t i = 0; i < fb.pixels.size(); i += 4) {
        if (fb.pixels[i] != 255 || fb.pixels[i+1] != 255 || fb.pixels[i+2] != 255) {
            count++;
        }
    }
    return count;
}

// ============================================================
// attachTo Tests
// ============================================================

TEST(Camera, AttachToSetsMount) {
    Camera camera;
    Entity mount;
    camera.attachTo(mount);
    CHECK(camera.getMount() == &mount);
}

TEST(Camera, AttachToNewEntityUpdatesMount) {
    Camera camera;
    Entity mount1;
    Entity mount2;
    camera.attachTo(mount1);
    CHECK(camera.getMount() == &mount1);
    camera.attachTo(mount2);
    CHECK(camera.getMount() == &mount2);
}

// ============================================================
// Draw Tests
// ============================================================

TEST(Camera, DrawRendersTriangleInFrontOfCamera) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(
        Eigen::Vector3f(-0.5f, -0.5f, 5.0f),
        Eigen::Vector3f( 0.5f, -0.5f, 5.0f),
        Eigen::Vector3f( 0.0f,  0.5f, 5.0f),
        Eigen::Vector3i(255, 0, 0)
    );
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    Transform t_entity(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    entity.setTransform(t_entity);

    Entity cam_mount;
    Transform t_cam(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    cam_mount.setTransform(t_cam);

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DrawCommand cmd;
    cmd.entity = &entity;
    cmd.cull_mode = CullMode::None;
    camera.draw(fb, cmd);

    CHECK(hasDrawnPixels(fb));
}

TEST(Camera, DrawDoesNotRenderTriangleBehindCamera) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(
        Eigen::Vector3f(-0.5f, -0.5f, -5.0f),
        Eigen::Vector3f( 0.5f, -0.5f, -5.0f),
        Eigen::Vector3f( 0.0f,  0.5f, -5.0f),
        Eigen::Vector3i(255, 0, 0)
    );
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    Transform t_entity(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    entity.setTransform(t_entity);

    Entity cam_mount;
    Transform t_cam(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    cam_mount.setTransform(t_cam);

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DrawCommand cmd;
    cmd.entity = &entity;
    cmd.cull_mode = CullMode::None;
    camera.draw(fb, cmd);

    CHECK(!hasDrawnPixels(fb));
}

TEST(Camera, DrawRespectsEntityTransform) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(
        Eigen::Vector3f(-0.5f, -0.5f, 0.0f),
        Eigen::Vector3f( 0.5f, -0.5f, 0.0f),
        Eigen::Vector3f( 0.0f,  0.5f, 0.0f),
        Eigen::Vector3i(0, 255, 0)
    );
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    Transform t_entity(Eigen::Vector3f(0, 0, 5), Eigen::Vector3f::Zero());
    entity.setTransform(t_entity);

    Entity cam_mount;
    Transform t_cam(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    cam_mount.setTransform(t_cam);

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DrawCommand cmd;
    cmd.entity = &entity;
    cmd.cull_mode = CullMode::None;
    camera.draw(fb, cmd);

    CHECK(hasDrawnPixels(fb));
}

TEST(Camera, DrawRespectsCameraTransform) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(
        Eigen::Vector3f(-0.5f, -0.5f, 10.0f),
        Eigen::Vector3f( 0.5f, -0.5f, 10.0f),
        Eigen::Vector3f( 0.0f,  0.5f, 10.0f),
        Eigen::Vector3i(255, 0, 0)
    );
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    Transform t_entity(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    entity.setTransform(t_entity);

    Entity cam_mount;
    Transform t_cam(Eigen::Vector3f(0, 0, 10), Eigen::Vector3f::Zero());
    cam_mount.setTransform(t_cam);

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DrawCommand cmd;
    cmd.entity = &entity;
    cmd.cull_mode = CullMode::None;
    camera.draw(fb, cmd);

    CHECK(!hasDrawnPixels(fb));
}

TEST(Camera, CloserObjectAppearsLarger) {
    int w = 200;
    int h = 200;

    Mesh mesh_close = buildTriangleMesh(
        Eigen::Vector3f(-1.0f, -1.0f, 3.0f),
        Eigen::Vector3f( 1.0f, -1.0f, 3.0f),
        Eigen::Vector3f( 0.0f,  1.0f, 3.0f),
        Eigen::Vector3i(255, 0, 0)
    );
    Mesh mesh_far = buildTriangleMesh(
        Eigen::Vector3f(-1.0f, -1.0f, 10.0f),
        Eigen::Vector3f( 1.0f, -1.0f, 10.0f),
        Eigen::Vector3f( 0.0f,  1.0f, 10.0f),
        Eigen::Vector3i(255, 0, 0)
    );

    Model model_close;
    model_close.addMesh(mesh_close);
    Model model_far;
    model_far.addMesh(mesh_far);

    Entity entity_close;
    entity_close.model = &model_close;
    Transform t_close(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    entity_close.setTransform(t_close);

    Entity entity_far;
    entity_far.model = &model_far;
    Transform t_far(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    entity_far.setTransform(t_far);

    Entity cam_mount;
    Transform t_cam(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    cam_mount.setTransform(t_cam);

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb_close(w, h);
    DrawCommand cmd_close;
    cmd_close.entity = &entity_close;
    cmd_close.cull_mode = CullMode::None;
    camera.draw(fb_close, cmd_close);

    FrameBuffer fb_far(w, h);
    DrawCommand cmd_far;
    cmd_far.entity = &entity_far;
    cmd_far.cull_mode = CullMode::None;
    camera.draw(fb_far, cmd_far);

    CHECK(countDrawnPixels(fb_close) > countDrawnPixels(fb_far));
}

TEST(Camera, DrawRendersCorrectColor) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(
        Eigen::Vector3f(-1.0f, -1.0f, 5.0f),
        Eigen::Vector3f( 1.0f, -1.0f, 5.0f),
        Eigen::Vector3f( 0.0f,  1.0f, 5.0f),
        Eigen::Vector3i(255, 0, 0)
    );
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    Transform t_entity(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    entity.setTransform(t_entity);

    Entity cam_mount;
    Transform t_cam(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    cam_mount.setTransform(t_cam);

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DrawCommand cmd;
    cmd.entity = &entity;
    cmd.cull_mode = CullMode::None;
    camera.draw(fb, cmd);

    size_t cx = w / 2;
    size_t cy = h / 2;
    size_t idx = (cy * w + cx) * 4;
    CHECK(fb.pixels[idx] == 255);
    CHECK(fb.pixels[idx + 1] == 0);
    CHECK(fb.pixels[idx + 2] == 0);
}

TEST(Camera, SceneGraphHierarchyAffectsRendering) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(
        Eigen::Vector3f(-0.5f, -0.5f, 0.0f),
        Eigen::Vector3f( 0.5f, -0.5f, 0.0f),
        Eigen::Vector3f( 0.0f,  0.5f, 0.0f),
        Eigen::Vector3i(0, 0, 255)
    );
    Model model;
    model.addMesh(mesh);

    Entity parent;
    Transform t_parent(Eigen::Vector3f(0, 0, 5), Eigen::Vector3f::Zero());
    parent.setTransform(t_parent);

    Entity child;
    child.model = &model;
    Transform t_child(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    parent.addChild(child);

    Entity cam_mount;
    Transform t_cam(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero());
    cam_mount.setTransform(t_cam);

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DrawCommand cmd;
    cmd.entity = &child;
    cmd.cull_mode = CullMode::None;
    camera.draw(fb, cmd);

    CHECK(hasDrawnPixels(fb));
}

int main() {
    TestResult tr;
    TestRegistry::runAllTests(tr);
    return 0;
}