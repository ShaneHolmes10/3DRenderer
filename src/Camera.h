
#ifndef Camera_H
#define Camera_H

#include "Reference_Frame.h"
#include "Stage.h"
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <vector>


class VectorObject;
class Stage;

/**
 * @brief This class represents a camera object that will take a picture of the 3d 
 * environment and represent this as an image. 
 * 
 * This class handles all the projection and drawing necessary to take a picture. 
 * 
 * In order to facilitate this, the object needs to be added to a stage, the stage
 * contains all the vectors and surfaces this means the camera must be added to it
 * so it can take the relavant picture.
 * 
 */
class Camera : public ReferenceFrame {

private:

    /**
     * @brief This is a pointer to the main stage
     * that holds all of the objects that the camera
     * can take a picture of.
     * 
     */
    Stage* main_stage;

    /**
     * @brief This is the Field Of View length.
     * 
     */
    float FOV_length;

    /**
     * @brief This represents the width of a photo taken.
     * 
     */
    int width;

    /**
     * @brief This represents the height of a photo taken.
     * 
     */
    int height;    

    /**
     * @brief right plane of the frustrum.
     * 
     */
    VectorObject right_FOV_plane_normal;
    
    /**
     * @brief left plane of the frustrum.
     * 
     */
    VectorObject left_FOV_plane_normal;
    
    /**
     * @brief top plane of the frustrum.
     * 
     */
    VectorObject top_FOV_plane_normal;
    
    /**
     * @brief bottom plane of the frustrum.
     * 
     */
    VectorObject bottom_FOV_plane_normal;


private:
    
    /**
     * @brief This generates the frustum plane normals based on the FOV length
     * and the image width and height. This is a relevant part in generating
     * the geometry of the frustrum.
     * 
     */
    void generate_FOV_normals();


public:
    /**
     * @brief Construct a new Camera object.
     * 
     * @param ox x position of the camera in space
     * @param oy y position of the camera in space
     * @param oz z position of the camera in space
     * @param ax angle about x axis of the camera in space
     * @param ay angle about y axis of the camera in space
     * @param az angle about z axis of the camera in space
     */
    Camera(float ox = 0, float oy = 0, float oz = 0, float ax = 0, float ay = 0, float az = 0);

    /**
     * @brief Set the stage object.
     * The stage object provides the objects in a "scene" 
     * that the camera needs to take a picture of.
     * 
     * @param stage 
     */
    void set_stage(Stage& stage);

    /**
     * @brief Set the FOV length object.
     * This value controls the Field Of View, this will
     * control how narrow or wide the FOV will be, which will 
     * affect the percieved size of objects and number of objects 
     * seen.
     * 
     * @param num value of the FOV
     * @return * void 
     */
    void set_FOV_length(float num);
    
    /**
     * @brief Set the picture width height object.
     * 
     * @param w width of the photo
     * @param h height of the photo
     */
    void set_picture_width_height(int w, int h);

    /**
     * @brief This will determine if the input vector object
     * is outside the right plane of the camera frustrum. 
     * This is necessary for functions like vector clipping
     * and for drawing efficiency.
     * 
     * @param environment_vector testing vector object
     * @return true means the vector lies outside the right plane
     * @return false means the vector lies inside the right plane
     */
    bool check_vector_outside_FOV_plane_right(VectorObject* environment_vector);
    
    /**
     * @brief This will determine if the input vector object
     * is outside the left plane of the camera frustrum. 
     * This is necessary for functions like vector clipping
     * and for drawing efficiency.
     * 
     * @param environment_vector testing vector object
     * @return true means the vector lies outside the left plane
     * @return false means the vector lies inside the left plane
     */
    bool check_vector_outside_FOV_plane_left(VectorObject* environment_vector);
    
    /**
     * @brief This will determine if the input vector object
     * is outside the top plane of the camera frustrum. 
     * This is necessary for functions like vector clipping
     * and for drawing efficiency.
     * 
     * @param environment_vector testing vector object
     * @return true means the vector lies outside the top plane
     * @return false means the vector lies inside the top plane
     */
    bool check_vector_outside_FOV_plane_top(VectorObject* environment_vector);
    
    /**
     * @brief This will determine if the input vector object
     * is outside the bottom plane of the camera frustrum. 
     * This is necessary for functions like vector clipping
     * and for drawing efficiency.
     * 
     * @param environment_vector testing vector object
     * @return true means the vector lies outside the bottom plane
     * @return false means the vector lies inside the bottom plane
     */
    bool check_vector_outside_FOV_plane_bottom(VectorObject* environment_vector);
    
    /**
     * @brief This will determine if the input vector object
     * is outside the photo plane of the camera frustrum. 
     * This is necessary for functions like vector clipping
     * and for drawing efficiency.
     * 
     * @param environment_vector testing vector object
     * @return true means the vector lies outside the photo plane
     * @return false means the vector lies inside the photo plane
     */
    bool check_vector_outside_photo_plane(VectorObject* environment_vector);

    /**
     * @brief This method "takes a picture" of what the camera
     * can see in the stage.
     * 
     * @return sf::Image image the camera captured
     */
    sf::Image take_picture();


};


#endif
