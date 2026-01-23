#include <iostream>
#include "Testing_Utils.h"
#include "Testing_Methods.h"
#include <vector>
#include <Eigen/Dense>


/*
    This will test the Bresenham algorithm against multiple scenarios to test fidelity


*/



/*

*/
void test_1() {

    std::vector<int> y_compare = {9, 9, 9, 9, 10, 10};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 14, 10);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_2() {

    std::vector<int> x_compare = {8, 9, 10, 11, 12, 13};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 14, 10);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_3() {

    std::vector<int> y_compare = {8, 8, 8, 8};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 12, 8);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_4() {

    std::vector<int> x_compare = {8, 9, 10, 11};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 12, 8);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_5() {

    std::vector<int> y_compare = {7, 7, 6, 6, 6, 5, 5};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 15, 5);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_6() {

    std::vector<int> x_compare = {8, 9, 10, 11, 12, 13, 14};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 15, 5);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_7() {

    std::vector<int> y_compare = {7, 6, 5, 4};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 12, 3);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_8() {

    std::vector<int> x_compare = {8, 9, 10, 11};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 12, 3);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_9() {

    std::vector<int> y_compare = {7, 6, 5, 4, 3};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 8, 2);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_10() {

    std::vector<int> x_compare = {7, 8, 8, 8, 8};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 8, 2);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_11() {

    std::vector<int> y_compare = {7, 6, 5, 4};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 7, 3);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_12() {

    std::vector<int> x_compare = {7, 7, 7, 7};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 7, 3);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_13() {

    std::vector<int> y_compare = {7, 6, 5, 4, 3};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 3, 2);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_14() {

    std::vector<int> x_compare = {6, 5, 4, 4, 3};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 3, 2);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_15() {

    std::vector<int> y_compare = {7, 6, 5, 4, 3};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 2);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_16() {

    std::vector<int> x_compare = {6, 5, 4, 3, 2};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 2);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_17() {

    std::vector<int> y_compare = {7, 7, 7, 6, 6};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 6);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_18() {

    std::vector<int> x_compare = {6, 5, 4, 3, 2};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 6);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_19() {

    std::vector<int> y_compare = {8, 8, 8};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 3, 8);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_20() {

    std::vector<int> x_compare = {6, 5, 4};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 3, 8);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_21() {

    std::vector<int> y_compare = {9, 10, 10, 11, 11};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 11);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_22() {

    std::vector<int> x_compare = {6, 5, 4, 3, 2};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 11);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_23() {

    std::vector<int> y_compare = {9, 10, 11, 12, 13};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_24() {

    std::vector<int> x_compare = {6, 5, 4, 3, 2};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 1, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_25() {

    std::vector<int> y_compare = {9, 10, 11, 12, 13};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 4, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_26() {

    std::vector<int> x_compare = {6, 5, 5, 4, 4};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 4, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_27() {

    std::vector<int> y_compare = {9, 10, 11, 12};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 7, 13);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_28() {

    std::vector<int> x_compare = {7, 7, 7, 7};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 7, 13);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_29() {

    std::vector<int> y_compare = {9, 10, 11, 12, 13};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 9, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_30() {

    std::vector<int> x_compare = {8, 8, 8, 9, 9};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 9, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_31() {

    std::vector<int> y_compare = {9, 10, 11, 12, 13};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 13, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_32() {

    std::vector<int> x_compare = {8, 9, 10, 11, 12};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(7, 8, 13, 14);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_33() {

    std::vector<int> y_compare = {0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(0, 0, 21, 4);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_34() {

    std::vector<int> x_compare = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(0, 0, 21, 4);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_35() {

    std::vector<int> y_compare = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(21, 4, 16, 17);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_36() {

    std::vector<int> x_compare = {20, 20, 19, 19, 19, 18, 18, 18, 17, 17, 16, 16};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(21, 4, 16, 17);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
        )
    );

}

/*

*/
void test_37() {

    std::vector<int> y_compare = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(16, 17, 0, 0);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            y_compare, 
            values[1]
        )
    );

}

/*

*/
void test_38() {

    std::vector<int> x_compare = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    std::array<std::vector<int>, 2> values = TestMeth::Bresenham(16, 17, 0, 0);

    TestUtils::pass_or_fail_printout(
        TestUtils::check_std_vector_similarity(
            x_compare, 
            values[0]
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
    TestUtils::perform_test(test_16);
    TestUtils::perform_test(test_17);
    TestUtils::perform_test(test_18);
    TestUtils::perform_test(test_19);
    TestUtils::perform_test(test_20);
    TestUtils::perform_test(test_21);
    TestUtils::perform_test(test_22);
    TestUtils::perform_test(test_23);
    TestUtils::perform_test(test_24);
    TestUtils::perform_test(test_25);
    TestUtils::perform_test(test_26);
    TestUtils::perform_test(test_27);
    TestUtils::perform_test(test_28);
    TestUtils::perform_test(test_29);
    TestUtils::perform_test(test_30);
    TestUtils::perform_test(test_31);
    TestUtils::perform_test(test_32);
    TestUtils::perform_test(test_33);
    TestUtils::perform_test(test_34);
    TestUtils::perform_test(test_35);
    TestUtils::perform_test(test_36);
    TestUtils::perform_test(test_37);
    TestUtils::perform_test(test_38);

    TestUtils::end_testing();

    return 0;
}


