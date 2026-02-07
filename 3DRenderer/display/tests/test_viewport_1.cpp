#include "CppUnitLite/TestHarness.h"
#include "display/Viewport.h"
#include <iostream>
#include <string>


TEST(Viewport, CreateWindowWithDefaultDimensions)
{
    Viewport::init();

    Viewport v1;
    v1.start();

    std::string answer;
    std::cout << "Did the window appear: ";
    std::cin >> answer;

    CHECK(answer == "y");

    v1.join();
}


TEST(Viewport, CreateWindowWithCustomDimensions)
{
    Viewport::init();

    Viewport v1(1000, 800);
    v1.start();

    std::string answer;
    std::cout << "Did the window appear with larger dimensions: ";
    std::cin >> answer;

    CHECK(answer == "y");

    v1.join();
}


TEST(Viewport, CreateWindowWithDimensionsAndLocation)
{
    Viewport::init();

    Viewport v1(800, 600, 0, 0);
    v1.start();

    std::string answer;
    std::cout << "Did the window appear with larger dimensions and in the right location: ";
    std::cin >> answer;

    CHECK(answer == "y");

    v1.join();
}


TEST(Viewport, CreateTwoWindowsSimultaneously)
{
    Viewport::init();

    Viewport v1(600, 400, 0, 0);
    v1.start();

    Viewport v2(600, 400, 400, 0);
    v2.start();

    std::string answer;
    std::cout << "Did both windows show up: ";
    std::cin >> answer;
    
    CHECK(answer == "y");

    v1.join();
    v2.join();
}


int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}