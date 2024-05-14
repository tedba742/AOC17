#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

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

int calculateTotalWeight(const std::string& name, const std::unordered_map<std::string, Program>& programs, std::unordered_map<std::string, int>& totalWeights) {
    const Program& program = programs.at(name);
    int totalWeight = program.weight;
    for (const std::string& child : program.children) {
        totalWeight += calculateTotalWeight(child, programs, totalWeights);
    }
    totalWeights[name] = totalWeight;
    return totalWeight;
}

int findUnbalancedProgram(const std::string& name, const std::unordered_map<std::string, Program>& programs, const std::unordered_map<std::string, int>& totalWeights) {
    const Program& program = programs.at(name);
    std::unordered_map<int, std::vector<std::string>> weightToChildren;
    for (const std::string& child : program.children) {
        int childWeight = totalWeights.at(child);
        weightToChildren[childWeight].push_back(child);
    }

    if (weightToChildren.size() == 1) {
        return 0;
    }

    std::string unbalancedChild;
    int correctWeight, wrongWeight;
    for (const auto& pair : weightToChildren) {
        if (pair.second.size() == 1) {
            unbalancedChild = pair.second[0];
            wrongWeight = pair.first;
        } else {
            correctWeight = pair.first;
        }
    }

    int weightDifference = correctWeight - wrongWeight;
    int unbalancedProgramWeight = programs.at(unbalancedChild).weight;
    int correctedWeight = unbalancedProgramWeight + weightDifference;

    int deeperCorrection = findUnbalancedProgram(unbalancedChild, programs, totalWeights);
    if (deeperCorrection != 0) {
        return deeperCorrection;
    } else {
        std::cout << "The unbalanced program is: " << unbalancedChild << " with weight " << unbalancedProgramWeight << " should be " << correctedWeight << std::endl;
        return correctedWeight;
    }
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

    std::unordered_map<std::string, int> totalWeights;
    calculateTotalWeight(bottomProgram, programs, totalWeights);

    int correctedWeight = findUnbalancedProgram(bottomProgram, programs, totalWeights);
    if (correctedWeight != 0) {
        std::cout << "The corrected weight for the unbalanced program is: " << correctedWeight << std::endl;
    }

}
