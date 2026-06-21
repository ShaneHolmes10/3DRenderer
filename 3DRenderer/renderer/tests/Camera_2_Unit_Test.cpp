#include <chrono>
#include <cmath>
#include <iostream>

#include "Camera.h"
#include "Stage.h"
#include "Testing_Utils.h"
#include "Vector_Object.h"
#include "Viewport.h"

/*
    For testing, this will test to see if the camera can successfully
   check a vector relative to a plane boundary

    outside right FOV
    inside right FOV

    outside left FOV
    inside left FOV

    outside top FOV
    inside top FOV

    outside bottom FOV
    inside bottom FOV


    outside top right corner
    inside top right corner

    outside top left corner
    inside top left corner

    outside bottom left corner
    inside bottom left corner

    outside bottom right corner
    inside bottom right corner

    outside photo planes
    inside photo plane


*/

/*
    outside right FOV
*/
void test_1() {
    Stage s1;

    VectorObject v1(-715.38948, 15.30819, 138.871);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_right(&v1));
}

/*
    inside right FOV
*/
void test_2() {
    Stage s1;

    VectorObject v1(-507.62739, -15.28733, 138.87191);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_right(&v1));
}

/*
    outside left FOV
*/
void test_3() {
    Stage s1;

    VectorObject v1(676.68866, -18.43922, 138.87191);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_left(&v1));
}

/*
    inside left FOV
*/
void test_4() {
    Stage s1;

    VectorObject v1(459.44751, 2.99284, 138.87191);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_left(&v1));
}

/*
    outside top FOV
*/
void test_5() {
    Stage s1;

    VectorObject v1(0, 600, 138.87191);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_top(&v1));
}

/*
    inside top FOV
*/
void test_6() {
    Stage s1;

    VectorObject v1(5.05973, 351.91045, 138.87191);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_top(&v1));
}

/*

    outside bottom FOV
*/
void test_7() {
    Stage s1;

    VectorObject v1(18.24217, -567.02492, 140.1350);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_bottom(&v1));
}

/*
    inside bottom FOV
*/
void test_8() {
    Stage s1;

    VectorObject v1(3.0678, -336.89108, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_bottom(&v1));
}

/*
    outside top right corner
*/
void test_9() {
    Stage s1;

    VectorObject v1(-725.8941, 525.63599, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_right(&v1) &&
        c1.check_vector_outside_FOV_plane_top(&v1));
}

/*
    inside top right corner
*/
void test_10() {
    Stage s1;

    VectorObject v1(-396.8641, 255.93012, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_right(&v1) &&
        !c1.check_vector_outside_FOV_plane_top(&v1));
}

/*
    outside top left corner
*/
void test_11() {
    Stage s1;

    VectorObject v1(800, 600, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_left(&v1) &&
        c1.check_vector_outside_FOV_plane_top(&v1));
}

/*
    inside top left corner
*/
void test_12() {
    Stage s1;

    VectorObject v1(442.00232, 318.67247, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_left(&v1) &&
        !c1.check_vector_outside_FOV_plane_top(&v1));
}

/*
    outside bottom right corner
*/
void test_13() {
    Stage s1;

    VectorObject v1(-651.14752, -503.26905, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_right(&v1) &&
        c1.check_vector_outside_FOV_plane_bottom(&v1));
}

/*
    inside bottom right corner
*/
void test_14() {
    Stage s1;

    VectorObject v1(-432.04446, -328.99134, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_right(&v1) &&
        !c1.check_vector_outside_FOV_plane_bottom(&v1));
}

/*
    outside bottom left corner
*/
void test_15() {
    Stage s1;

    VectorObject v1(707.19449, -525.66538, 140.13504);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        c1.check_vector_outside_FOV_plane_left(&v1) &&
        c1.check_vector_outside_FOV_plane_bottom(&v1));
}

/*
    inside bottom left corner
*/
void test_16() {
    Stage s1;

    VectorObject v1(400.12758, -303.31412, 140.135);
    s1.add(&v1);

    Camera c1(0, 0, 0);
    c1.set_stage(s1);

    TestUtils::pass_or_fail_printout(
        !c1.check_vector_outside_FOV_plane_left(&v1) &&
        !c1.check_vector_outside_FOV_plane_bottom(&v1));
}

/*
    Generate a sphere that orbits around the camera to verify that there
   are no point projection errors
*/
void test_17() {
    std::cout
        << "Observe, then close the window and answer the questions\n";

    Stage s1;

    ReferenceFrame planet_object;
    std::vector<VectorObject> planet_points = {};

    float planet_radius = 400;
    float planet_frequency = 18.95;

    // This should generate a bunch of points in a sphere in a spiral
    // pattern
    for (float index = 0; index <= 1; index += 0.0025) {
        float variable_radius = sqrt(
            std::pow((planet_radius), 2) -
            std::pow(((2 * index * planet_radius) - planet_radius), 2));
        float x = ((variable_radius) *
                   (cosf(planet_frequency * (index * 2 * M_PI))));
        float y = ((variable_radius) *
                   (sinf(planet_frequency * (index * 2 * M_PI))));
        float z = (2 * index * planet_radius - planet_radius);

        planet_points.push_back(VectorObject(x, y, z));
    }

    // Assign each vector to the reference frame and to the stage
    for (int ind = 0; ind < planet_points.size(); ind++) {
        planet_object.add(planet_points[ind]);
        s1.add(&planet_points[ind]);
    }

    // Create the camera and give it a stage to look at
    Camera c1(0, 0, 0, 0, 0, 0);
    c1.set_FOV_length(400);
    c1.set_stage(s1);

    // Create the viewport to display the picture at
    Viewport::init();
    Viewport view1(800, 600, 0, 0);
    view1.start();

    // Take a picture and update the viewport with it
    view1.set_frame(c1.take_picture());
    view1.update();

    for (float n = 0; n < 400; n++) {
        // translate the entire sphere

        planet_object.set_ox(2000 * cos((n / 100) * 2 * M_PI));
        planet_object.set_oz(2000 * sin((n / 100) * 2 * M_PI));
        planet_object.set_ay(-(0.87 * (n / 100) * 2 * M_PI));

        view1.set_frame(c1.take_picture());
        view1.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::string answer;
    std::cout << "Do you see rotating and orbiting planets?: ";
    std::cin >> answer;
    TestUtils::pass_or_fail_printout((answer == "y") ? (true)
                                                     : (false));

    view1.join();
}

int main() {
    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);
    TestUtils::perform_test(test_4);
    TestUtils::perform_test(test_5);
    TestUtils::perform_test(test_6);
    TestUtils::perform_test(test_7);
    TestUtils::perform_test(test_8);

    TestUtils::perform_test(test_9);
    TestUtils::perform_test(test_10);
    TestUtils::perform_test(test_11);
    TestUtils::perform_test(test_12);
    TestUtils::perform_test(test_13);
    TestUtils::perform_test(test_14);
    TestUtils::perform_test(test_15);
    TestUtils::perform_test(test_16);

    TestUtils::perform_test(test_17);

    TestUtils::end_testing();

    return 0;
}