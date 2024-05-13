#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("input.txt");
    std::string digits;

    file >> digits;
    file.close();

    int sum = 0;
    int n = digits.length();

    for (int i = 0; i < n; i++) {
        int nextIndex = (i + 1) % n;
        if (digits[i] == digits[nextIndex]) {
            sum += digits[i] - '0';
        }
    }

    std::cout << "The solution to the captcha is: " << sum << std::endl;
}
