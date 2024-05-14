#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> readFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int main() {
    std::vector<std::string> lines = readFile("input.txt");
    std::vector<int> intlines;
    std::stringstream ss(lines[0]);
    std::string word;
    
    while (ss >> word) {
        intlines.push_back(std::stoi(word));
    }

    std::unordered_map<std::string, int> seen;
    std::string initial_state = std::to_string(intlines[0]);
    for (size_t i = 1; i < intlines.size(); ++i) {
        initial_state += "," + std::to_string(intlines[i]);
    }
    seen[initial_state] = 0;

    bool done = false;
    int iters = 0;
    int first_occurrence = 0;
    
    while (!done) {
        int maxind = 0;
        iters++;
        for (size_t i = 1; i < intlines.size(); ++i) {
            if (intlines[i] > intlines[maxind]) {
                maxind = i;
            }
        }

        int nums = intlines[maxind];
        intlines[maxind] = 0;
        for (int i = 1; i <= nums; ++i) {
            intlines[(maxind + i) % intlines.size()]++;
        }

        std::string current_state = std::to_string(intlines[0]);
        for (size_t i = 1; i < intlines.size(); ++i) {
            current_state += "," + std::to_string(intlines[i]);
        }

        if (seen.find(current_state) != seen.end()) {
            first_occurrence = seen[current_state];
            done = true;
        } else {
            seen[current_state] = iters;
        }
    }

    int loop_size = iters - first_occurrence;
    std::cout << "Number of cycles in the loop: " << loop_size << std::endl;
    return 0;
}
