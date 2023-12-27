#include <iostream>
#include <set>
#include <string>

int string(const std::string& s) {
    int maxLength = 0;
    std::set<char> uniqueChars;
    int left = 0;
    int right = 0;

    while (right < s.length()) {
        if (uniqueChars.count(s[right]) == 0) {
            uniqueChars.insert(s[right]);
            maxLength = std::max(maxLength, right - left + 1);
            right++;
        } else {
            uniqueChars.erase(s[left]);
            left++;
        }
    }

    return maxLength;
}

int main() {
    std::string s = "abcabcbb";
    int length = string(s);
    std::cout << "The length of the longest substring without repeating characters is: " << length << std::endl;
    return 0;
}