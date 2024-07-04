
#ifndef VECTOR_OBJECT_H
#define VECTOR_OBJECT_H

#include "Math_Position_Object.h"
#include "Reference_Frame.h"
#include <Eigen/Dense>
#include <vector>


class VectorObject : public MathPositionObject {
public:
    ReferenceFrame* defining_frame;

public:
    VectorObject(float ox, float oy, float oz);
    Eigen::Vector3d get_transformed_vector();
    VectorObject* get_expressed_in(ReferenceFrame& expressing_frame);

};


#endif
