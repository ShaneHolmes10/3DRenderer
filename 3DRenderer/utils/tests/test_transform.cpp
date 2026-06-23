#include <Eigen/Dense>

#include "CppUnitLite/TestHarness.h"
#include "utils/transform.h"

TEST(Transform, ConstructWithPositionRotationScale) {
    Eigen::Vector3f pos(1.0f, 2.0f, 3.0f);
    Eigen::Vector3f rot(0.5f, 1.0f, 1.5f);
    Eigen::Vector3f scale(2.0f, 3.0f, 4.0f);

    Transform t(pos, rot, scale);

    CHECK((t.getPosition() - pos).norm() < 0.01f);
    CHECK((t.getAngles() - rot).norm() < 0.01f);
    CHECK((t.getScale() - scale).norm() < 0.01f);
}

TEST(Transform, ConstructWithPositionRotationDefaultScale) {
    Eigen::Vector3f pos(1.0f, 2.0f, 3.0f);
    Eigen::Vector3f rot(0.5f, 1.0f, 1.5f);

    Transform t(pos, rot);

    CHECK((t.getPosition() - pos).norm() < 0.01f);
    CHECK((t.getAngles() - rot).norm() < 0.01f);
    CHECK((t.getScale() - Eigen::Vector3f(1.0f, 1.0f, 1.0f)).norm() <
          0.01f);
}

TEST(Transform, SetPositionX) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setPositionX(5.0f);

    CHECK(std::abs(t.getPosition()[0] - 5.0f) < 0.01f);
    CHECK(std::abs(t.getPosition()[1] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getPosition()[2] - 0.0f) < 0.01f);
}

TEST(Transform, SetPositionY) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setPositionY(7.0f);

    CHECK(std::abs(t.getPosition()[0] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getPosition()[1] - 7.0f) < 0.01f);
    CHECK(std::abs(t.getPosition()[2] - 0.0f) < 0.01f);
}

TEST(Transform, SetPositionZ) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setPositionZ(9.0f);

    CHECK(std::abs(t.getPosition()[0] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getPosition()[1] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getPosition()[2] - 9.0f) < 0.01f);
}

TEST(Transform, SetAngleX) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setAngleX(1.5f);

    CHECK(std::abs(t.getAngles()[0] - 1.5f) < 0.01f);
    CHECK(std::abs(t.getAngles()[1] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getAngles()[2] - 0.0f) < 0.01f);
}

TEST(Transform, SetAngleY) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setAngleY(2.0f);

    CHECK(std::abs(t.getAngles()[0] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getAngles()[1] - 2.0f) < 0.01f);
    CHECK(std::abs(t.getAngles()[2] - 0.0f) < 0.01f);
}

TEST(Transform, SetAngleZ) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setAngleZ(2.5f);

    CHECK(std::abs(t.getAngles()[0] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getAngles()[1] - 0.0f) < 0.01f);
    CHECK(std::abs(t.getAngles()[2] - 2.5f) < 0.01f);
}

TEST(Transform, SetScaleX) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setScaleX(3.0f);

    CHECK(std::abs(t.getScale()[0] - 3.0f) < 0.01f);
    CHECK(std::abs(t.getScale()[1] - 1.0f) < 0.01f);
    CHECK(std::abs(t.getScale()[2] - 1.0f) < 0.01f);
}

TEST(Transform, SetScaleY) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setScaleY(4.0f);

    CHECK(std::abs(t.getScale()[0] - 1.0f) < 0.01f);
    CHECK(std::abs(t.getScale()[1] - 4.0f) < 0.01f);
    CHECK(std::abs(t.getScale()[2] - 1.0f) < 0.01f);
}

TEST(Transform, SetScaleZ) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);
    t.setScaleZ(5.0f);

    CHECK(std::abs(t.getScale()[0] - 1.0f) < 0.01f);
    CHECK(std::abs(t.getScale()[1] - 1.0f) < 0.01f);
    CHECK(std::abs(t.getScale()[2] - 5.0f) < 0.01f);
}

TEST(Transform, TransformationMatrixIsIdentityForDefaults) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);

    Eigen::Matrix4f identity = Eigen::Matrix4f::Identity();

    CHECK((t.getMatrix() - identity).norm() < 0.01f);
}

TEST(Transform, TransformationMatrixUpdatesOnPositionChange) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);

    Eigen::Matrix4f matrix_before = t.getMatrix();

    t.setPositionX(5.0f);

    Eigen::Matrix4f matrix_after = t.getMatrix();

    CHECK((matrix_before - matrix_after).norm() > 0.01f);
}

TEST(Transform, TransformationMatrixUpdatesOnRotationChange) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);

    Eigen::Matrix4f matrix_before = t.getMatrix();

    t.setAngleY(1.57f);

    Eigen::Matrix4f matrix_after = t.getMatrix();

    CHECK((matrix_before - matrix_after).norm() > 0.01f);
}

TEST(Transform, TransformationMatrixUpdatesOnScaleChange) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);

    Eigen::Matrix4f matrix_before = t.getMatrix();

    t.setScaleX(2.0f);

    Eigen::Matrix4f matrix_after = t.getMatrix();

    CHECK((matrix_before - matrix_after).norm() > 0.01f);
}

TEST(Transform, MultipleSettersWork) {
    Eigen::Vector3f pos(0.0f, 0.0f, 0.0f);
    Eigen::Vector3f rot(0.0f, 0.0f, 0.0f);

    Transform t(pos, rot);

    t.setPositionX(1.0f);
    t.setPositionY(2.0f);
    t.setPositionZ(3.0f);
    t.setAngleX(0.5f);
    t.setAngleY(1.0f);
    t.setAngleZ(1.5f);
    t.setScaleX(2.0f);
    t.setScaleY(3.0f);
    t.setScaleZ(4.0f);

    CHECK((t.getPosition() - Eigen::Vector3f(1.0f, 2.0f, 3.0f)).norm() <
          0.01f);
    CHECK((t.getAngles() - Eigen::Vector3f(0.5f, 1.0f, 1.5f)).norm() <
          0.01f);
    CHECK((t.getScale() - Eigen::Vector3f(2.0f, 3.0f, 4.0f)).norm() <
          0.01f);
}

int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}