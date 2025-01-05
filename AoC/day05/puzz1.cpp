#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// Function to convert string to integer manually
int stringToInt(const string& str) {
    int number = 0;
    stringstream ss(str);
    ss >> number;
    return number;
}

// Function to check if a given update is in the correct order
bool isValidOrder(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules) {
    unordered_map<int, int> position;
    for (size_t i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }

    for (const auto& [before, afterSet] : rules) {
        if (position.find(before) != position.end()) {
            for (int after : afterSet) {
                if (position.find(after) != position.end() && position[before] > position[after]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    string line;
    unordered_map<int, unordered_set<int>> rules;
    vector<vector<int>> updates;

    // Read ordering rules
    while (getline(inputFile, line) && !line.empty()) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, '|');
        int before = stringToInt(temp);
        getline(ss, temp);
        int after = stringToInt(temp);
        rules[before].insert(after);
    }

    // Read updates
    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<int> update;
        string temp;
        while (getline(ss, temp, ',')) {
            update.push_back(stringToInt(temp));
        }
        updates.push_back(update);
    }

    inputFile.close();

    int sumOfMiddlePages = 0;

    for (const auto& update : updates) {
        if (isValidOrder(update, rules)) {
            // Find the middle page number
            int middleIndex = update.size() / 2;
            sumOfMiddlePages += update[middleIndex];
        }
    }

    cout << "Sum of middle page numbers: " << sumOfMiddlePages << endl;

    return 0;
}

