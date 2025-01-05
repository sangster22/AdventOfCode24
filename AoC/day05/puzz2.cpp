#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Function to convert string to integer manually
int stringToInt(const string& str) {
    int number = 0;
    stringstream ss(str);
    ss >> number;
    return number;
}

// Divide and conquer approach to check if an update is in valid order
bool isValidOrderDC(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules, int start, int end) {
    if (end - start <= 1) return true;

    int mid = (start + end) / 2;
    bool leftValid = isValidOrderDC(update, rules, start, mid);
    bool rightValid = isValidOrderDC(update, rules, mid, end);

    if (!leftValid || !rightValid) return false;

    unordered_map<int, int> position;
    for (int i = start; i < end; ++i) {
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

// Divide and conquer approach to reorder an update
vector<int> reorderUpdateDC(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules, int start, int end) {
    if (end - start <= 1) return {update.begin() + start, update.begin() + end};

    int mid = (start + end) / 2;
    vector<int> left = reorderUpdateDC(update, rules, start, mid);
    vector<int> right = reorderUpdateDC(update, rules, mid, end);

    vector<int> merged;
    auto itLeft = left.begin(), itRight = right.begin();
    while (itLeft != left.end() && itRight != right.end()) {
        if (rules.count(*itLeft) && rules.at(*itLeft).count(*itRight)) {
            merged.push_back(*itLeft++);
        } else if (rules.count(*itRight) && rules.at(*itRight).count(*itLeft)) {
            merged.push_back(*itRight++);
        } else if (*itLeft < *itRight) {
            merged.push_back(*itLeft++);
        } else {
            merged.push_back(*itRight++);
        }
    }
    merged.insert(merged.end(), itLeft, left.end());
    merged.insert(merged.end(), itRight, right.end());

    return merged;
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
        vector<int> reorderedUpdate = update;
        bool needsReordering = !isValidOrderDC(update, rules, 0, update.size());
        if (needsReordering) {
            // Reorder the update using divide and conquer if it's not valid
            reorderedUpdate = reorderUpdateDC(update, rules, 0, update.size());
            // Compute the middle page number after reordering
            int middleIndex = reorderedUpdate.size() / 2;
            sumOfMiddlePages += reorderedUpdate[middleIndex];
        }
    }

    cout << "Sum of middle page numbers after reordering: " << sumOfMiddlePages << endl;

    return 0;
}


