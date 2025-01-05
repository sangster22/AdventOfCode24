#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <tuple>

struct Machine {
    int ax, ay; // Button A increments
    int bx, by; // Button B increments
    int px, py; // Prize location
};

// Function to calculate the minimum cost to align the claw with the prize
std::tuple<int, int, int> minCostToWin(const Machine& machine, int maxPresses) {
    int minCost = std::numeric_limits<int>::max();
    int bestA = -1, bestB = -1;

    for (int a = 0; a <= maxPresses; ++a) {
        for (int b = 0; b <= maxPresses; ++b) {
            int x = a * machine.ax + b * machine.bx;
            int y = a * machine.ay + b * machine.by;

            if (x == machine.px && y == machine.py) {
                int cost = a * 3 + b * 1;
                if (cost < minCost) {
                    minCost = cost;
                    bestA = a;
                    bestB = b;
                }
            }
        }
    }

    return {minCost, bestA, bestB};
}

int main() {
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input file!\n";
        return 1;
    }

    std::vector<Machine> machines;
    std::string line;

    while (std::getline(input, line)) {
        Machine machine;
        sscanf(line.c_str(), "Button A: X+%d, Y+%d\n", &machine.ax, &machine.ay);
        std::getline(input, line);
        sscanf(line.c_str(), "Button B: X+%d, Y+%d\n", &machine.bx, &machine.by);
        std::getline(input, line);
        sscanf(line.c_str(), "Prize: X=%d, Y=%d\n", &machine.px, &machine.py);
        machines.push_back(machine);
        std::getline(input, line); // Skip empty line if present
    }

    int maxPresses = 100;
    int totalCost = 0;
    int prizesWon = 0;

    for (const auto& machine : machines) {
        auto [cost, a, b] = minCostToWin(machine, maxPresses);
        if (cost != std::numeric_limits<int>::max()) {
            totalCost += cost;
            ++prizesWon;
        }
    }

    std::cout << "Maximum prizes won: " << prizesWon << "\n";
    std::cout << "Minimum tokens required: " << totalCost << "\n";

    return 0;
}

