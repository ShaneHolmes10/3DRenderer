#include <iostream>
#include "Testing_Utils.h"
#include "Reference_Frame.h"
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

/*
    Tests to make sure constructor is setting the angles properly for passing values
*/
void test_2() {

    Eigen::Vector3d compare_1(4, 5, 6);

    ReferenceFrame reference_frame_A(1, 2, 3, 4, 5, 6);

    TestUtils::pass_or_fail_printout(TestUtils::check_vector_3_similarity(compare_1, reference_frame_A.get_angles()));
}

/*
    Tests to make sure constructor is setting the placement vector properly for default constructor
*/
void test_3() {

    Eigen::Vector3d compare_1(0,0,0);

    ReferenceFrame reference_frame_A;

    TestUtils::pass_or_fail_printout(TestUtils::check_vector_3_similarity(compare_1, reference_frame_A.get_placement_vector()));
}

/*
    Tests to make sure constructor is setting the placement vector properly for passing values
*/
void test_4() {

    Eigen::Vector3d compare_1(1,2,3);

    ReferenceFrame reference_frame_A(1, 2, 3, 4, 5, 6);

    TestUtils::pass_or_fail_printout(TestUtils::check_vector_3_similarity(compare_1, reference_frame_A.get_placement_vector()));

}

/*
    Test to make sure the transformation matrix of the default reference frame is correct
*/
void test_5() {

    Eigen::Matrix4d compare_1;
    compare_1 << 1, 0, 0, 0,
                 0, 1, 0, 0, 
                 0, 0, 1, 0, 
                 0, 0, 0, 1;

    ReferenceFrame reference_frame_A;

    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_4_similarity(compare_1, reference_frame_A.get_transformation_matrix()));

}

/*
    Test to make sure the transformation matrix of the reference frame is correct
*/
void test_6() { 

    Eigen::Matrix4d compare_1;
    compare_1 << 0.27, 0.51, 0.81, 1,
                 -0.08, -0.83, 0.55, 2,
                 0.96, -0.21, -0.19, 3, 
                 0,    0,     0,     1;

    ReferenceFrame reference_frame_A(1, 2, 3, 4, 5, 6);

    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_4_similarity(compare_1, reference_frame_A.get_transformation_matrix()));

}

/*
   Test setters, check to see that angles is correct
*/
void test_7() { 

    Eigen::Vector3d compare_1(7,8,9);

    ReferenceFrame reference_frame_A;

    reference_frame_A.set_ax(7);
    reference_frame_A.set_ay(8);
    reference_frame_A.set_az(9);
    reference_frame_A.set_ox(10);
    reference_frame_A.set_oy(11);
    reference_frame_A.set_oz(12);

    TestUtils::pass_or_fail_printout(TestUtils::check_vector_3_similarity(compare_1, reference_frame_A.get_angles()));

}

/*
   Test setters, check to see that placement is correct
*/
void test_8() { 

    Eigen::Vector3d compare_1(10,11,12);

    ReferenceFrame reference_frame_A;

    reference_frame_A.set_ax(7);
    reference_frame_A.set_ay(8);
    reference_frame_A.set_az(9);
    reference_frame_A.set_ox(10);
    reference_frame_A.set_oy(11);
    reference_frame_A.set_oz(12);

    TestUtils::pass_or_fail_printout(TestUtils::check_vector_3_similarity(compare_1, reference_frame_A.get_placement_vector()));

}

/*
   Test setters, check to see that transformation is correct
*/
void test_9() { 

    Eigen::Matrix4d compare_1;
    compare_1 << 0.13, -0.9, -0.41, 10,
                 -0.06, -0.42, 0.91, 11,
                 -0.99, -0.1, -0.11, 12, 
                 0,     0,    0,     1;

    ReferenceFrame reference_frame_A;

    reference_frame_A.set_ax(7);
    reference_frame_A.set_ay(8);
    reference_frame_A.set_az(9);
    reference_frame_A.set_ox(10);
    reference_frame_A.set_oy(11);
    reference_frame_A.set_oz(12);


    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_4_similarity(compare_1, reference_frame_A.get_transformation_matrix()));

}

/*
   This tests the fidelity of the X axis rotation matrix 
*/
void test_10() { 

    Eigen::Matrix3d compare_1;
    compare_1 << 1, 0, 0, 
                 0, -0.99, -0.14, 
                 0, 0.14, -0.99;

    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_3_similarity(compare_1,  MathPositionObject::calculate_rotation_matrix_x(3)));

}

/*
   This tests the fidelity of the Y axis rotation matrix 
*/
void test_11() { 

    Eigen::Matrix3d compare_1;
    compare_1 << -0.99, 0, 0.14,
                 0, 1, 0, 
                 -0.14, 0, -0.99;

    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_3_similarity(compare_1,  MathPositionObject::calculate_rotation_matrix_y(3)));

}

/*
   This tests the fidelity of the Z axis rotation matrix 
*/
void test_12() { 

    Eigen::Matrix3d compare_1;
    compare_1 << -0.99, -0.14, 0,
                 0.14, -0.99, 0, 
                 0, 0, 1;

    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_3_similarity(compare_1,  MathPositionObject::calculate_rotation_matrix_z(3)));

}

/*
    This tests the fidelity of the transformation matrix calulation
*/
void test_13() { 

    Eigen::Matrix4d compare_1;
    compare_1 << -0.1, -0.91, -0.41, 16,
                 0.09, -0.42, 0.9,   17, 
                 -0.99, 0.06, 0.12,  18,
                 0,     0,    0,     1;

    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_4_similarity(compare_1, MathPositionObject::calculate_transformation_matrix(Eigen::Vector3d(13, 14, 15), Eigen::Vector3d(16, 17, 18))));

}

/*
    This tests the fidelity of the reference frame expression
*/
void test_14() { 

    Eigen::Matrix4d compare_1;
    compare_1 << -0.91, -0.30, -0.29, 10.36,
                 0.33, -0.09, -0.94, -4.77,
                 0.26, -0.94, 0.19, 10.62,
                 0,     0,    0,     1;

    ReferenceFrame reference_frame_A;
    ReferenceFrame reference_frame_B(1, 2, 3, 4, 5, 6);

    reference_frame_A.set_ax(7);
    reference_frame_A.set_ay(8);
    reference_frame_A.set_az(9);
    reference_frame_A.set_ox(10);
    reference_frame_A.set_oy(11);
    reference_frame_A.set_oz(12);

    TestUtils::pass_or_fail_printout(TestUtils::check_matrix_4_similarity(compare_1, reference_frame_A.get_expressed_in(reference_frame_B)->get_transformation_matrix()));

}

/*
    This tests if the child adding system works, this will control how reference frames are defined
*/
void test_15() {

    Eigen::Matrix4d compare_1;
    compare_1 << 0.96, -0.22, -0.18, 10.02,
                 0.09, 0.83, -0.56, 6.02,
                 0.27, 0.52, 0.81, 9.98,
                 0,     0,    0,     1;

    ReferenceFrame reference_frame_A(7, 8, 9, 10, 11, 12);
    ReferenceFrame reference_frame_B(1, 2, 3, 4, 5, 6);

    reference_frame_A.add(reference_frame_B);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_matrix_4_similarity(
            compare_1, 
            reference_frame_B.get_transformation_matrix()
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
    TestUtils::perform_test(test_7);
    TestUtils::perform_test(test_8);
    TestUtils::perform_test(test_9);
    TestUtils::perform_test(test_10);
    TestUtils::perform_test(test_11);
    TestUtils::perform_test(test_12);
    TestUtils::perform_test(test_13);
    TestUtils::perform_test(test_14);
    TestUtils::perform_test(test_15);

    TestUtils::end_testing();

    return 0;
}


