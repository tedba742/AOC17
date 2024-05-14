#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>

bool evaluateCondition(const std::unordered_map<std::string, int>& registers, const std::string& reg, const std::string& op, int value) {
    auto it = registers.find(reg);
    int regValue = (it != registers.end()) ? it->second : 0;

    if (op == ">") return regValue > value;
    if (op == "<") return regValue < value;
    if (op == ">=") return regValue >= value;
    if (op == "<=") return regValue <= value;
    if (op == "==") return regValue == value;
    if (op == "!=") return regValue != value;
    return false;
}

void processInstruction(std::unordered_map<std::string, int>& registers, const std::string& reg, const std::string& op, int value) {
    if (op == "inc") {
        registers[reg] += value;
    } else if (op == "dec") {
        registers[reg] -= value;
    }
}

int main() {
    std::ifstream infile("input.txt");
    std::string line;
    std::unordered_map<std::string, int> registers;
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string reg, op, condReg, condOp;
        int value, condValue;
        std::string dummy;

        iss >> reg >> op >> value >> dummy >> condReg >> condOp >> condValue;

        if (evaluateCondition(registers, condReg, condOp, condValue)) {
            processInstruction(registers, reg, op, value);
        }
    }

    auto maxRegister = std::max_element(registers.begin(), registers.end(),
                                        [](const auto& a, const auto& b) {
                                            return a.second < b.second;
                                        });

    if (maxRegister != registers.end()) {
        std::cout << "The largest value in any register is: " << maxRegister->second << std::endl;
    } else {
        std::cout << "No instructions were processed." << std::endl;
    }
}
