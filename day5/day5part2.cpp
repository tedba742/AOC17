#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream file("input.txt");

    std::vector<int> jumps;
    int value;
    while (file >> value) {
        jumps.push_back(value);
    }

    file.close();

    int steps = 0;
    int position = 0;
    int size = jumps.size();

    while (position >= 0 && position < size) {
        int jump = jumps[position];
        if (jump >= 3) {
            jumps[position] -= 1;
        } else {
            jumps[position] += 1;
        }
        position += jump;
        steps++;
    }
    std::cout << "Result: " << steps << std::endl;

}
