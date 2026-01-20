#include <iostream>
#include "Testing_Utils.h"
#include "Camera.h"
#include "Vector_Object.h"
#include "Viewport.h"
#include "Stage.h"
#include <cmath>
#include <chrono>



/*
    For testing, we need to adjust the camera 
    position
    orientation
    FOV
    photo dimensions
    play around with a cube animation
    ensure that vectors aren’t projected out of bounds(behind photo plane, outside FOV). 

*/


/*
    Rotate the camera around a cube find the average amount of time per frame
*/
void test_1() {

    std::cout << "Observe, then close the window and answer the questions\n";

    Stage s1;

    VectorObject v1(800, 800, 800);
    VectorObject v2(800, -800, 800);
    VectorObject v3(-800, 800, 800);
    VectorObject v4(-800, -800, 800);

    VectorObject v5(800, 800, 2400);
    VectorObject v6(800, -800, 2400);
    VectorObject v7(-800, 800, 2400);
    VectorObject v8(-800, -800, 2400);


    s1.add(&v1);
    s1.add(&v2);
    s1.add(&v3);
    s1.add(&v4);

    s1.add(&v5);
    s1.add(&v6);
    s1.add(&v7);
    s1.add(&v8);



    Camera c1(0, 0, -200, 0, 0, 0);


    c1.set_stage(s1);
    
    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();


    view1.set_frame(c1.take_picture());
    view1.update();
    
    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {
        TestUtils::start_stop_watch();
        c1.set_ox(1800*cos( ((n / 100) * 2 * M_PI) - (M_PI / 2)));
        c1.set_oz(1800*sin( ((n / 100) * 2 * M_PI) - (M_PI / 2)) + 1600);

        c1.set_ay(-((n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();
        TestUtils::end_stop_watch();
    }

    view1.join();

    TestUtils::time_result(50);
    TestUtils::end_clear_track_time();
    


}


/*
    Rotate the camera around a cube find the average amount of to take a picture*
*/
void test_2() {

    std::cout << "Observe, then close the window and answer the questions\n";

    Stage s1;

    VectorObject v1(800, 800, 800);
    VectorObject v2(800, -800, 800);
    VectorObject v3(-800, 800, 800);
    VectorObject v4(-800, -800, 800);

    VectorObject v5(800, 800, 2400);
    VectorObject v6(800, -800, 2400);
    VectorObject v7(-800, 800, 2400);
    VectorObject v8(-800, -800, 2400);


    s1.add(&v1);
    s1.add(&v2);
    s1.add(&v3);
    s1.add(&v4);

    s1.add(&v5);
    s1.add(&v6);
    s1.add(&v7);
    s1.add(&v8);



    Camera c1(0, 0, -200, 0, 0, 0);


    c1.set_stage(s1);
    
    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();


    view1.set_frame(c1.take_picture());
    view1.update();
    
    TestUtils::start_track_time();
    
    for(float n = 0; n < 200; n++) {
        
        c1.set_ox(1800*cos( ((n / 100) * 2 * M_PI) - (M_PI / 2)));
        c1.set_oz(1800*sin( ((n / 100) * 2 * M_PI) - (M_PI / 2)) + 1600);
        
        
        c1.set_ay(-((n / 100) * 2 * M_PI));
        
        
        TestUtils::start_stop_watch();
        view1.set_frame(c1.take_picture());
        TestUtils::end_stop_watch();

        view1.update();


    }

    view1.join();

    TestUtils::time_result(50);
    TestUtils::end_clear_track_time();
    
}




int main() {


    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    
    TestUtils::end_testing();

    return 0;
}