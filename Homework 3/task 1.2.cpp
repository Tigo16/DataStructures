#include <iostream>
#include <string>
#include <set>

int StonesCount(const std::string& jewels, const std::string& stones) {
    std::set<char> jewelSet;
    for (char jewel : jewels) {
        jewelSet.insert(jewel);
    }

    int count = 0;
    for (char stone : stones) {
        if (jewelSet.count(stone) > 0) {
            count++;
        }
    }
    return count;
}

int main() {
    std::string jewels = "aA";
    std::string stones = "aAAbbbb";
    int UniqueCount = StonesCount(jewels, stones);
    std::cout << UniqueCount << std::endl;
    return 0;
}

