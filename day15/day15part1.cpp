#include <iostream>
#include <cstdint>

int main() {
    uint64_t generatorA = 699;
    uint64_t generatorB = 124;

    const uint64_t factorA = 16807;
    const uint64_t factorB = 48271;

    const uint64_t divider = 2147483647;

    const int pairsToCompare = 5000000; // change to 40 000 000 if doing part1.

    int matchCount = 0;

    for (int i = 0; i < pairsToCompare; i++) {
        generatorA = (generatorA * factorA) % divider;
        generatorB = (generatorB * factorB) % divider;

        // Compare the lowest 16 bits
        if ((generatorA & 0xFFFF) == (generatorB & 0xFFFF)) {
            ++matchCount;
        }
    }

    std::cout << "Final count of matches: " << matchCount << std::endl;

}
