
#ifndef VECTOR_OBJECT_H
#define VECTOR_OBJECT_H

#include "Math_Position_Object.h"
#include "Reference_Frame.h"
#include <Eigen/Dense>
#include <vector>

/**
 * @brief This class represents a vector but in the context
 * of it's relationship to a referenceframe. So the values of 
 * this object change depending on it's reference frame parent.
 * 
 */
class VectorObject : public MathPositionObject {
public:

    /**
     * @brief This is the parent reference frame that contains 
     * this object.
     * 
     */
    ReferenceFrame* defining_frame;

public:

    /**
     * @brief Construct a new Vector Object object.
     * 
     * @param ox x component of the vector
     * @param oy y component of the vector
     * @param oz z component of the vector
     */
    VectorObject(float ox = 0, float oy = 0, float oz = 0);

    /**
     * @brief Get the transformed vector object.
     * 
     * @return Eigen::Vector3d 
     */
    Eigen::Vector3d get_transformed_vector();

    /**
     * @brief Get this object expressed in the input reference
     * frame.
     * 
     * @param expressing_frame input expressing reference frame
     * @return VectorObject* resultant expressed vector
     */
    VectorObject* get_expressed_in(ReferenceFrame& expressing_frame);

};


#endif
