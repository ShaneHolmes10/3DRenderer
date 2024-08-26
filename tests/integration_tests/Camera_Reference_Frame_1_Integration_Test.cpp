#include <iostream>
#include "Testing_Utils.h"
#include "Camera.h"
#include "Vector_Object.h"
#include "Viewport.h"
#include "Stage.h"
#include "Reference_Frame.h"
#include <vector>
#include <cmath>
#include <chrono>



/*
    For testing, We will create an array of vectors in the shape of a sphere
    We will define these vectors to be defined in a reference frame
    This time we will move the reference frame around and rotate it

*/


/*
    Create a sphere of points tied to a reference frame and print it to the screen 
*/
void test_1() {

    std::cout << "Observe, then close the window and answer the questions\n";

    Stage s1;

    ReferenceFrame rf1;

    std::vector<VectorObject> sphere_points = {};

    float radius = 800;
    float frequency = 10;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.01) {

        float variable_radius = sqrt(std::pow( (radius) ,2) - std::pow( ((2*index*radius) - radius) ,2));
        float x = ((variable_radius)*(cosf(frequency*(index*2*M_PI))));
        float z = ((variable_radius)*(sinf(frequency*(index*2*M_PI))));
        float y = (2*index*radius - radius);


        sphere_points.push_back(VectorObject(x, y, z));
    }

    //std::cout << sphere_points[70].get_placement_vector() << "\n";

    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < sphere_points.size(); ind++) {
        rf1.add(sphere_points[ind]);   
        s1.add(&sphere_points[ind]);
    }


    // Create the camera and give it a stage to look at
    Camera c1(0, 0, -1000, 0, 0, 0);
    c1.set_stage(s1);
    

    // Create the viewport to display the picture at
    Viewport::init();
    Viewport view1(800, 600, 0, 0);
    view1.start();


    // Take a picture and update the viewport with it
    view1.set_frame(c1.take_picture());
    view1.update();
    //for(float n = 0; n < 200; n++) {

    //    view1.set_frame(c1.take_picture());
    //    view1.update();
    //}


    std::string answer;
    std::cout << "Was a sphere of points made?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    view1.join();
    
}


/*
    With the sphere of points translate the entire sphere  
*/
void test_2() {

    std::cout << "Observe, then close the window and answer the questions\n";

    Stage s1;

    ReferenceFrame rf1;

    std::vector<VectorObject> sphere_points = {};

    float radius = 800;
    float frequency = 10;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.01) {

        float variable_radius = sqrt(std::pow( (radius) ,2) - std::pow( ((2*index*radius) - radius) ,2));
        float x = ((variable_radius)*(cosf(frequency*(index*2*M_PI))));
        float z = ((variable_radius)*(sinf(frequency*(index*2*M_PI))));
        float y = (2*index*radius - radius);


        sphere_points.push_back(VectorObject(x, y, z));
    }


    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < sphere_points.size(); ind++) {
        rf1.add(sphere_points[ind]);   
        s1.add(&sphere_points[ind]);
    }



    // Create the camera and give it a stage to look at
    Camera c1(0, 0, -1000, 0, 0, 0);
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
        rf1.set_ox(n);

        view1.set_frame(c1.take_picture());
        view1.update();
    }

    std::string answer;
    std::cout << "Was a sphere of points made, and has is been translated on the screen?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    view1.join();
    
}



/*
    With the sphere of points rotate it around it's y axis
*/
void test_3() {

    std::cout << "Observe, then close the window and answer the questions\n";

    Stage s1;

    ReferenceFrame rf1;

    std::vector<VectorObject> sphere_points = {};

    float radius = 800;
    float frequency = 10;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.01) {

        float variable_radius = sqrt(std::pow( (radius) ,2) - std::pow( ((2*index*radius) - radius) ,2));
        float x = ((variable_radius)*(cosf(frequency*(index*2*M_PI))));
        float z = ((variable_radius)*(sinf(frequency*(index*2*M_PI))));
        float y = (2*index*radius - radius);


        sphere_points.push_back(VectorObject(x, y, z));
    }


    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < sphere_points.size(); ind++) {
        rf1.add(sphere_points[ind]);   
        s1.add(&sphere_points[ind]);
    }



    // Create the camera and give it a stage to look at
    Camera c1(0, 0, -1000, 0, 0, 0);
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
        
        rf1.set_ay(-((n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::string answer;
    std::cout << "Was a sphere of points made, and has is been rotated on the screen?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    view1.join();
    
}


/*
    generate the sphere with more points for the rotating sphere
*/
void test_4() {

    std::cout << "Observe, then close the window and answer the questions\n";

    Stage s1;

    ReferenceFrame rf1;

    std::vector<VectorObject> sphere_points = {};

    float radius = 800;
    float frequency = 18.95;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.005) {

        float variable_radius = sqrt(std::pow( (radius) ,2) - std::pow( ((2*index*radius) - radius) ,2));
        float x = ((variable_radius)*(cosf(frequency*(index*2*M_PI))));
        float z = ((variable_radius)*(sinf(frequency*(index*2*M_PI))));
        float y = (2*index*radius - radius);


        sphere_points.push_back(VectorObject(x, y, z));
    }


    // Assign each vector to the reference frame and to the stage
    for(int ind = 0; ind < sphere_points.size(); ind++) {
        rf1.add(sphere_points[ind]);   
        s1.add(&sphere_points[ind]);
    }



    // Create the camera and give it a stage to look at
    Camera c1(0, 0, -1000, 0, 0, 0);
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
        
        rf1.set_ay(-((n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::string answer;
    std::cout << "Were more points generated for the rotating sphere?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    view1.join();
    
}


/*
    Generate a sphere rotating on it's axis and then a smaller sphere orbiting around that axis
*/
void test_5() {

    std::cout << "Observe, then close the window and answer the questions\n";

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
    
    for(float n = 0; n < 2000; n++) {

        // translate the entire sphere
        
        sun_object.set_ay(-(0.15*(n / 100) * 2 * M_PI));

        planet_object.set_ox(2000*cos((n/100)*2*M_PI));
        planet_object.set_oz(2000*sin((n/100)*2*M_PI));
        planet_object.set_ay(-(0.87*(n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::string answer;
    std::cout << "Do you see rotating and orbiting planets?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    view1.join();
    
}



int main() {


    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);
    TestUtils::perform_test(test_4);
    TestUtils::perform_test(test_5);
    
    TestUtils::end_testing();

    return 0;
}