#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

int main() {
    std::fstream file("input.txt");
    std::string line;
    int checksum = 0;

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> numbers;
        int number;

        while (iss >> number) {
            numbers.push_back(number);
        }

        if (!numbers.empty()) {
            int min_value = *std::min_element(numbers.begin(), numbers.end());
            int max_value = *std::max_element(numbers.begin(), numbers.end());
            checksum += (max_value - min_value);
        }
    }

    file.close();
    std::cout << "The checksum of the spreadsheet is: " << checksum << std::endl;
}
