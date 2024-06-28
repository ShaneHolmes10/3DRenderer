
#include "Math_Position_Object.h"


MathPositionObject::MathPositionObject(float ox, float oy, float oz) 
    : defining_frame(nullptr), placement_vector(ox, oy, oz) {
    
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


