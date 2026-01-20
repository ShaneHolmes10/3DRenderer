
#ifndef MATH_POSITION_OBJECT_H
#define MATH_POSITION_OBJECT_H

#include <Eigen/Dense>

/**
 * @brief This class is a representation of a mathematical object that
 * contains positional information.
 * 
 */
class MathPositionObject {
protected:
    /**
     * @brief This vector holds the position of the obejct.
     * 
     */
    Eigen::Vector3d placement_vector;
    
protected:
 
    /**
     * @brief Construct a new Math Position Object. 
     * 
     * @param ox length of vectors x component
     * @param oy length of vectors y component
     * @param oz length of vectors z component
     */
    MathPositionObject(float ox = 0, float oy = 0, float oz = 0);

public:

    /**
     * @brief Set the ox value of the position. 
     * 
     * @param value to set component to
     */
    void set_ox(float value);

    /**
     * @brief Set the oy value of the position.
     * 
     * @param value to set component to 
     */
    void set_oy(float value);

    /**
     * @brief Set the oz value of the position.
     * 
     * @param value to set component to
     */
    void set_oz(float value);

    /**
     * @brief Get the placement vector object (ox, oy, oz).
     * 
     * @return const Eigen::Vector3d& 
     */
    const Eigen::Vector3d& get_placement_vector() const;

    /**
     * @brief This static method allows us to generate a rotation
     * matrix about the x axis for the given input value. 
     * 
     * @param value angle of rotation around the x axis
     * @return Eigen::Matrix3d X rotation matrix
     */
    static Eigen::Matrix3d calculate_rotation_matrix_x(float value);
    
    /**
     * @brief This static method allows us to generate a rotation
     * matrix about the y axis for the given input value.
     * 
     * @param value angle of rotation around the y axis
     * @return Eigen::Matrix3d Y rotation matrix
     */
    static Eigen::Matrix3d calculate_rotation_matrix_y(float value);
    
    /**
     * @brief This static method allows us to generate a rotation
     * matrix about the z axis for the given input value.
     * 
     * @param value angle of rotation around the z axis
     * @return Eigen::Matrix3d Z rotation matrix
     */
    static Eigen::Matrix3d calculate_rotation_matrix_z(float value);

    /**
     * @brief This static method extracts the transformation matrix for the
     * given inputs of angles and position.  
     * 
     * @param angs angles about (X, Y, Z) for the transformation matrix
     * @param plac placement about (ox, oy, oz) for the transformation matrix
     * @return Eigen::Matrix4d transformation matrix
     */
    static Eigen::Matrix4d calculate_transformation_matrix(Eigen::Vector3d angs, Eigen::Vector3d plac);
    
    
};


#endif
