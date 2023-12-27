#include <iostream>
#include <map>

int Length(const std::string& s) {
  std::map<char, int> charCount;
  for (char c : s) {
    charCount[c]++;
  }

  int length = 0;
  bool hasOddCount = false;

  for (const auto& pair : charCount) {
    int count = pair.second;
    if (count % 2 == 0) {
      length += count;
    } else {
      length += count - 1;
      hasOddCount = true;
    }
  }
  if (hasOddCount) {
    length += 1;
  }
  return length;
}

int main() {
  std::string s = "acbcccdd";
  std::cout << Length(s) << std::endl;
  return 0;
}