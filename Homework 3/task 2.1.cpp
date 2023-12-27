#include <iostream>
#include <map>

int UniqueCharacter(const std::string& s) {
  std::map<char, int> charCount;

  for (char c : s) {
    charCount[c]++;
  }

  for (int i = 0; i < s.size(); i++) {
    if (charCount[s[i]] == 1) {
      return i;
    }
  }

  return -1;
}

int main() {
  std::string s1 = "apple";
  std::cout << UniqueCharacter(s1) << std::endl;

  std::string s2 = "staticanalysis";
  std::cout << UniqueCharacter(s2) << std::endl;

  std::string s3 = "aabb";
  std::cout << UniqueCharacter(s3) << std::endl;

  return 0;
}