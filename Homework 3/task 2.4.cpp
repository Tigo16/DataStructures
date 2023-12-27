#include <iostream>
#include <string>
#include <sstream>
#include <map>

bool wordPatt(const std::string& pattern, const std::string& s) {
  std::map<char, std::string> pattMap;
  std::map<std::string, char> wordMap;
  std::istringstream ss(s);
  std::string word;
  int i = 0;

  for (char c : pattern) {
    if (!(ss >> word)) {
      return false;
    }

    if (pattMap.count(c) > 0 && pattMap[c] != word) {
      return false;
    }

    if (wordMap.count(word) > 0 && wordMap[word] != c) {
      return false;
    }

    pattMap[c] = word;
    wordMap[word] = c;
    i++;
  }

  if (ss >> word) {
    return false;
  }

  return i == pattern.size();
}

int main() {
  std::string pattern1 = "abba";
  std::string s1 = "dog cat cat dog";
  std::cout << std::boolalpha << wordPatt(pattern1, s1) << std::endl;

  std::string pattern2 = "abba";
  std::string s2 = "dog cat cat fish";
  std::cout << std::boolalpha << wordPatt(pattern2, s2) << std::endl;

  std::string pattern3 = "aaaa";
  std::string s3 = "dog cat cat dog";
  std::cout << std::boolalpha << wordPatt(pattern3, s3) << std::endl; 

  return 0;
}