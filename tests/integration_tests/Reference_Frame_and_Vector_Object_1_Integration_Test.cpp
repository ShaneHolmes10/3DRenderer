#include <iostream>
#include "Testing_Utils.h"
#include "Reference_Frame.h"
#include "Vector_Object.h"
#include <Eigen/Dense>


/*
This test will confirm some basic functionality of the VectorObject class. Below is a list
of desired functions we wish to test.


test definition of vector object in reference frame
test Expression of vector object in reference frame 

*/



/*
    This tests the expression system for a null reference frame
*/
void test_1() {

    Eigen::Vector3d compare_1(1,2,3);

    ReferenceFrame reference_frame_A;
    VectorObject vector_1(1, 2, 3);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_expressed_in(reference_frame_A)->get_transformed_vector()
        )
    );

}

/*
    This is expression for a non-null reference frame
*/
void test_2() {

    Eigen::Vector3d compare_1(3.97,5.92,-0.82);

    ReferenceFrame reference_frame_A(4, 5, 6, 1, 2, 3);
    VectorObject vector_1(1, 1.5, 0.5);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_expressed_in(reference_frame_A)->get_transformed_vector()
        )
    );

}

/*
    This is the transformed value for a none null reference frame
*/
void test_3() {

    Eigen::Vector3d compare_1(2.98,4.75,4.45);

    ReferenceFrame reference_frame_A(4, 5, 6, 1, 2, 3);
    VectorObject vector_1(1, 1.5, 0.5);

    reference_frame_A.add(vector_1);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_transformed_vector()
        )
    );

}


int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);
    TestUtils::perform_test(test_2);
    TestUtils::perform_test(test_3);

    TestUtils::end_testing();

    return 0;
}


