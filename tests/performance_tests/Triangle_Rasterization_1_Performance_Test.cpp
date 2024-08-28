#include <iostream>
#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include <vector>
#include <Eigen/Dense>
#include <random>
#include "Viewport.h"
#include <cstdlib>



/*
    I want to do a performance test for rendering the traingle 
    triangle at different sizes
    multiple triangles
*/


/*
    Measure the time it takes to draw a triangle
*/
void test_1() {

    int width = 800;
    int height = 600;

    // Create an image
    sf::Image image;
    image.create(width, height, sf::Color::White); // Create an image object to color

    Viewport::init();

    Viewport view1(width, height, 0, 0);
    view1.start();


    TestUtils::start_track_time();

    
    for(float ind = 0; ind < 200; ind++) {
        TestUtils::start_stop_watch();
        image.create(width, height, sf::Color::White);
        TestMeth::create_triangle(image, {163,277-ind}, {793,280}, {458,462}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255});
        view1.set_frame(image);
        view1.update();
        TestUtils::end_stop_watch();

    }
    

    view1.join();    

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

}


/*
    Measure the time it takes to draw a small triangle
*/
void test_2() {

    int width = 800;
    int height = 600;

    // Create an image
    sf::Image image;
    image.create(width, height, sf::Color::White); // Create an image object to color

    Viewport::init();

    Viewport view1(width, height, 0, 0);
    view1.start();


    TestUtils::start_track_time();

    
    for(float ind = 0; ind < 200; ind++) {
        TestUtils::start_stop_watch();
        image.create(width, height, sf::Color::White);

        TestMeth::create_triangle(image, {66,35+ind}, 
                                         {37,64+ind}, 
                                         {28,27+ind}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255});

        view1.set_frame(image);
        view1.update();
        TestUtils::end_stop_watch();
    }
    

    view1.join();    

    TestUtils::time_result(16);
    TestUtils::end_clear_track_time();

}


/*
    Measure the time it takes to draw a small triangle
*/
void test_3() {


    srand(static_cast<unsigned int>(time(0)));

    int width = 800;
    int height = 600;

    // Create an image
    sf::Image image;
    image.create(width, height, sf::Color::White); // Create an image object to color

    Viewport::init();

    Viewport view1(width, height, 0, 0);
    view1.start();

    
    TestUtils::start_stop_watch();
    for(float ind = 0; ind < 1000; ind++) {
        

        float point_x = (rand() % 600 + 100);
        float point_y = (rand() % 400 + 100);
        
        TestMeth::create_triangle(image, {point_x,point_y}, 
                                         {point_x+95,point_y+92}, 
                                         {point_x-41,point_y+95}, {255, 0, 0}, {0, 255, 0}, {0, 0, 255});
        
    }
    TestUtils::end_stop_watch();
    view1.set_frame(image);
    view1.update();
    

    TestUtils::time_result(16);
    

    view1.join();    


}


int main() {

    TestUtils::start_testing();

    //TestUtils::perform_test(test_1);
    //TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);

    TestUtils::end_testing();

    return 0;
}