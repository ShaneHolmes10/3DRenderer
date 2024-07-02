
#ifndef MATH_POSITION_OBJECT_H
#define MATH_POSITION_OBJECT_H

#include <Eigen/Dense>

class MathPositionObject {
protected:
    Eigen::Vector3d placement_vector;
    
protected:
    MathPositionObject(float ox = 0, float oy = 0, float oz = 0);

public:
    void set_ox(float value);
    void set_oy(float value);
    void set_oz(float value);
    const Eigen::Vector3d& get_placement_vector() const;

    static Eigen::Matrix3d calculate_rotation_matrix_x(float value);
    static Eigen::Matrix3d calculate_rotation_matrix_y(float value);
    static Eigen::Matrix3d calculate_rotation_matrix_z(float value);

    static Eigen::Matrix4d calculate_transformation_matrix(Eigen::Vector3d angs, Eigen::Vector3d plac);
    
    
};


#endif
