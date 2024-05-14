#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
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

        bool found = false;
        for (size_t i = 0; i < numbers.size() && !found; ++i) {
            for (size_t j = 0; j < numbers.size() && !found; ++j) {
                if (i != j && numbers[i] % numbers[j] == 0) {
                    checksum += numbers[i] / numbers[j];
                    found = true;
                }
            }
        }
    }

    file.close();

    std::cout << "The checksum of the spreadsheet is: " << checksum << std::endl;

}
