#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include "display/viewport.h"
#include "display/frame_buffer.h"
#include "display/key.h"

int main() {
    
    Viewport::init();
    
    Viewport viewport(800, 600, 100, 100);
    
    FrameBuffer frame_buffer(800, 600);
    
    // Fill with a gradient test pattern
    for(size_t y = 0; y < 600; y++) {
        for(size_t x = 0; x < 800; x++) {
            uint8_t r = (x * 255) / 800;
            uint8_t g = (y * 255) / 600;
            uint8_t b = 128;
            frame_buffer.setPixel(x, y, r, g, b);
        }
    }
    
    viewport.setFrame(frame_buffer);
    viewport.update();
    
    std::atomic<bool> running(true);
    
    // Set up keyboard callback
    viewport.setKeyCallback([&](Key key) {
        std::cout << "Key pressed: ";
        
        switch(key) {
            case W:
                std::cout << "W (Forward)";
                break;
            case S:
                std::cout << "S (Backward)";
                break;
            case A:
                std::cout << "A (Left)";
                break;
            case D:
                std::cout << "D (Right)";
                break;
            case Q:
                std::cout << "Q (Up)";
                break;
            case E:
                std::cout << "E (Down)";
                break;
            case Up:
                std::cout << "Up Arrow";
                break;
            case Down:
                std::cout << "Down Arrow";
                break;
            case Left:
                std::cout << "Left Arrow";
                break;
            case Right:
                std::cout << "Right Arrow";
                break;
            case Space:
                std::cout << "Space";
                break;
            case Escape:
                std::cout << "Escape (Exiting...)";
                running = false;
                break;
            case F1:
                std::cout << "F1";
                break;
            case F2:
                std::cout << "F2";
                break;
            default:
                std::cout << "Other key (code: " << static_cast<int>(key) << ")";
                break;
        }
        
        std::cout << "\n";
    });
    
    std::cout << "=================================\n";
    std::cout << "Keyboard Demo Started\n";
    std::cout << "=================================\n";
    std::cout << "Press keys to see output:\n";
    std::cout << "  WASD - Movement\n";
    std::cout << "  Q/E - Up/Down\n";
    std::cout << "  Arrow Keys\n";
    std::cout << "  Space, F1, F2, etc.\n";
    std::cout << "  Escape - Exit\n";
    std::cout << "=================================\n\n";
    
    viewport.start();
    
    // Keep main thread alive while viewport is running
    while(running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "\nDemo ended.\n";
    
    viewport.join();
    
    return 0;
}