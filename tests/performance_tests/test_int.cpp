
#include "Fibonacci.h"
#include "the_library.h"

#include <iostream>
#include <fstream>
#include <string>

void readDocument(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}


int main() {

    Fibonacci fib;
	
    std::cout << "This is the third test executable\n";

    std::cout << fib.getNthFibonacci(6);
    
    hello();
    
    std::string filename = "files/document.txt"; // Reference to the file in the build directory
    readDocument(filename); // Read and print the contents of document.txt

    return 0;  // Return zero to indicate success
}

