#include <iostream>
#include <map>
#include <vector>

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

struct PointCompare {
    bool operator()(const Point& a, const Point& b) const {
        return std::tie(a.x, a.y) < std::tie(b.x, b.y);
    }
};

int sumAdjacent(const std::map<Point, int, PointCompare>& grid, const Point& p) {
    static const std::vector<Point> directions = {
        Point(-1, -1), Point(-1, 0), Point(-1, 1),
        Point(0, -1),              Point(0, 1),
        Point(1, -1), Point(1, 0), Point(1, 1)
    };
    int sum = 0;
    for (const Point& d : directions) {
        Point neighbor(p.x + d.x, p.y + d.y);
        if (grid.find(neighbor) != grid.end()) {
            sum += grid.at(neighbor);
        }
    }
    return sum;
}

int firstValueLargerThan(int puzzleInput) {
    std::map<Point, int, PointCompare> grid;
    Point current(0, 0);
    grid[current] = 1;

    static const std::vector<Point> directions = {
        Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)
    };

    int directionIndex = 0;
    int steps = 1;
    int stepsInCurrentDirection = 0;
    int stepsInCurrentLength = 0;

    while (true) {
        if (stepsInCurrentDirection == steps) {
            directionIndex = (directionIndex + 1) % 4;
            stepsInCurrentDirection = 0;
            stepsInCurrentLength++;
            if (stepsInCurrentLength == 2) {
                steps++;
                stepsInCurrentLength = 0;
            }
        }

        current.x += directions[directionIndex].x;
        current.y += directions[directionIndex].y;
        stepsInCurrentDirection++;

        int value = sumAdjacent(grid, current);
        grid[current] = value;

        if (value > puzzleInput) {
            return value;
        }
    }

    return -1;
}

int main() {
    int puzzleInput = 347991;
    int result = firstValueLargerThan(puzzleInput);
    std::cout << "The first value larger than " << puzzleInput << " is: " << result << std::endl;
    return 0;
}
