
#include "Reference_Frame.h"
#include "Vector_Object.h"
#include <iostream>

ReferenceFrame::ReferenceFrame(float ox, float oy, float oz, float ax, float ay, float az) 
    : defining_frame(nullptr),
    MathPositionObject(ox, oy, oz), 
    angles(ax, ay, az),
    children_list() {

    transformation_matrix = MathPositionObject::calculate_transformation_matrix(angles, placement_vector);
    
}

void ReferenceFrame::set_ax(float value) {
    angles.x() = value;
    transformation_matrix = MathPositionObject::calculate_transformation_matrix(angles, placement_vector);
}

void ReferenceFrame::set_ay(float value) {
    angles.y() = value;
    transformation_matrix = MathPositionObject::calculate_transformation_matrix(angles, placement_vector);

}

void ReferenceFrame::set_az(float value) {
    angles.z() = value;
    transformation_matrix = MathPositionObject::calculate_transformation_matrix(angles, placement_vector);

}

void ReferenceFrame::set_ox(float value) {
    placement_vector.x() = value;
    transformation_matrix = MathPositionObject::calculate_transformation_matrix(angles, placement_vector);

}

void ReferenceFrame::set_oy(float value) {
    placement_vector.y() = value;
    transformation_matrix = MathPositionObject::calculate_transformation_matrix(angles, placement_vector);

}

void ReferenceFrame::set_oz(float value) {
    placement_vector.z() = value;
    transformation_matrix = MathPositionObject::calculate_transformation_matrix(angles, placement_vector);

}

const Eigen::Vector3d& ReferenceFrame::get_angles() const {
    return angles;

}

const Eigen::Matrix4d ReferenceFrame::get_transformation_matrix() const {
    if(defining_frame != nullptr) {
        
        return defining_frame->get_transformation_matrix()*transformation_matrix;
    } else {
        
        return transformation_matrix;
    }
    
}

void ReferenceFrame::add(ReferenceFrame& child) {
    children_list.push_back(&child);
    child.defining_frame = this;

}

void ReferenceFrame::add(VectorObject& child) {
    children_list.push_back(&child);
    child.defining_frame = this;

}

ReferenceFrame* ReferenceFrame::get_expressed_in(ReferenceFrame& expressing_frame) { 
        
    Eigen::Matrix4d result_matrix = expressing_frame.get_transformation_matrix().inverse() * transformation_matrix;

    Eigen::Matrix3d rotation_matrix = result_matrix.block<3, 3>(0,0);
    Eigen::Vector3d placement_vector = result_matrix.block<3, 1>(0, 3);

    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); 

    return new ReferenceFrame(placement_vector.x(), placement_vector.y(), placement_vector.z(),
                                euler_angles.z(), euler_angles.y(), euler_angles.x());

}



