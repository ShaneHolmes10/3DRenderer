#include <Eigen/Dense>
#include <cmath>
#include <utility>

#include "CppUnitLite/TestHarness.h"
#include "display/depth_buffer.h"
#include "display/frame_buffer.h"
#include "forms/entity.h"
#include "forms/mesh.h"
#include "forms/model.h"
#include "renderer/camera.h"
#include "renderer/types.h"
#include "utils/transform.h"

// ============================================================
// Helper types and factories
// ============================================================

struct Varying {
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector3f color = Eigen::Vector3f::Zero();
    VARYING(position, color)
};

struct CameraTestUniform {
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f proj = Eigen::Matrix4f::Identity();
};

Program<CameraTestUniform, Varying> makeProgram() {
    Program<CameraTestUniform, Varying> program;
    program.vertex_shader = [](const CameraTestUniform& u,
                               const VertexAttributes& v) {
        Varying out;
        out.position = u.proj * u.view * u.model *
                       Eigen::Vector4f(v.position.x(), v.position.y(),
                                       v.position.z(), 1.0f);
        out.color = v.color.cast<float>();
        return out;
    };
    program.fragment_shader = [](const CameraTestUniform&,
                                 const Varying& v) {
        return v.color.cast<int>();
    };
    return program;
}

Mesh buildTriangleMesh(Eigen::Vector3f a, Eigen::Vector3f b,
                       Eigen::Vector3f c, const Eigen::Vector3i& col) {
    Vertex3 v0;
    v0.position = std::move(a);
    v0.color = col;

    Vertex3 v1;
    v1.position = std::move(b);
    v1.color = col;

    Vertex3 v2;
    v2.position = std::move(c);
    v2.color = col;

    std::vector<Vertex3> verts = {v0, v1, v2};
    std::vector<Face> faces = {{0, 1, 2}};
    return {verts, faces};
}

bool hasDrawnPixels(const FrameBuffer& fb) {
    for (size_t i = 0; i < fb.pixels.size(); i += 4) {
        if (fb.pixels[i] != 255 || fb.pixels[i + 1] != 255 ||
            fb.pixels[i + 2] != 255) {
            return true;
        }
    }
    return false;
}

int countDrawnPixels(const FrameBuffer& fb) {
    int count = 0;
    for (size_t i = 0; i < fb.pixels.size(); i += 4) {
        if (fb.pixels[i] != 255 || fb.pixels[i + 1] != 255 ||
            fb.pixels[i + 2] != 255) {
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

    Mesh mesh = buildTriangleMesh(Eigen::Vector3f(-0.5f, -0.5f, 5.0f),
                                  Eigen::Vector3f(0.5f, -0.5f, 5.0f),
                                  Eigen::Vector3f(0.0f, 0.5f, 5.0f),
                                  Eigen::Vector3i(255, 0, 0));
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    entity.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Entity cam_mount;
    cam_mount.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DepthBuffer db(w, h);
    Buffers buffers{fb, db};
    Options options;
    camera.draw(&entity, makeProgram(), options, buffers);

    CHECK(hasDrawnPixels(fb));
}

TEST(Camera, DrawDoesNotRenderTriangleBehindCamera) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(Eigen::Vector3f(-0.5f, -0.5f, -5.0f),
                                  Eigen::Vector3f(0.5f, -0.5f, -5.0f),
                                  Eigen::Vector3f(0.0f, 0.5f, -5.0f),
                                  Eigen::Vector3i(255, 0, 0));
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    entity.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Entity cam_mount;
    cam_mount.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DepthBuffer db(w, h);
    Buffers buffers{fb, db};
    Options options;
    camera.draw(&entity, makeProgram(), options, buffers);

    CHECK(!hasDrawnPixels(fb));
}

TEST(Camera, DrawRespectsEntityTransform) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(Eigen::Vector3f(-0.5f, -0.5f, 0.0f),
                                  Eigen::Vector3f(0.5f, -0.5f, 0.0f),
                                  Eigen::Vector3f(0.0f, 0.5f, 0.0f),
                                  Eigen::Vector3i(0, 255, 0));
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    entity.setTransform(
        Transform(Eigen::Vector3f(0, 0, 5), Eigen::Vector3f::Zero()));

    Entity cam_mount;
    cam_mount.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DepthBuffer db(w, h);
    Buffers buffers{fb, db};
    Options options;
    camera.draw(&entity, makeProgram(), options, buffers);

    CHECK(hasDrawnPixels(fb));
}

TEST(Camera, DrawRespectsCameraTransform) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(Eigen::Vector3f(-0.5f, -0.5f, 10.0f),
                                  Eigen::Vector3f(0.5f, -0.5f, 10.0f),
                                  Eigen::Vector3f(0.0f, 0.5f, 10.0f),
                                  Eigen::Vector3i(255, 0, 0));
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    entity.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Entity cam_mount;
    cam_mount.setTransform(
        Transform(Eigen::Vector3f(0, 0, 10), Eigen::Vector3f::Zero()));

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DepthBuffer db(w, h);
    Buffers buffers{fb, db};
    Options options;
    camera.draw(&entity, makeProgram(), options, buffers);

    CHECK(!hasDrawnPixels(fb));
}

TEST(Camera, CloserObjectAppearsLarger) {
    int w = 200;
    int h = 200;

    Mesh mesh_close = buildTriangleMesh(
        Eigen::Vector3f(-1.0f, -1.0f, 3.0f),
        Eigen::Vector3f(1.0f, -1.0f, 3.0f),
        Eigen::Vector3f(0.0f, 1.0f, 3.0f), Eigen::Vector3i(255, 0, 0));
    Mesh mesh_far = buildTriangleMesh(
        Eigen::Vector3f(-1.0f, -1.0f, 10.0f),
        Eigen::Vector3f(1.0f, -1.0f, 10.0f),
        Eigen::Vector3f(0.0f, 1.0f, 10.0f), Eigen::Vector3i(255, 0, 0));

    Model model_close;
    model_close.addMesh(mesh_close);
    Model model_far;
    model_far.addMesh(mesh_far);

    Entity entity_close;
    entity_close.model = &model_close;
    entity_close.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Entity entity_far;
    entity_far.model = &model_far;
    entity_far.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Entity cam_mount;
    cam_mount.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    Options options;

    FrameBuffer fb_close(w, h);
    DepthBuffer db_close(w, h);
    Buffers buffers_close{fb_close, db_close};
    camera.draw(&entity_close, makeProgram(), options, buffers_close);

    FrameBuffer fb_far(w, h);
    DepthBuffer db_far(w, h);
    Buffers buffers_far{fb_far, db_far};
    camera.draw(&entity_far, makeProgram(), options, buffers_far);

    CHECK(countDrawnPixels(fb_close) > countDrawnPixels(fb_far));
}

TEST(Camera, DrawRendersCorrectColor) {
    int w = 200;
    int h = 200;

    Mesh mesh = buildTriangleMesh(Eigen::Vector3f(-1.0f, -1.0f, 5.0f),
                                  Eigen::Vector3f(1.0f, -1.0f, 5.0f),
                                  Eigen::Vector3f(0.0f, 1.0f, 5.0f),
                                  Eigen::Vector3i(255, 0, 0));
    Model model;
    model.addMesh(mesh);

    Entity entity;
    entity.model = &model;
    entity.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Entity cam_mount;
    cam_mount.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DepthBuffer db(w, h);
    Buffers buffers{fb, db};
    Options options;
    camera.draw(&entity, makeProgram(), options, buffers);

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

    Mesh mesh = buildTriangleMesh(Eigen::Vector3f(-0.5f, -0.5f, 0.0f),
                                  Eigen::Vector3f(0.5f, -0.5f, 0.0f),
                                  Eigen::Vector3f(0.0f, 0.5f, 0.0f),
                                  Eigen::Vector3i(0, 0, 255));
    Model model;
    model.addMesh(mesh);

    Entity parent;
    parent.setTransform(
        Transform(Eigen::Vector3f(0, 0, 5), Eigen::Vector3f::Zero()));

    Entity child;
    child.model = &model;
    child.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));
    parent.addChild(child);

    Entity cam_mount;
    cam_mount.setTransform(
        Transform(Eigen::Vector3f(0, 0, 0), Eigen::Vector3f::Zero()));

    Camera camera;
    camera.attachTo(cam_mount);
    camera.setFovLength(100.0f);
    camera.setPictureWidthHeight(w, h);

    FrameBuffer fb(w, h);
    DepthBuffer db(w, h);
    Buffers buffers{fb, db};
    Options options;
    camera.draw(&child, makeProgram(), options, buffers);

    CHECK(hasDrawnPixels(fb));
}

int main() {
    TestResult tr;
    TestRegistry::runAllTests(tr);
    return 0;
}
