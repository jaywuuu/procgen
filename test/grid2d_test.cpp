#include "types.h"

#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Testing the Grid.\n";

    const unsigned x = 80;
    const unsigned y = 60;
    
    std::cout << "Creating grid of size: (" << x << ", " << y << ")\n";

    Grid2D grid(x, y);

    std::cout << "Filling grid with 1s...\n";

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            grid[i][j] = 1;
        }
    }

    std::cout << "Checking all values are 1s...\n";
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            if (grid[i][j] != 1) {
                std::cout << "Error.  Not all values are 1.\n";
                return -1;
            }
        }
    }
    
    std::cout << "Test PASSED!\n";

    return 0;
}