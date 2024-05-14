#include <iostream>
#include <fstream>
#include <string>

int calculateCircularMatchSum(const std::string& digits) {
    int n = digits.length();
    int step = n / 2;
    int total_sum = 0;

    for (int i = 0; i < n; ++i) {
        int match_index = (i + step) % n;
        if (digits[i] == digits[match_index]) {
            total_sum += digits[i] - '0';
        }
    }

    return total_sum;
}

void processFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    while (getline(file, line)) {
        if (!line.empty()) {
            int result = calculateCircularMatchSum(line);
            std::cout << "Sum for line \"" << line << "\": " << result << std::endl;
        }
    }

    file.close();
}

int main() {
    processFile("input.txt");
    return 0;
}
