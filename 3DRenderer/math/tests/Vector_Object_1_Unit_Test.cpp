#include <iostream>
#include "Testing_Utils.h"
#include "Reference_Frame.h"
#include "Vector_Object.h"
#include <Eigen/Dense>


/*
This test will confirm some basic functionality of the VectorObject class. Below is a list
of desired functions we wish to test.


Set the values for the frame using the constructor
Verify that the getter for place vector works
verify that the getter for transform vector
Verify that the setters work

*/



/*
    This tests the default constructor
*/
void test_1() {

    Eigen::Vector3d compare_1(0,0,0);

    VectorObject vector_1;

    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_placement_vector()
        )
    );

}

/*
    This tests a parameter constructor
*/
void test_2() {

    Eigen::Vector3d compare_1(1,2,3);

    VectorObject vector_1(1, 2, 3);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_placement_vector()
        )
    );

}

/*
    This tests the get transformed vector method with default constructor
*/
void test_3() {

    Eigen::Vector3d compare_1(0,0,0);

    VectorObject vector_1;

    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_transformed_vector()
        )
    );

}

/*
    This tests the get transformed vector method with parameter constructor
*/
void test_4() {

    Eigen::Vector3d compare_1(1,2,3);

    VectorObject vector_1(1, 2, 3);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_transformed_vector()
        )
    );

}

/*
    This tests the setter methods, for placement vector
*/
void test_5() {

    Eigen::Vector3d compare_1(4,5,6);

    VectorObject vector_1;
    vector_1.set_ox(4);
    vector_1.set_oy(5);
    vector_1.set_oz(6);


    TestUtils::pass_or_fail_printout(
        TestUtils::check_vector_3_similarity(
            compare_1, 
            vector_1.get_placement_vector()
        )
    );

}

/*
    This tests the setter methods, for transformed vector vector 
*/
void test_6() {

    Eigen::Vector3d compare_1(4,5,6);

    VectorObject vector_1;
    vector_1.set_ox(4);
    vector_1.set_oy(5);
    vector_1.set_oz(6);


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
    TestUtils::perform_test(test_4);
    TestUtils::perform_test(test_5);
    TestUtils::perform_test(test_6);

    TestUtils::end_testing();

    return 0;
}


