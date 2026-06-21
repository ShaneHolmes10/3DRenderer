#include <chrono>
#include <cmath>
#include <iostream>
#include <string>

#include "CppUnitLite/TestHarness.h"
#include "display/frame_buffer.h"
#include "display/viewport.h"

FrameBuffer create_circle_framebuffer(int width, int height, int cx,
                                      int cy, int radius) {
    FrameBuffer fb(width, height);

    // Fill with white background
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            fb.setPixel(x, y, 255, 255, 255);
        }
    }

    // Draw green circle
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            int dx = x - cx;
            int dy = y - cy;
            if (dx * dx + dy * dy <= radius * radius) {
                fb.setPixel(x, y, 0, 255, 0);  // Green
            }
        }
    }

    return fb;
}

TEST(Viewport, SetFrameDisplaysGreenCircle) {
    int width = 600;
    int height = 400;

    Viewport::init();

    Viewport v1(width, height);
    v1.start();

    v1.setFrame(create_circle_framebuffer(width, height, width / 2,
                                          height / 2, 100));
    v1.update();

    std::string answer;
    std::cout << "Did the screen show a green circle: ";
    std::cin >> answer;

    CHECK(answer == "y");

    v1.join();
}

TEST(Viewport, AnimatedCircleMovesDownward) {
    int width = 600;
    int height = 400;

    Viewport::init();

    Viewport v1(width, height);
    v1.start();

    for (int n = 0; n < 50; n++) {
        v1.setFrame(create_circle_framebuffer(width, height, width / 2,
                                              height / 2 + n * 4, 100));
        v1.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::string answer;
    std::cout << "Did the screen show a green circle animation: ";
    std::cin >> answer;

    CHECK(answer == "y");

    v1.join();
}

int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}