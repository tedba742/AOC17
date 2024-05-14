#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
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
    int count{0};
    for (const auto& row : wordVector) {
        std::set<std::string> uniqueItems(row.begin(), row.end());
        if(uniqueItems.size() == row.size()){
            count++;
        }
    }

    std::cout << "Result: "<< count << std::endl; 
}
