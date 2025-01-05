#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <utility>
#include <limits>
#include <cmath>

struct Machine {
    int ax, ay; // Button A increments
    int bx, by; // Button B increments
    long long px, py; // Prize location (with offset)
};

struct State {
    long long x, y;
    int cost;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

std::tuple<int, int, int> minCostToWin(const Machine& machine) {
    long long gcdX = gcd(machine.ax, machine.bx);
    long long gcdY = gcd(machine.ay, machine.by);

    if (machine.px % gcdX != 0 || machine.py % gcdY != 0) {
        return {std::numeric_limits<int>::max(), -1, -1};
    }

    long long normPx = machine.px / gcdX;
    long long normPy = machine.py / gcdY;

    int normAx = machine.ax / gcdX;
    int normAy = machine.ay / gcdY;
    int normBx = machine.bx / gcdX;
    int normBy = machine.by / gcdY;

    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    std::unordered_map<std::pair<long long, long long>, int, PairHash> visited;

    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto [x, y, cost] = pq.top();
        pq.pop();

        if (x == normPx && y == normPy) {
            return {cost, (x * gcdX - machine.px) / machine.ax, (y * gcdY - machine.py) / machine.by};
        }

        auto stateKey = std::make_pair(x, y);
        if (visited.count(stateKey) && visited[stateKey] <= cost) {
            continue;
        }
        visited[stateKey] = cost;

        pq.push({x + normAx, y + normAy, cost + 3});
        pq.push({x + normBx, y + normBy, cost + 1});
    }

    return {std::numeric_limits<int>::max(), -1, -1};
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
        sscanf(line.c_str(), "Prize: X=%lld, Y=%lld\n", &machine.px, &machine.py);
        machine.px += 10000000000000LL;
        machine.py += 10000000000000LL;
        machines.push_back(machine);
        std::getline(input, line);
    }

    int totalCost = 0;
    int prizesWon = 0;

    for (const auto& machine : machines) {
        auto [cost, _, __] = minCostToWin(machine);
        if (cost != std::numeric_limits<int>::max()) {
            totalCost += cost;
            ++prizesWon;
        }
    }

    std::cout << "Maximum prizes won: " << prizesWon << "\n";
    std::cout << "Minimum tokens required: " << totalCost << "\n";

    return 0;
}

