#include <iostream>
#include <unordered_map>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Функция для вычисления суммы поддерева
int calculateSubtreeSum(TreeNode* root, std::unordered_map<int, int>& freq) {
    if (root == nullptr) return 0;

    int leftSum = calculateSubtreeSum(root->left, freq);
    int rightSum = calculateSubtreeSum(root->right, freq);

    int currentSum = root->val + leftSum + rightSum;
    freq[currentSum]++;

    return currentSum;
}

// Функция для нахождения наиболее часто встречающейся суммы поддерева
std::vector<int> findFrequentTreeSum(TreeNode* root) {
    std::unordered_map<int, int> freq;
    calculateSubtreeSum(root, freq);

    int maxFreq = 0;
    for (const auto& pair : freq) {
        maxFreq = std::max(maxFreq, pair.second);
    }

    std::vector<int> result;
    for (const auto& pair : freq) {
        if (pair.second == maxFreq) {
            result.push_back(pair.first);
        }
    }

    return result;
}

int main() {
    // Пример использования
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(-3);

    std::vector<int> frequentSums = findFrequentTreeSum(root);

    std::cout << "Frequent Sums: ";
    for (int sum : frequentSums) {
        std::cout << sum << " ";
    }
    std::cout << std::endl;

    return 0;
}