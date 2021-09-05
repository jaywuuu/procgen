#include "types.h"
#include "noisefunc.h"

#include <iostream>

int main(int argc, void* argv[]) {
    std::cout << "Testing the noise function.\n";
    const unsigned seed = 1234;

    NoiseFunction noiseFunc(1234);

    std::cout << "Generating function of 100 values with seed: " << seed << "\n";
    unsigned vals[100];

    for (int i = 0; i < 100; ++i) {
        vals[i] = noiseFunc.noise1D(i);
        std::cout << vals[i];
        if (i < 99)
            std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Generating function of 100 values with same seed: " << seed << "\n";
    unsigned vals2[100];
    for (int i = 0; i < 100; ++i) {
        vals2[i] = noiseFunc.noise1D(i);
        std::cout << vals2[i];
        if (i < 99)
            std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Given same seed, values should be the same.\n";

    for (int i = 0; i < 100; ++i) {
        if (vals[i] != vals2[i]) {
            std::cout << "Error. Values from same seed is not the same.\n";
            return -1;
        }
    }
    
    std::cout << "Test PASSED!\n";

    return 0;
}