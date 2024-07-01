#include <iostream>
#include "Reference_Frame.h"

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

*/

int main() {
    std::cout << "UNIT TEST *STARTED*" << std::endl;
    std::cout << std::endl << "TEST 1" << std::endl;
    std::cout << "EXPECTED: " << std::endl 
    << "RFA angles: " << "0, 0, 0" << std::endl
    << "RFB angles: " << "4, 5, 6" << std::endl;

    ReferenceFrame reference_frame_A;
    ReferenceFrame reference_frame_B(1, 2, 3, 4, 5, 6);

    std::cout << std::endl << "RETURNED: " << std::endl; 
    std::cout << "RFA angles: " << reference_frame_A.get_angles() << std::endl;
    std::cout << "RFB angles: " << reference_frame_B.get_angles() << std::endl;



    std::cout << std::endl << "TEST 2" << std::endl;
    std::cout << "EXPECTED: " << std::endl 
    << "RFA place: " << "0, 0, 0" << std::endl
    << "RFB place: " << "1, 2, 3" << std::endl;

    std::cout << std::endl << "RETURNED: " << std::endl; 
    std::cout << "RFA place: " << reference_frame_A.get_placement_vector() << std::endl;
    std::cout << "RFB place: " << reference_frame_B.get_placement_vector() << std::endl;



    std::cout << std::endl << "TEST 3" << std::endl;
    std::cout << "EXPECTED: " << std::endl 
    << "RFA trans: " << "1, 0, 0, 0, \n 0, 1, 0, 0, \n 0, 0, 1, 0, \n 0, 0, 0, 1" << std::endl
    << "RFB trans: " << "0.27, 0.51, 0.81, 1, \n -0.08, -0.83, 0.55, 2, \n 0.96, -0.21, -0.19, 3, \n 0, 0, 0, 1" << std::endl;

    std::cout << std::endl << "RETURNED: " << std::endl; 
    std::cout << "RFA trans: " << reference_frame_A.get_transformation_matrix() << std::endl;
    std::cout << "RFB trans: " << reference_frame_B.get_transformation_matrix() << std::endl;



    std::cout << std::endl << "TEST 4" << std::endl;
    std::cout << "EXPECTED: " << std::endl 
    << "RFA angles: " << "7, 8, 9" << std::endl
    << "RFA place: " << "10, 11, 12" << std::endl
    << "RFA trans: " << "0.13, -0.9, -0.41, 10, \n -0.06, -0.42, 0.91, 11, \n -0.99, -0.1, -0.11, 12, \n 0, 0, 0, 1" << std::endl;


    reference_frame_A.set_ax(7);
    reference_frame_A.set_ay(8);
    reference_frame_A.set_az(9);
    reference_frame_A.set_ox(10);
    reference_frame_A.set_oy(11);
    reference_frame_A.set_oz(12);

    std::cout << std::endl << "RETURNED: " << std::endl; 
    std::cout << "RFA angles: " << reference_frame_A.get_angles() << std::endl;
    std::cout << "RFA place: " << reference_frame_A.get_placement_vector() << std::endl;
    std::cout << "RFA trans: " << reference_frame_A.get_transformation_matrix() << std::endl;



    std::cout << std::endl << "TEST 5" << std::endl;
    std::cout << "EXPECTED: " << std::endl 
    << "rot x: " << "1, 0, 0, \n 0, -0.99, -0.14, \n 0, 0.14, -0.99" << std::endl
    << "rot y: " << "-0.99, 0, 0.14, \n 0, 1, 0, \n -0.14, 0, -0.99" << std::endl
    << "rot z: " << "-0.99, -0.14, 0, \n 0.14, -0.99, 0, \n 0, 0, 1" << std::endl;

    std::cout << std::endl << "RETURNED: " << std::endl; 
    std::cout << "rot x: " << MathPositionObject::calculate_rotation_matrix_x(3) << std::endl;
    std::cout << "rot y: " << MathPositionObject::calculate_rotation_matrix_y(3) << std::endl;
    std::cout << "rot z: " << MathPositionObject::calculate_rotation_matrix_z(3) << std::endl;




    std::cout << std::endl << "TEST 6" << std::endl;
    std::cout << "EXPECTED: " << std::endl 
    << "trans: " << "-0.1, -0.91, -0.41, 16, \n 0.09, -0.42, 0.9, 17, \n -0.99, 0.06, 0.12, 18, \n 0, 0, 0, 1" << std::endl;


    std::cout << std::endl << "RETURNED: " << std::endl; 
    std::cout << "trans: " << MathPositionObject::calculate_transformation_matrix(Eigen::Vector3d(13, 14, 15), Eigen::Vector3d(16, 17, 18)) << std::endl;



    std::cout << std::endl << "TEST 7" << std::endl;
    std::cout << "EXPECTED: " << std::endl 
    << "trans: " << "-0.91, -0.30, -0.29, 10.36, \n 0.33, -0.09, -0.94, -4.77, \n 0.26, -0.94, 0.19, 10.62, \n 0, 0, 0, 1" << std::endl;


    std::cout << std::endl << "RETURNED: " << std::endl; 
    std::cout << "trans: " << reference_frame_A.get_expressed_in(&reference_frame_B)->get_transformation_matrix() << std::endl;


    std::cout << "UNIT TEST *COMPLETED*" << std::endl;
    return 0;
}


