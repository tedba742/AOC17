#include <iostream>
#include <cmath>
#include <algorithm>

int calculateManhattanDistance(int input) {

    int layer = 0;
    while ((2 * layer + 1) * (2 * layer + 1) < input) {
        ++layer;
    }

    int maxValInLayer = (2 * layer + 1) * (2 * layer + 1);

    int sideLength = 2 * layer;

    int offset = maxValInLayer - input;

    int sidePosition = offset % sideLength;

    int distanceToCenterOfSide = std::abs(sidePosition - layer);

    int distance = layer + distanceToCenterOfSide;

    return distance;
}

int main() {
    int puzzleInput = 347991;
    int distance = calculateManhattanDistance(puzzleInput);
    std::cout << "The Manhattan Distance is: " << distance << std::endl;
    return 0;
}
