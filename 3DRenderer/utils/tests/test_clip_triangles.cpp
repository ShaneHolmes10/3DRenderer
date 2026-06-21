
#include <Eigen/Dense>
#include <cmath>

#include "CppUnitLite/TestHarness.h"
#include "forms/mesh.h"
#include "utils/clip_triangles.h"
#include "utils/project_triangles.h"

// ── helpers
// ───────────────────────────────────────────────────────────────────

static Vertex3 makeVertex(float x, float y, float z, int r = 255,
                          int g = 255, int b = 255) {
    Vertex3 v;
    v.position = Eigen::Vector3f(x, y, z);
    v.color = Eigen::Vector3i(r, g, b);
    return v;
}

static Triangle3 makeTri(Vertex3 a, Vertex3 b, Vertex3 c) {
    Triangle3 t;
    t.vertex_A = a;
    t.vertex_B = b;
    t.vertex_C = c;
    return t;
}

// Standard frustum used across all tests:
//   focal=100, 200×200 screen, near_z=0.1
//   At depth z the lateral bounds are: x ∈ [−z, z], y ∈ [−z, z]
static constexpr float FOCAL = 100.0f;
static constexpr float W = 200.0f;
static constexpr float H = 200.0f;
static constexpr float NEAR_Z = 0.1f;

// ── fully inside
// ──────────────────────────────────────────────────────────────

// A triangle well inside all frustum planes should pass through
// unmodified and produce exactly one Triangle3.
TEST(ClipTriangles, FullyInsideFrustum_ReturnsOneTriangle) {
    Triangle3 tri = makeTri(makeVertex(-0.5f, -0.5f, 5.0f),
                            makeVertex(0.5f, -0.5f, 5.0f),
                            makeVertex(0.0f, 0.5f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.size() == 1);
}

// ── fully culled
// ──────────────────────────────────────────────────────────────

// All three vertices behind the near plane → entire triangle discarded.
TEST(ClipTriangles, AllVerticesBehindNearPlane_ReturnsEmpty) {
    Triangle3 tri = makeTri(makeVertex(0.0f, 0.0f, 0.05f),
                            makeVertex(1.0f, 0.0f, 0.05f),
                            makeVertex(0.0f, 1.0f, 0.05f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.empty());
}

// All vertices with negative z are also behind the near plane.
TEST(ClipTriangles, AllVerticesBehindCamera_ReturnsEmpty) {
    Triangle3 tri = makeTri(makeVertex(0.0f, 0.0f, -5.0f),
                            makeVertex(1.0f, 0.0f, -5.0f),
                            makeVertex(0.0f, 1.0f, -5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.empty());
}

// Left frustum plane: focal*x + (W/2)*z >= 0  →  x + z >= 0 (with these
// params). At z=5, the left boundary is x = −5. Triangle entirely to
// the left.
TEST(ClipTriangles, AllVerticesOutsideLeftFrustum_ReturnsEmpty) {
    Triangle3 tri = makeTri(makeVertex(-8.0f, 0.0f, 5.0f),
                            makeVertex(-7.0f, 0.0f, 5.0f),
                            makeVertex(-7.0f, 1.0f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.empty());
}

// Right frustum plane: −focal*x + (W/2)*z >= 0  →  z − x >= 0.
// At z=5, the right boundary is x = 5. Triangle entirely to the right.
TEST(ClipTriangles, AllVerticesOutsideRightFrustum_ReturnsEmpty) {
    Triangle3 tri = makeTri(makeVertex(8.0f, 0.0f, 5.0f),
                            makeVertex(7.0f, 0.0f, 5.0f),
                            makeVertex(7.0f, 1.0f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.empty());
}

// Bottom frustum plane: focal*y + (H/2)*z >= 0  →  y + z >= 0.
// At z=5, the bottom boundary is y = −5. Triangle entirely below.
TEST(ClipTriangles, AllVerticesOutsideBottomFrustum_ReturnsEmpty) {
    Triangle3 tri = makeTri(makeVertex(0.0f, -8.0f, 5.0f),
                            makeVertex(1.0f, -8.0f, 5.0f),
                            makeVertex(0.0f, -7.0f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.empty());
}

// Top frustum plane: −focal*y + (H/2)*z >= 0  →  z − y >= 0.
// At z=5, the top boundary is y = 5. Triangle entirely above.
TEST(ClipTriangles, AllVerticesOutsideTopFrustum_ReturnsEmpty) {
    Triangle3 tri = makeTri(makeVertex(0.0f, 8.0f, 5.0f),
                            makeVertex(1.0f, 8.0f, 5.0f),
                            makeVertex(0.0f, 7.0f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.empty());
}

// ── near-plane partial clipping
// ───────────────────────────────────────────────

// Two vertices inside (d=0.9), one vertex behind near plane (d=−0.05).
// S-H clips the single outside vertex, producing a quad (4 vertices).
// Fan triangulation of a quad yields 2 triangles.
TEST(ClipTriangles, OneVertexBehindNearPlane_ReturnsTwoTriangles) {
    // v2 is just barely behind the near plane; v0 and v1 are clearly in
    // front. All three are near the screen centre so the lateral
    // frustum planes leave the clipped intersection points untouched.
    Triangle3 tri = makeTri(
        makeVertex(-0.1f, -0.1f, 1.0f), makeVertex(0.1f, -0.1f, 1.0f),
        makeVertex(0.0f, 0.0f, 0.05f)  // behind: d = 0.05 − 0.1 = −0.05
    );
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.size() == 2);
}

// One vertex inside (d=0.9), two vertices behind near plane (d=−0.05).
// S-H keeps one vertex and adds two intersection points: 3 vertices → 1
// triangle.
TEST(ClipTriangles, TwoVerticesBehindNearPlane_ReturnsOneTriangle) {
    Triangle3 tri = makeTri(makeVertex(0.0f, 0.0f, 1.0f),   // inside
                            makeVertex(0.1f, 0.0f, 0.05f),  // behind
                            makeVertex(-0.1f, 0.0f, 0.05f)  // behind
    );
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.size() == 1);
}

// A vertex sitting exactly on the near plane (z == near_z) has d == 0,
// which satisfies d >= 0 and is treated as inside. The triangle should
// survive.
TEST(ClipTriangles, VertexExactlyOnNearPlane_IsRetained) {
    Triangle3 tri = makeTri(
        makeVertex(0.0f, 0.0f, NEAR_Z),  // exactly on boundary
        makeVertex(1.0f, 0.0f, 5.0f), makeVertex(-1.0f, 0.0f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(!result.empty());
}

// ── projection accuracy
// ───────────────────────────────────────────────────────

// A vertex at camera-space (0, 0, z) must project to the screen centre
// (W/2, H/2).
TEST(ClipTriangles, VertexAtOriginXY_ProjectsToScreenCentre) {
    Triangle3 tri = makeTri(
        makeVertex(0.0f, 0.0f, 5.0f),  // should hit (100, 100)
        makeVertex(0.5f, -0.5f, 5.0f), makeVertex(-0.5f, -0.5f, 5.0f));
    auto clipped = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(clipped.size() == 1);

    Triangle2 projected = projectTriangle(clipped[0], FOCAL, W, H);

    bool found = false;
    for (const Eigen::Vector2f p :
         {projected.vertex_A.position, projected.vertex_B.position,
          projected.vertex_C.position}) {
        if (std::abs(p[0] - W / 2.0f) < 0.01f &&
            std::abs(p[1] - H / 2.0f) < 0.01f)
            found = true;
    }
    CHECK(found);
}

// x_screen = (x * focal / z) + W/2.  For (x=1, z=1): 1*100/1 + 100 =
// 200 = W. Verifies that focal length and perspective division are
// applied correctly.
TEST(ClipTriangles, ProjectionScalesWithFocalLength) {
    Triangle3 tri = makeTri(
        makeVertex(0.0f, 0.0f, 1.0f),  // projects to (100, 100)
        makeVertex(1.0f, 0.0f,
                   1.0f),  // projects to (200, 100) — right edge
        makeVertex(0.0f, 1.0f,
                   1.0f)  // projects to (100, 200) — bottom edge
    );
    auto clipped = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(clipped.size() == 1);

    Triangle2 projected = projectTriangle(clipped[0], FOCAL, W, H);

    // Vertex (1,0,1) → screen x = W, y = H/2
    bool found_right_edge = false;
    for (const Eigen::Vector2f p :
         {projected.vertex_A.position, projected.vertex_B.position,
          projected.vertex_C.position}) {
        if (std::abs(p[0] - W) < 0.01f &&
            std::abs(p[1] - H / 2.0f) < 0.01f)
            found_right_edge = true;
    }
    CHECK(found_right_edge);
}

// ── color interpolation
// ───────────────────────────────────────────────────────

// When the near plane cuts an edge, the new vertex should have a
// linearly interpolated colour between the two endpoints.
//
// Setup: v0 and v1 are black (0,0,0) at z=0.5 (d=0.4, inside).
//        v2 is bright (200,200,200) at z=−0.5 (d=−0.6, outside).
//
// Intersection t = d_inside / (d_inside − d_outside)
//                = 0.4 / (0.4 − (−0.6)) = 0.4
//
// Expected intersection colour: 0 + 0.4 * 200 = 80 per channel.
TEST(ClipTriangles, NearPlaneClip_InterpolatesColourAtIntersection) {
    Triangle3 tri = makeTri(
        makeVertex(-0.1f, 0.0f, 0.5f, 0, 0, 0),       // inside,  black
        makeVertex(0.1f, 0.0f, 0.5f, 0, 0, 0),        // inside,  black
        makeVertex(0.0f, 0.0f, -0.5f, 200, 200, 200)  // outside, bright
    );
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.size() == 2);

    // At least one vertex across the two fan triangles should carry the
    // interpolated colour (80, 80, 80).
    bool found_interpolated = false;
    for (const auto& t : result) {
        for (const Vertex3 v : {t.vertex_A, t.vertex_B, t.vertex_C}) {
            if (v.color[0] == 80 && v.color[1] == 80 &&
                v.color[2] == 80)
                found_interpolated = true;
        }
    }
    CHECK(found_interpolated);
}

// All resulting vertex colours must remain within the range spanned by
// the input colours — clipping must never extrapolate outside [0, 200].
TEST(ClipTriangles, ClippedColours_StayWithinInputRange) {
    Triangle3 tri =
        makeTri(makeVertex(-0.1f, 0.0f, 0.5f, 0, 0, 0),
                makeVertex(0.1f, 0.0f, 0.5f, 0, 0, 0),
                makeVertex(0.0f, 0.0f, -0.5f, 200, 200, 200));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);

    for (const auto& t : result) {
        for (const Vertex3 v : {t.vertex_A, t.vertex_B, t.vertex_C}) {
            CHECK(v.color[0] >= 0 && v.color[0] <= 200);
            CHECK(v.color[1] >= 0 && v.color[1] <= 200);
            CHECK(v.color[2] >= 0 && v.color[2] <= 200);
        }
    }
}

// ── combined frustum planes
// ───────────────────────────────────────────────────

// Triangle mostly visible but with one vertex behind the near plane
// that, after clipping, also grazes the left frustum boundary. The
// visible portion is still non-trivial and must not be discarded.
TEST(ClipTriangles, StraddlingNearAndLeftFrustum_IsNonEmpty) {
    Triangle3 tri =
        makeTri(makeVertex(-3.0f, 0.0f, 5.0f),  // inside all planes
                makeVertex(1.0f, 0.0f, 5.0f),   // inside all planes
                makeVertex(-1.0f, 0.0f, -5.0f)  // behind near plane
        );
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(!result.empty());
}

// A triangle whose vertices are simultaneously outside two frustum
// planes (left AND bottom here) should be completely clipped away.
TEST(ClipTriangles, TriangleOutsideTwoFrustumPlanes_ReturnsEmpty) {
    // At z=5: left boundary x=−5, bottom boundary y=−5.
    // All vertices are beyond both boundaries.
    Triangle3 tri = makeTri(makeVertex(-8.0f, -8.0f, 5.0f),
                            makeVertex(-7.0f, -8.0f, 5.0f),
                            makeVertex(-8.0f, -7.0f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(result.empty());
}

// A very large triangle that completely contains the frustum pyramid
// should still clip down to a visible polygon — the output must be
// non-empty.
TEST(ClipTriangles, HugeTriangleCoveringEntireFrustum_IsNonEmpty) {
    Triangle3 tri = makeTri(makeVertex(-50.0f, -50.0f, 5.0f),
                            makeVertex(50.0f, -50.0f, 5.0f),
                            makeVertex(0.0f, 50.0f, 5.0f));
    auto result = clipTriangle(tri, FOCAL, W, H, NEAR_Z);
    CHECK(!result.empty());
}

int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}
