#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

bool isAnagram(const std::string& word1, const std::string& word2) {
    if (word1.length() != word2.length()) return false;
    std::string sortedWord1 = word1;
    std::string sortedWord2 = word2;
    std::sort(sortedWord1.begin(), sortedWord1.end());
    std::sort(sortedWord2.begin(), sortedWord2.end());
    return sortedWord1 == sortedWord2;
}

bool isValidPassphrase(const std::vector<std::string>& row) {
    std::set<std::string> uniqueWords;
    for (const auto& word : row) {
        std::string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());
        if (uniqueWords.find(sortedWord) != uniqueWords.end()) {
            return false;
        }
        uniqueWords.insert(sortedWord);
    }
    return true;
}

int main() {
    std::fstream file("input.txt");
    std::string line;
    std::vector<std::vector<std::string>> wordVector;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> row;
        std::string toVectorString;

        while (iss >> toVectorString) {
            row.push_back(toVectorString);
        }
        wordVector.push_back(row);
    }

    file.close();
    int count = 0;
    for (const auto& row : wordVector) {
        if (isValidPassphrase(row)) {
            count++;
        }
    }

    std::cout << "Result: " << count << std::endl;

}
