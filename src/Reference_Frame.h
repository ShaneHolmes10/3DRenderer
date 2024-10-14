
#ifndef REFERENCE_FRAME_H
#define REFERENCE_FRAME_H

#include "Math_Position_Object.h"
#include <Eigen/Dense>
#include <vector>

class VectorObject;


/**
 * @brief This class represents a mathematical reference frame.
 * 
 */
class ReferenceFrame : public MathPositionObject {
private:

    /**
     * @brief This holds the current reference frames transformation
     * matrix.
     * 
     */
    Eigen::Matrix4d transformation_matrix;
    
    /**
     * @brief This holds the angles that encode the orientation of the
     * reference frame.
     * 
     */
    Eigen::Vector3d angles;

    /**
     * @brief This is a list of all the children of this reference frame.
     * 
     */
    std::vector<MathPositionObject*> children_list;

public:
    /**
     * @brief This holds the current reference frames parent.
     * 
     */
    ReferenceFrame* defining_frame;

public:
    
    /**
     * @brief This specifies that this constructor should be removed.
     * 
     * @param ox 
     * @param oy 
     * @param oz 
     */
    ReferenceFrame(float ox, float oy, float oz) = delete;

    /**
     * @brief Construct a new Reference Frame object. based on the position 
     * and angles.
     * 
     * @param ox x component of the position of the reference frame
     * @param oy y component of the position of the reference frame
     * @param oz z component of the position of the reference frame
     * @param ax angle of rotation about the x axis
     * @param ay angle of rotation about the y axis
     * @param az angle of rotation about the z axis
     */
    ReferenceFrame(float ox = 0, float oy = 0, float oz = 0, float ax = 0, float ay = 0, float az = 0);
    
    /**
     * @brief Set the ax object.
     * 
     * @param value 
     */
    void set_ax(float value);

    /**
     * @brief Set the ay object.
     * 
     * @param value 
     */
    void set_ay(float value);

    /**
     * @brief Set the az object.
     * 
     * @param value 
     */
    void set_az(float value);

    /**
     * @brief Set the ox object.
     * 
     * @param value 
     */
    void set_ox(float value);

    /**
     * @brief Set the oy object.
     * 
     * @param value 
     */
    void set_oy(float value);

    /**
     * @brief Set the oz object.
     * 
     * @param value 
     */
    void set_oz(float value);
    
    /**
     * @brief Get the angles of the reference frame.
     * 
     * @return const Eigen::Vector3d& vector of angles
     */
    const Eigen::Vector3d& get_angles() const;

    /**
     * @brief Get the transformation matrix of the reference frame.
     * 
     * @return const Eigen::Matrix4d transformation matrix
     */
    const Eigen::Matrix4d get_transformation_matrix() const;

    /**
     * @brief add a child reference frame to this reference frame
     * 
     * @param child 
     */
    void add(ReferenceFrame& child);

    /**
     * @brief add a child vector object to this reference frame
     * 
     * @param child 
     */
    void add(VectorObject& child);

    /**
     * @brief Get the expressed representation of this reference frame relative
     * to the expressing reference frame.
     * 
     * @param expressing_frame 
     * @return ReferenceFrame* 
     */
    ReferenceFrame* get_expressed_in(ReferenceFrame& expressing_frame);


};


#endif
