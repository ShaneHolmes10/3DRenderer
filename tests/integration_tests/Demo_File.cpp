#include <iostream>
#include "Testing_Utils.h"
#include "Camera.h"
#include "Vector_Object.h"
#include "Testing_Methods.h"
#include "Viewport.h"
#include "Stage.h"
#include <cmath>
#include <chrono>



/*
    This is a demo file for the sake of demonstrating cool things 
    sphere
    orbiting planets
    nested reference frames
    triangle 

*/



/*
    Generate a revolving sphere with 3201 elements and sample over 200 frames
*/
void test_1() {

    Stage s1;

    ReferenceFrame sun_object;
    std::vector<VectorObject> sun_points = {};


    float sun_radius = 800;
    float sun_frequency = 95.6;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.0003125) {

        float variable_radius = sqrt(std::pow( (sun_radius) ,2) - std::pow( ((2*index*sun_radius) - sun_radius) ,2));
        float x = ((variable_radius)*(cosf(sun_frequency*(index*2*M_PI))));
        float y = ((variable_radius)*(sinf(sun_frequency*(index*2*M_PI))));
        float z = (2*index*sun_radius - sun_radius);


        sun_points.push_back(VectorObject(x, y, z));
    }


    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < sun_points.size(); ind++) {
        sun_object.add(sun_points[ind]);   
        s1.add(&sun_points[ind]);
    }


    // Create the camera and give it a stage to look at
    Camera c1(0, 0, -3000, 0, 0, 0);
    c1.set_FOV_length(400);
    c1.set_stage(s1);
    

    // Create the viewport to display the picture at
    Viewport::init();
    Viewport view1(800, 600, 0, 0);
    view1.start();


    // Take a picture and update the viewport with it
    view1.set_frame(c1.take_picture());
    view1.update();
    
    for(float n = 0; n < 666; n++) {

        // translate the entire sphere        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

    }

    view1.join();
    
}


/*
    Generate a sphere rotating on it's axis and then a smaller sphere orbiting around that axis
*/
void test_2() {

    Stage s1;

    ReferenceFrame sun_object;
    std::vector<VectorObject> sun_points = {};


    ReferenceFrame planet_object;
    std::vector<VectorObject> planet_points = {};



    float sun_radius = 800;
    float sun_frequency = 95.6;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.0025) {

        float variable_radius = sqrt(std::pow( (sun_radius) ,2) - std::pow( ((2*index*sun_radius) - sun_radius) ,2));
        float x = ((variable_radius)*(cosf(sun_frequency*(index*2*M_PI))));
        float y = ((variable_radius)*(sinf(sun_frequency*(index*2*M_PI))));
        float z = (2*index*sun_radius - sun_radius);


        sun_points.push_back(VectorObject(x, y, z));
    }


    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < sun_points.size(); ind++) {
        sun_object.add(sun_points[ind]);   
        s1.add(&sun_points[ind]);
    }



    float planet_radius = 400;
    float planet_frequency = 18.95;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.005) {

        float variable_radius = sqrt(std::pow( (planet_radius) ,2) - std::pow( ((2*index*planet_radius) - planet_radius) ,2));
        float x = ((variable_radius)*(cosf(planet_frequency*(index*2*M_PI))));
        float y = ((variable_radius)*(sinf(planet_frequency*(index*2*M_PI))));
        float z = (2*index*planet_radius - planet_radius);


        planet_points.push_back(VectorObject(x, y, z));
    }


    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < planet_points.size(); ind++) {
        planet_object.add(planet_points[ind]);   
        s1.add(&planet_points[ind]);
    }



    // Create the camera and give it a stage to look at
    Camera c1(0, 0, -3000, 0, 0, 0);
    c1.set_FOV_length(400);
    c1.set_stage(s1);
    

    // Create the viewport to display the picture at
    Viewport::init();
    Viewport view1(800, 600, 0, 0);
    view1.start();


    // Take a picture and update the viewport with it
    view1.set_frame(c1.take_picture());
    view1.update();
    
    for(float n = 0; n < 200; n++) {

        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));

        planet_object.set_ox(2000*cos((n/100)*2*M_PI));
        planet_object.set_oz(2000*sin((n/100)*2*M_PI));
        planet_object.set_ay(-(0.87*(n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    view1.join();
    
}


/*
    Create 3 nested reference frames
*/
void test_3() {

    Stage s1;


    // Reference Frame Definitions
    ReferenceFrame rf1;


    // Vector Definitions of a reference frame
    float length = 1000;
    std::vector<VectorObject> line_points = {};
    for(float index = 0; index <= 1; index+=0.1) {

        line_points.push_back(VectorObject(0, 0, length*(index)));
    }

    for(float index = 0; index <= 1; index+=0.1) {

        line_points.push_back(VectorObject(0, length*(index), 0));
    }

    for(float index = 0; index <= 1; index+=0.1) {

        line_points.push_back(VectorObject(length*(index), 0, 0));
    }

    
    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < line_points.size(); ind++) {
        rf1.add(line_points[ind]);   
        s1.add(&line_points[ind]);
    }



    // Reference Frame definition
    ReferenceFrame rf2(1500, 0, 0, 0, 0, 0);

    // Vector Definitions of a reference frame
    float length_2 = 1000;
    std::vector<VectorObject> line_points_2 = {};
    for(float index = 0; index <= 1; index+=0.1) {

        line_points_2.push_back(VectorObject(0, 0, length_2*(index)));
    }

    for(float index = 0; index <= 1; index+=0.1) {

        line_points_2.push_back(VectorObject(0, length_2*(index), 0));
    }

    for(float index = 0; index <= 1; index+=0.1) {

        line_points_2.push_back(VectorObject(length_2*(index), 0, 0));
    }

    
    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < line_points_2.size(); ind++) {
        rf2.add(line_points_2[ind]);   
        s1.add(&line_points_2[ind]);
    }

    // Define rf2 inside rf1
    rf1.add(rf2);



    // Reference Frame definition
    ReferenceFrame rf3(0, 1500, 0, 0, 0, 0);

    // Vector Definitions of a reference frame
    float length_3 = 1000;
    std::vector<VectorObject> line_points_3 = {};
    for(float index = 0; index <= 1; index+=0.1) {

        line_points_3.push_back(VectorObject(0, 0, length_3*(index)));
    }

    for(float index = 0; index <= 1; index+=0.1) {

        line_points_3.push_back(VectorObject(0, length_3*(index), 0));
    }

    for(float index = 0; index <= 1; index+=0.1) {

        line_points_3.push_back(VectorObject(length_3*(index), 0, 0));
    }

    
    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < line_points_3.size(); ind++) {
        rf3.add(line_points_3[ind]);   
        s1.add(&line_points_3[ind]);
    }

    // Define rf2 inside rf1
    rf2.add(rf3);




    // Create the camera and give it a stage to look at
    Camera c1(0, 0, -3000, 0, 0, 0);
    c1.set_FOV_length(400);
    c1.set_stage(s1);
    

    // Create the viewport to display the picture at
    Viewport::init();
    Viewport view1(800, 600, 0, 0);
    view1.start();


    // Take a picture and update the viewport with it
    view1.set_frame(c1.take_picture());
    view1.update();

    for(float n = 0; n < 400; n++) {

        // translate the entire sphere
        rf1.set_ax(-(0.15*(n / 100) * 2 * M_PI));
        rf1.set_ay(-(0.15*(n / 100) * 2 * M_PI));
        rf1.set_az(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }


    view1.join();
    
}


/*
    Draw a triangle and display it
*/
void test_4() {

    int width = 800;
    int height = 600;

    // Create an image
    sf::Image image;
    image.create(width, height, sf::Color::White); // Create an image object to color

    Viewport::init();

    Viewport view1(width, height, 0, 0);
    view1.start();


    image.create(width, height, sf::Color::White);
    TestMeth::create_triangle(image, {163,277}, {793,280}, {458,462}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255});
    view1.set_frame(image);
    view1.update();


    view1.join();


}



int main() {


    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);
    TestUtils::perform_test(test_4);

    TestUtils::end_testing();

    return 0;
}