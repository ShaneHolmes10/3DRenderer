#include <iostream>
#include "Testing_Utils.h"
#include "Camera.h"
#include "Vector_Object.h"
#include "Viewport.h"
#include "Stage.h"
#include <cmath>
#include <chrono>



/*
    For testing, we want to determine how the camera object performs as more pixels are drawn 
    We will do this is the orbiting sphere where for each test we will progressively increase the number of points by 2 

*/

/*
    Generate a revolving sphere with 401 elements and sample over 200 frames
*/
void test_1() {

    Stage s1;

    ReferenceFrame sun_object;
    std::vector<VectorObject> sun_points = {};


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

    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {

        TestUtils::start_stop_watch();
        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

        TestUtils::end_stop_watch();
    }

    view1.join();

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

    
}


/*
    Generate a revolving sphere with 801 elements and sample over 200 frames
*/
void test_2() {

    Stage s1;

    ReferenceFrame sun_object;
    std::vector<VectorObject> sun_points = {};


    float sun_radius = 800;
    float sun_frequency = 95.6;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.00125) {

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

    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {

        TestUtils::start_stop_watch();
        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

        TestUtils::end_stop_watch();
    }

    view1.join();

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

    
}


/*
    Generate a revolving sphere with 1601 elements and sample over 200 frames
*/
void test_3() {

    Stage s1;

    ReferenceFrame sun_object;
    std::vector<VectorObject> sun_points = {};


    float sun_radius = 800;
    float sun_frequency = 95.6;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.000625) {

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

    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {

        TestUtils::start_stop_watch();
        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

        TestUtils::end_stop_watch();
    }

    view1.join();

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

    
}


/*
    Generate a revolving sphere with 3201 elements and sample over 200 frames
*/
void test_4() {

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

    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {

        TestUtils::start_stop_watch();
        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

        TestUtils::end_stop_watch();
    }

    view1.join();

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

    
}


/*
    Generate a revolving sphere with 6401 elements and sample over 200 frames
*/
void test_5() {

    Stage s1;

    ReferenceFrame sun_object;
    std::vector<VectorObject> sun_points = {};


    float sun_radius = 800;
    float sun_frequency = 95.6;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.00015625) {

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

    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {

        TestUtils::start_stop_watch();
        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

        TestUtils::end_stop_watch();
    }

    view1.join();

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

    
}


/*
    Generate a revolving sphere with 12801 elements and sample over 200 frames
*/
void test_6() {

    Stage s1;

    ReferenceFrame sun_object;
    std::vector<VectorObject> sun_points = {};


    float sun_radius = 800;
    float sun_frequency = 95.6;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.000078125) {

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

    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {

        TestUtils::start_stop_watch();
        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));


        view1.set_frame(c1.take_picture());
        view1.update();

        TestUtils::end_stop_watch();
    }

    view1.join();

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

    
}

int main() {


    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);
    TestUtils::perform_test(test_4);
    TestUtils::perform_test(test_5);
    TestUtils::perform_test(test_6);
    
    TestUtils::end_testing();

    return 0;
}