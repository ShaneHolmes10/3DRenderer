
#ifndef Camera_H
#define Camera_H

#include "Reference_Frame.h"
#include "Stage.h"
#include <SFML/Graphics.hpp>
#include <Eigen/Dense>
#include <vector>


class VectorObject;
class Stage;

class Camera : public ReferenceFrame {

private:
    Stage* main_stage;

    float FOV_length;
    int width;
    int height;    

    VectorObject right_FOV_plane_normal;
    VectorObject left_FOV_plane_normal;
    VectorObject top_FOV_plane_normal;
    VectorObject bottom_FOV_plane_normal;


private:
    void generate_FOV_normals();


public:
    Camera(float ox = 0, float oy = 0, float oz = 0, float ax = 0, float ay = 0, float az = 0);

    void set_stage(Stage& stage);

    void set_FOV_length(float num);
    void set_picture_width_height(int w, int h);

    bool check_vector_outside_FOV_plane_right(VectorObject* environment_vector);
    bool check_vector_outside_FOV_plane_left(VectorObject* environment_vector);
    bool check_vector_outside_FOV_plane_top(VectorObject* environment_vector);
    bool check_vector_outside_FOV_plane_bottom(VectorObject* environment_vector);
    bool check_vector_outside_photo_plane(VectorObject* environment_vector);

    sf::Image take_picture();


};


#endif
