
#include "Vector_Object.h"
#include <iostream>

VectorObject::VectorObject(float ox, float oy, float oz) : 
    MathPositionObject(ox, oy, oz) {

}

Eigen::Vector3d VectorObject::get_transformed_vector() {
    Eigen::Vector4d extended_vector;
    extended_vector << placement_vector, 1.0;

    return defining_frame->get_transformation_matrix()*extended_vector;

}

VectorObject* VectorObject::get_expressed_in(ReferenceFrame& expressing_frame) {
    Eigen::Vector4d extended_vector;
    extended_vector << placement_vector, 1.0;

    Eigen::Vector3d result_vector;
    result_vector = expressing_frame.get_transformation_matrix().inverse()*extended_vector;

    return new VectorObject(result_vector.x(), result_vector.y(), result_vector.z());

}






