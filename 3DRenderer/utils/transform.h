
#pragma once

#include <Eigen/Dense>

/**
 * @brief Represents a 3D transformation with position, rotation, and
 * scale.
 *
 * This class encapsulates the transformation state of an object in 3D
 * space, including its position, rotation angles, and scale factors.
 * The combined transformation matrix is automatically recalculated
 * whenever any component is modified.
 */
class Transform {
   private:
    /**
     * @brief Position of the object in 3D space (x, y, z).
     */
    Eigen::Vector3f position;

    /**
     * @brief Rotation angles in radians (rotation about x, y, z axes).
     */
    Eigen::Vector3f angles;

    /**
     * @brief Scale factors along each axis (sx, sy, sz).
     */
    Eigen::Vector3f scale;

    /**
     * @brief The combined 4x4 transformation matrix.
     *
     * This matrix represents the complete transformation (translation,
     * rotation, and scale) and is automatically recalculated whenever
     * position, angles, or scale is modified.
     */
    Eigen::Matrix4f matrix;

    /**
     * @brief Recalculates the transformation matrix from position,
     * angles, and scale.
     *
     * This method combines translation, rotation (from Euler angles),
     * and scale into a single 4x4 transformation matrix. Called
     * automatically by all setters.
     */
    void recalculateMatrix();

   public:
    /**
     * @brief Construct a Transform with position, rotation, and scale.
     *
     * @param position Position vector (x, y, z)
     * @param angles Euler rotation angles in radians (rx, ry, rz)
     * @param scale Scale factors (sx, sy, sz)
     */
    Transform(const Eigen::Vector3f& position,
              const Eigen::Vector3f& angles,
              const Eigen::Vector3f& scale);

    /**
     * @brief Construct a Transform with position and rotation (default
     * scale of 1,1,1).
     *
     * @param position Position vector (x, y, z)
     * @param angles Euler rotation angles in radians (rx, ry, rz)
     */
    Transform(const Eigen::Vector3f& position,
              const Eigen::Vector3f& angles);

    /**
     * @brief Set the rotation angle about the X axis.
     *
     * @param value Rotation angle in radians
     */
    void setAngleX(float value);

    /**
     * @brief Set the rotation angle about the Y axis.
     *
     * @param value Rotation angle in radians
     */
    void setAngleY(float value);

    /**
     * @brief Set the rotation angle about the Z axis.
     *
     * @param value Rotation angle in radians
     */
    void setAngleZ(float value);

    /**
     * @brief Set the X component of the position.
     *
     * @param value Position along X axis
     */
    void setPositionX(float value);

    /**
     * @brief Set the Y component of the position.
     *
     * @param value Position along Y axis
     */
    void setPositionY(float value);

    /**
     * @brief Set the Z component of the position.
     *
     * @param value Position along Z axis
     */
    void setPositionZ(float value);

    /**
     * @brief Set the X component of the scale.
     *
     * @param value Scale factor along X axis
     */
    void setScaleX(float value);

    /**
     * @brief Set the Y component of the scale.
     *
     * @param value Scale factor along Y axis
     */
    void setScaleY(float value);

    /**
     * @brief Set the Z component of the scale.
     *
     * @param value Scale factor along Z axis
     */
    void setScaleZ(float value);

    /**
     * @brief Get the Euler rotation angles.
     *
     * @return const Eigen::Vector3f& Reference to rotation angles (rx,
     * ry, rz) in radians
     */
    const Eigen::Vector3f& getAngles() const;

    /**
     * @brief Get the position vector.
     *
     * @return const Eigen::Vector3f& Reference to position (x, y, z)
     */
    const Eigen::Vector3f& getPosition() const;

    /**
     * @brief Get the scale factors.
     *
     * @return const Eigen::Vector3f& Reference to scale (sx, sy, sz)
     */
    const Eigen::Vector3f& getScale() const;

    /**
     * @brief Get the combined transformation matrix.
     *
     * @return const Eigen::Matrix4f& Reference to 4x4 transformation
     * matrix
     */
    const Eigen::Matrix4f& getMatrix() const;
};
