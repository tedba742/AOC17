#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

struct Point {
    int x = 0;
    int y = 0;
    int z = 0;

    void move(const std::string& direction) {
        if (direction == "n") {
            y += 1; z -= 1;
        } else if (direction == "ne") {
            x += 1; z -= 1;
        } else if (direction == "se") {
            x += 1; y -= 1;
        } else if (direction == "s") {
            y -= 1; z += 1;
        } else if (direction == "sw") {
            x -= 1; z += 1;
        } else if (direction == "nw") {
            x -= 1; y += 1;
        }
    }

    int distance() const {
        return (std::abs(x) + std::abs(y) + std::abs(z)) / 2;
    }
};

int main() {
    std::ifstream infile("input.txt");
    std::string line;

    std::getline(infile, line);
    std::istringstream iss(line);
    std::string direction;

    Point current;
    int maxDistance = 0;

    while (std::getline(iss, direction, ',')) {
        current.move(direction);
        maxDistance = std::max(maxDistance, current.distance());
    }

    std::cout << "Fewest number of steps required to reach the child: " << current.distance() << std::endl;
}
