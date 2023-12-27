#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::string SortString(const std::string& s) {
    std::map<char, int> freqMap;
    for (char c : s) {
        freqMap[c]++;
    }
    std::vector<std::pair<char, int>> freqVector(freqMap.begin(), freqMap.end());
    std::sort(freqVector.begin(), freqVector.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    std::string result;
    for (const auto& pair : freqVector) {
        result += std::string(pair.second, pair.first);
    }
    return result;
}

int main() {
    std::string s = "tree";
    std::string sortedString = SortString(s);
    std::cout << sortedString << std::endl;

    return 0;
}