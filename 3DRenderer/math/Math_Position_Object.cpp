
#include "Math_Position_Object.h"


MathPositionObject::MathPositionObject(float ox, float oy, float oz) 
    : placement_vector(ox, oy, oz) {
    
}

void MathPositionObject::set_ox(float value) {
    placement_vector.x() = value;
}

void MathPositionObject::set_oy(float value) {
    placement_vector.y() = value;
}

void MathPositionObject::set_oz(float value) {
    placement_vector.z() = value;
}

const Eigen::Vector3d& MathPositionObject::get_placement_vector() const {
    return placement_vector;
}

Eigen::Matrix3d MathPositionObject::calculate_rotation_matrix_x(float value) {
    Eigen::Matrix3d result_matrix;

    result_matrix <<   1, 0,          0,
                       0, cos(value), -sin(value),
                       0, sin(value), cos(value);

    return result_matrix;
}

Eigen::Matrix3d MathPositionObject::calculate_rotation_matrix_y(float value) {
    Eigen::Matrix3d result_matrix;

    result_matrix <<   cos(value),  0,   sin(value),
                       0,           1,   0,
                       -sin(value), 0,   cos(value);

    return result_matrix;
}

Eigen::Matrix3d MathPositionObject::calculate_rotation_matrix_z(float value) {
    Eigen::Matrix3d result_matrix;

    result_matrix <<   cos(value),  -sin(value), 0,
                       sin(value),  cos(value),  0,
                       0,           0,           1;

    return result_matrix;
}

Eigen::Matrix4d MathPositionObject::calculate_transformation_matrix(Eigen::Vector3d angs, Eigen::Vector3d plac) {
    
    Eigen::Matrix3d rotation_matrix = 
        MathPositionObject::calculate_rotation_matrix_z(angs.z())*
        MathPositionObject::calculate_rotation_matrix_y(angs.y())*
        MathPositionObject::calculate_rotation_matrix_x(angs.x());

    Eigen::Matrix4d transformation_matrix;
    transformation_matrix << 
        rotation_matrix(0, 0), rotation_matrix(0, 1), rotation_matrix(0, 2), plac.x(),
        rotation_matrix(1, 0), rotation_matrix(1, 1), rotation_matrix(1, 2), plac.y(),
        rotation_matrix(2, 0), rotation_matrix(2, 1), rotation_matrix(2, 2), plac.z(),
        0,                     0,                     0,                     1;

    return  transformation_matrix;

}
