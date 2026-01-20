



#include <iostream>
#include "Camera.h"
#include "Vector_Object.h"
#include "Stage.h"
#include "Viewport.h"


int main() {

    Stage s1;

    VectorObject v1(800, 0, 800);
    VectorObject v2(800, 800, 800);
    VectorObject v3(800, -800, 800);

    VectorObject v4(0, 0, 800);
    VectorObject v5(0, 800, 800);
    VectorObject v6(0, -800, 800);

    VectorObject v7(-800, 0, 800);
    VectorObject v8(-800, 800, 800);
    VectorObject v9(-800, -800, 800);


    s1.add(&v1);
    s1.add(&v2);
    s1.add(&v3);

    s1.add(&v4);
    s1.add(&v5);
    s1.add(&v6);

    s1.add(&v7);
    s1.add(&v8);
    s1.add(&v9);



    Camera c1(0, 0, -100);

    c1.set_stage(s1);

    
    Viewport::init();

    Viewport view1(800, 600, 0, 0);
    view1.start();

    view1.set_frame(c1.take_picture());
    view1.update();

    view1.join();

    std::cout << "Done taking a picture\n"; 


    return 0;
}

