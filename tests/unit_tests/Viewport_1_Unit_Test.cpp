#include <iostream>
#include "Testing_Utils.h"
#include <vector>
#include <Eigen/Dense>
#include "Viewport.h"


/*
This test will confirm some basic functionality of the Viewport object class/

We want to be able to create a window with the default dimensions
We want to be able to create a window with parameter dimensions
We want to be able to check if the object is still alive
We want to be able to kill the object
We want to be able to set the frame of the object
We want to be able to update the current frame from the buffer to the current frame


*/


/*
    
*/
void test_1() {

    Viewport v1();



}


int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}