#include <iostream>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::set<int> nums;
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        nums.insert(num);
    }

    int count = nums.size();
    std::cout << count << std::endl;
    return 0;
}