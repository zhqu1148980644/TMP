---
title: Most Frequent Subtree Su
date: 2021-01-04
---
Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

Examples 1
Input:

  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.

#### Solutions

1. ##### postorder traversal with recursion

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    unordered_map<int, int> m;
    int maxc = INT_MIN;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        int cursum = dfs(root->left) + dfs(root->right) + root->val;
        maxc = max(maxc, ++m[cursum]);
        return cursum;
    }
    vector<int> findFrequentTreeSum(TreeNode* root) {
        if (root) dfs(root);
        vector<int> res;
        for (auto & [v, c] : m)
            if (c == maxc)
                res.push_back(v);
        return res;
    }
};
```

2. ##### iteration


```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        stack<TreeNode *> s;
        TreeNode * prev;
        stack<int> lefts; int rights = 0;
        unordered_map<int, int> m;
        int maxc = INT_MIN;

        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != prev)
                root = root->right;
            else {
                int left = 0, right = 0;
                if (root->left) {
                    left = lefts.top(); lefts.pop();
                }
                if (root->right)
                    right = rights;
                int cursum = left + right + root->val;
                maxc = max(maxc, ++m[cursum]);
                s.pop();
                if (!s.empty()) {
                    if (s.top()->left && s.top()->left == root)
                        lefts.push(cursum);
                    else if (s.top()->right && s.top()->right == root)
                        rights = cursum;
                }
                prev = root;
                root = nullptr;
            }
        }
        
        vector<int> res;
        for (auto & [val, c] : m)
            if (c == maxc) res.push_back(val);

        return res;
    }
};
```