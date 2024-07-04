#include <iostream>
#include "Testing_Utils.h"
#include "Reference_Frame.h"
#include "Vector_Object.h"
#include <Eigen/Dense>


/*
This test will confirm some basic functionality of the ReferenceFrame class. Below is a list
of desired functions we wish to test.


Set the values for the frame using the constructor
Verify that the getter for angles works
Verify that the getter for place vector works
Verify that the getter for the transformation_matrix works
Verify that the setters work
Verify that the rotation matricies work
Verify that the transformation matrix calc works
Verify that expression works
Verify that adding children work

*/



/*
    Tests to make sure constructor is setting the angles properly for default constructor
*/
void test_1() {

    Eigen::Vector3d compare_1(0,0,0);

    ReferenceFrame reference_frame_A;

    TestUtils::pass_or_fail_printout(TestUtils::check_vector_3_similarity(compare_1, reference_frame_A.get_angles()));
}


int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}


