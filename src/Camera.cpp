
#include "Camera.h"
#include "Vector_Object.h"
#include <iostream>
#include <cmath>

Camera::Camera(float ox, float oy, float oz, float ax, float ay, float az) 
    : ReferenceFrame(ox, oy, oz, ax, ay, az),
      main_stage(nullptr),
      FOV_length(100), 
      width(800),
      height(600),
      right_FOV_plane_normal(0,0,0),
      left_FOV_plane_normal(0,0,0),
      top_FOV_plane_normal(0,0,0),
      bottom_FOV_plane_normal(0,0,0) {

    generate_FOV_normals();

};

void Camera::set_stage(Stage& stage) {
    main_stage = &stage;

};

void Camera::set_FOV_length(float num) {
    FOV_length = num;

    generate_FOV_normals();
}


void Camera::generate_FOV_normals() {

    // Calculate the boundry frames 
    right_FOV_plane_normal.set_ox(-std::cos(std::atan((width / 2) / (FOV_length))));
    right_FOV_plane_normal.set_oy(0);
    right_FOV_plane_normal.set_oz(-std::sin(std::atan((width / 2) / (FOV_length))));

    left_FOV_plane_normal.set_ox(std::cos(std::atan((width / 2) / (FOV_length))));
    left_FOV_plane_normal.set_oy(0);
    left_FOV_plane_normal.set_oz(-std::sin(std::atan((width / 2) / (FOV_length))));

    top_FOV_plane_normal.set_ox(0);
    top_FOV_plane_normal.set_oy(std::cos(std::atan((height / 2) / (FOV_length))));
    top_FOV_plane_normal.set_oz(-std::sin(std::atan((height / 2) / (FOV_length))));
    
    bottom_FOV_plane_normal.set_ox(0);
    bottom_FOV_plane_normal.set_oy(-std::cos(std::atan((height / 2) / (FOV_length))));
    bottom_FOV_plane_normal.set_oz(-std::sin(std::atan((height / 2) / (FOV_length))));


}


void Camera::set_picture_width_height(int w, int h) {
    width = w;
    height = h;

    generate_FOV_normals();
}


/*

    *** Notes ***
    This is a limited projcetion process where it purely projects vectors. Eventually we will incorporate triangles and that will
    require the process of vector clipping and rasterization. Getting the vector projection working first will be important first step 
    in verifying that the process works.


    *** Description ***

    This method will take a picture of the environment by using a computational pipeline and by using a technique of rasterization

    The first step would be to use the stage that's registered with the camera object. 
    This stage contains all the vectors (and eventually relevant triangles) that the camera needs to take a picture.

    The camera will need to create a new blank image object.

    First we get the list of all the vectors in the stage. 
    After we've gone through that process we will then need to find the values of all the vectors expressed in the camera frame.
    Then we need to check if it's behind the photo plane, if it is then don't process it
    Then we need to check if it's outside the FOV planes, if it is then don't process it

    Then need to project the vectors onto the photoplane, we do this by taking all the vectors and multiplying them by (FOVLength / Zn).
    This will produce all the points in 2D for display. 
    Draw that vector on the image object.
    Repeat for next vector.

    At the end we will have our picture

*/
sf::Image Camera::take_picture() {

    
    std::vector<VectorObject*> vec_list = main_stage->get_vector_list();

    //std::cout << right_FOV_plane_normal.get_placement_vector()[0] << ", "<< right_FOV_plane_normal.get_placement_vector()[1] << ", " << right_FOV_plane_normal.get_placement_vector()[2] << "\n";

    sf::RenderTexture renderTexture;
    renderTexture.create(width, height);

    // Clear the RenderTexture with a white color
    renderTexture.clear(sf::Color::White);


    for(int n = 0; n < vec_list.size(); n++) {
        

        
        // Express this vector in terms of the cameras reference frame
        VectorObject* vec_expressed = vec_list[n]->get_expressed_in(*this);

        
        // See if it's out of the right FOV bounds
        if(
            (right_FOV_plane_normal.get_placement_vector()[0]*(vec_expressed->get_transformed_vector()[0]) +
            right_FOV_plane_normal.get_placement_vector()[1]*(vec_expressed->get_transformed_vector()[1]) +
            right_FOV_plane_normal.get_placement_vector()[2]*(vec_expressed->get_transformed_vector()[2])) > 0
        ) {
            continue;

        }

        
        // See if it's out of the left FOV bounds
        if(
            (left_FOV_plane_normal.get_placement_vector()[0]*(vec_expressed->get_transformed_vector()[0]) +
            left_FOV_plane_normal.get_placement_vector()[1]*(vec_expressed->get_transformed_vector()[1]) +
            left_FOV_plane_normal.get_placement_vector()[2]*(vec_expressed->get_transformed_vector()[2])) > 0
        ) {
            continue;

        }

        // See if it's out of the top FOV bounds
        if(
            (top_FOV_plane_normal.get_placement_vector()[0]*(vec_expressed->get_transformed_vector()[0]) +
            top_FOV_plane_normal.get_placement_vector()[1]*(vec_expressed->get_transformed_vector()[1]) +
            top_FOV_plane_normal.get_placement_vector()[2]*(vec_expressed->get_transformed_vector()[2])) > 0
        ) {
            continue;

        }

        // See if it's out of the bottom FOV bounds
        if(
            (bottom_FOV_plane_normal.get_placement_vector()[0]*(vec_expressed->get_transformed_vector()[0]) +
            bottom_FOV_plane_normal.get_placement_vector()[1]*(vec_expressed->get_transformed_vector()[1]) +
            bottom_FOV_plane_normal.get_placement_vector()[2]*(vec_expressed->get_transformed_vector()[2])) > 0
        ) {
            continue;

        }
        


        
        // See if it's behind the photo plane
        if(vec_expressed->get_placement_vector()[2] < FOV_length) {
            continue;
        }

        float z = vec_expressed->get_placement_vector()[2];


        // Draw a circle shape on the RenderTexture
        sf::CircleShape circle(4); // Radius of 100
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(
            (vec_expressed->get_placement_vector()[0] * (FOV_length/z)) + (width / 2), 
            (vec_expressed->get_placement_vector()[1] * (FOV_length/z)) + (height / 2)
        ); // Position the circle at (300, 200)

        renderTexture.draw(circle);
        renderTexture.display();

    
        //std::cout << vec_expressed->get_placement_vector()[0] << ", " << vec_expressed->get_placement_vector()[1] << ", " << vec_expressed->get_placement_vector()[2] << "\n";
        
    }

    // Get the texture from the RenderTexture
    sf::Texture texture = renderTexture.getTexture();

    // Convert the texture to an image
    sf::Image image = texture.copyToImage();

    return image;

};



