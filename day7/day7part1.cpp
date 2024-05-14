#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Program {
    std::string name;
    int weight;
    std::vector<std::string> children;
};

void parseLine(const std::string& line, std::unordered_map<std::string, Program>& programs) {
    std::istringstream iss(line);
    std::string name;
    std::string weightStr;
    iss >> name >> weightStr;
    int weight = std::stoi(weightStr.substr(1, weightStr.size() - 2));
    
    Program program{name, weight, {}};
    std::string arrow;
    iss >> arrow;
    if (arrow == "->") {
        std::string child;
        while (iss >> child) {
            if (child.back() == ',') child.pop_back();
            program.children.push_back(child);
        }
    }
    programs[name] = program;
}

std::string findBottomProgram(const std::unordered_map<std::string, Program>& programs) {
    std::unordered_set<std::string> allPrograms;
    std::unordered_set<std::string> childPrograms;
    
    for (const auto& pair : programs) {
        const std::string& name = pair.first;
        const Program& program = pair.second;
        allPrograms.insert(name);
        for (const auto& child : program.children) {
            childPrograms.insert(child);
        }
    }
    
    for (const auto& name : allPrograms) {
        if (childPrograms.find(name) == childPrograms.end()) {
            return name;
        }
    }
    
    return "";
}

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    std::unordered_map<std::string, Program> programs;
    
    while (std::getline(infile, line)) {
        parseLine(line, programs);
    }
    
    std::string bottomProgram = findBottomProgram(programs);
    std::cout << "The bottom program is: " << bottomProgram << std::endl;
}
