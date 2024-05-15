#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

using Registers = unordered_map<char, long long>;

long long getValue(const Registers& registers, const string& operand) {
    if (isalpha(operand[0])) {
        return registers.at(operand[0]);
    } else {
        return stoll(operand);
    }
}

void executeSnd(const Registers& registers, const string& x, long long& lastPlayedSound) {
    lastPlayedSound = getValue(registers, x);
}

void executeSet(Registers& registers, const string& x, const string& y) {
    registers[x[0]] = getValue(registers, y);
}

void executeAdd(Registers& registers, const string& x, const string& y) {
    registers[x[0]] += getValue(registers, y);
}

void executeMul(Registers& registers, const string& x, const string& y) {
    registers[x[0]] *= getValue(registers, y);
}

void executeMod(Registers& registers, const string& x, const string& y) {
    registers[x[0]] %= getValue(registers, y);
}

bool executeRcv(const Registers& registers, const string& x, long long lastPlayedSound) {
    if (getValue(registers, x) != 0) {
        cout << "Recovered frequency: " << lastPlayedSound << endl;
        return true;
    }
    return false;
}

bool executeJgz(const Registers& registers, const string& x, const string& y, size_t& pc) {
    if (getValue(registers, x) > 0) {
        pc += getValue(registers, y);
        return true;
    }
    return false;
}

void executeInstructions(const vector<string>& instructions) {
    Registers registers;
    long long lastPlayedSound = 0;
    size_t pc = 0;

    while (pc < instructions.size()) {
        stringstream ss(instructions[pc]);
        string cmd, x, y;
        ss >> cmd >> x >> y;

        if (cmd == "snd") {
            executeSnd(registers, x, lastPlayedSound);
        } else if (cmd == "set") {
            executeSet(registers, x, y);
        } else if (cmd == "add") {
            executeAdd(registers, x, y);
        } else if (cmd == "mul") {
            executeMul(registers, x, y);
        } else if (cmd == "mod") {
            executeMod(registers, x, y);
        } else if (cmd == "rcv") {
            if (executeRcv(registers, x, lastPlayedSound)) {
                return;
            }
        } else if (cmd == "jgz") {
            if (executeJgz(registers, x, y, pc)) {
                continue;
            }
        }
        ++pc;
    }
}

vector<string> readInput(const string& filename) {
    ifstream file(filename);
    vector<string> instructions;
    string line;
    while (getline(file, line)) {
        instructions.push_back(line);
    }
    return instructions;
}

int main() {
    vector<string> instructions = readInput("input.txt");
    executeInstructions(instructions);
}
