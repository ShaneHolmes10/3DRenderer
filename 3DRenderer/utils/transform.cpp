
#include "utils/transform.h"

#include <iostream>

void Transform::recalculateMatrix() {
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();

    Eigen::AngleAxisf rotX(angles[0], Eigen::Vector3f::UnitX());
    Eigen::AngleAxisf rotY(angles[1], Eigen::Vector3f::UnitY());
    Eigen::AngleAxisf rotZ(angles[2], Eigen::Vector3f::UnitZ());

    // Combine into rotation matrix
    Eigen::Matrix3f rotation_matrix =
        (rotZ * rotY * rotX).toRotationMatrix();

    transform.translate(position);
    transform.rotate(rotation_matrix);
    transform.scale(scale);

    matrix = transform.matrix();
}

Transform::Transform(const Eigen::Vector3f& position,
                     const Eigen::Vector3f& angles,
                     const Eigen::Vector3f& scale)
    : position(position), angles(angles), scale(scale) {
    recalculateMatrix();
}

Transform::Transform(const Eigen::Vector3f& position,
                     const Eigen::Vector3f& angles)
    : position(position), angles(angles), scale(1.0f, 1.0f, 1.0f) {
    recalculateMatrix();
}

void Transform::setAngleX(float value) {
    angles[0] = value;
    recalculateMatrix();
}

void Transform::setAngleY(float value) {
    angles[1] = value;
    recalculateMatrix();
}

void Transform::setAngleZ(float value) {
    angles[2] = value;
    recalculateMatrix();
}

void Transform::setPositionX(float value) {
    position[0] = value;
    recalculateMatrix();
}

void Transform::setPositionY(float value) {
    position[1] = value;
    recalculateMatrix();
}

void Transform::setPositionZ(float value) {
    position[2] = value;
    recalculateMatrix();
}

void Transform::setScaleX(float value) {
    scale[0] = value;
    recalculateMatrix();
}

void Transform::setScaleY(float value) {
    scale[1] = value;
    recalculateMatrix();
}

void Transform::setScaleZ(float value) {
    scale[2] = value;
    recalculateMatrix();
}

const Eigen::Vector3f& Transform::getAngles() const { return angles; }

const Eigen::Vector3f& Transform::getPosition() const {
    return position;
}

const Eigen::Vector3f& Transform::getScale() const { return scale; }

const Eigen::Matrix4f& Transform::getMatrix() const { return matrix; }
