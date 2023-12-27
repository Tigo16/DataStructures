#include <iostream>
#include <vector>
#include <map>

bool Duplicate(const std::vector<int>& nums, int k) {
  std::map<int, int> numIndex;

  for (int i = 0; i < nums.size(); i++) {
    int num = nums[i];
    if (numIndex.count(num) > 0) {
      int prevIndex = numIndex[num];
      if (i - prevIndex <= k) {
        return true;
      }
    }
    numIndex[num] = i;
  }
  return false;
}

int main() {
  std::vector<int> nums1 = {1, 2, 3, 1};
  int k1 = 3;
  std::cout << std::boolalpha << Duplicate(nums1, k1) << std::endl;

  std::vector<int> nums2 = {1, 0, 1, 1};
  int k2 = 1;
  std::cout << std::boolalpha << Duplicate(nums2, k2) << std::endl;

  std::vector<int> nums3 = {1, 2, 3, 1, 2, 3};
  int k3 = 2;
  std::cout << std::boolalpha << Duplicate(nums3, k3) << std::endl;

  return 0;
}