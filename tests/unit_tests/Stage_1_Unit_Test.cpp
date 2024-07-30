#include <iostream>
#include "Testing_Utils.h"
#include "Stage.h"
#include <vector>
#include <chrono>


/*
This test will confirm some basic functionality of the Stage class

Ensuring that the stage can have vectors added to it
Ensure that the vector list can be recieved

*/




/*
    Test to see that the stage vectors are added properly and that the list can be retrieved
*/
void test_1() {

    Stage s1;

    VectorObject v1(0, 2, 3);
    VectorObject v2(2, 3, 1);
    VectorObject v3(4, 2, 4);
    VectorObject v4(5, 1, 1);

    s1.add(&v1);
    s1.add(&v2);
    s1.add(&v3);
    s1.add(&v4);


    std::vector<VectorObject*>& v_list = s1.get_vector_list();

    bool ret = true;
    if( !(v_list[0]->get_placement_vector()[0] == 0 && 
        v_list[0]->get_placement_vector()[1] == 2 &&
        v_list[0]->get_placement_vector()[2] == 3) ) {
            ret = false;
    }

    if( !(v_list[1]->get_placement_vector()[0] == 2 && 
        v_list[1]->get_placement_vector()[1] == 3 &&
        v_list[1]->get_placement_vector()[2] == 1) ) {
            ret = false;
    }

    if( !(v_list[2]->get_placement_vector()[0] == 4 && 
        v_list[2]->get_placement_vector()[1] == 2 &&
        v_list[2]->get_placement_vector()[2] == 4) ) {
            ret = false;
    }

    if( !(v_list[3]->get_placement_vector()[0] == 5 && 
        v_list[3]->get_placement_vector()[1] == 1 &&
        v_list[3]->get_placement_vector()[2] == 1) ) {
            ret = false;
    }

    TestUtils::pass_or_fail_printout(
        ret
    );

}



int main() {

    TestUtils::start_testing();

    TestUtils::perform_test(test_1);

    TestUtils::end_testing();

    return 0;
}