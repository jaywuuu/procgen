#include "random.h"
#include "types.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;

int main(int argc, void *argv[]) {
    std::cout << "Testing NoiseFunctionRNG.\n";

    const unsigned x = 0;
    const unsigned y = 9;

    std::cout << "Rolling random mumber between: (" << x << ", " << y << ")\n";

    system_clock::time_point now = system_clock::now();
    unsigned seed = static_cast<unsigned>(system_clock::to_time_t(now));

    NoiseFunctionRNG rng(seed);

    std::cout << "Rolling 100 times... \n";

    unsigned buckets[10] = {};

    for (int i = 0; i < 100; ++i) {
        unsigned num = rng.getRandUIntInRange(x, y);
        std::cout << num;
        if (i < 99) {
            std::cout << ", ";
        }

        if (num < x || num > y) {
            std::cout << "Error.  Random number is out of range. \n";
            return -1;
        }

        buckets[num]++;
    }
    std::cout << std::endl;

    std::cout << "Distribution: \n";
    for (int i = 0; i < 10; ++i) {
        std::cout << i << ": " << buckets[i] << std::endl;
    }

    std::cout << "Test PASSED!\n";

    return 0;
}