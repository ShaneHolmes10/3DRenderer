#include <iostream>
#include "Testing_Utils.h"
#include "Camera.h"
#include "Vector_Object.h"
#include "Viewport.h"
#include "Stage.h"
#include "Reference_Frame.h"
#include <vector>
#include <cmath>



/*
    For testing, We will create an array of vectors in the shape of a sphere
    We will define these vectors to be defined in a reference frame
    This time we will move the reference frame around and rotate it

*/


/*
    Rotate the camera around a cube find the average amount of time per frame
*/
void test_1() {

    std::cout << "Observe, then close the window and answer the questions\n";

    Stage s1;

    ReferenceFrame rf1;

    std::vector<VectorObject> sphere_points = {};

    float radius = 4;
    float frequency = 10;

    // This should generate a bunch of points in a sphere in a spiral pattern
    for(float index = 0; index <= 1; index+=0.01) {

        float variable_radius = sqrt(std::pow( (radius) ,2) - std::pow( ((2*index*radius) - radius) ,2));
        float x = ((variable_radius)*(cosf(frequency*(index*2*M_PI))));
        float y = ((variable_radius)*(sinf(frequency*(index*2*M_PI))));
        float z = (2*index*radius - radius);


        sphere_points.push_back(VectorObject(x, y, z));
    }

    std::cout << sphere_points[70].get_placement_vector() << "\n";






    /*
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
    */


}


int main() {


    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    
    TestUtils::end_testing();

    return 0;
}