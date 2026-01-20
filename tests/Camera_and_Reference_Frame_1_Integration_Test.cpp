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
    For this test We will check to verify that reference frames within reference frames will work
    reference frame within a reference frame
    reference frame within a nested 3 times
    reference frame within a reference frame and vectors in each


*/


/*
    Create a reference frame visual
*/
void test_1() {

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


    std::string answer;
    std::cout << "Do you see a bunch of vectors as a corner?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));


    view1.join();
    
}


/*
    Create a reference frame visual moving around
*/
void test_2() {

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


    std::string answer;
    std::cout << "Do you see the corner rotating around?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));

    view1.join();
    
}


/*
    Create a reference frame visual moving around with another reference frame visual defined inside it
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


    std::string answer;
    std::cout << "Do you see another frame moving within another?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true) : (false));


    view1.join();
    
}



/*
    Create 3 nested reference frames
*/
void test_4() {

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


    std::string answer;
    std::cout << "Do you see 3 reference frames rotating around inside each other?: ";
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
    
    TestUtils::end_testing();

    return 0;
}