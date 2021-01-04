---
title: Maximum Average Subtree
date: 2021-01-04
---
Given the root of a binary tree, find the maximum average value of any subtree of that tree.

(A subtree of a tree is any node of that tree plus all its descendants. The average value of a tree is the sum of its values, divided by the number of nodes.)

 

Example 1:



Input: [5,6,1]
Output: 6.00000
Explanation: 
For the node with value = 5 we have an average of (5 + 6 + 1) / 3 = 4.
For the node with value = 6 we have an average of 6 / 1 = 6.
For the node with value = 1 we have an average of 1 / 1 = 1.
So the answer is 6 which is the maximum.
 

Note:

The number of nodes in the tree is between 1 and 5000.
Each node will have a value between 0 and 100000.
Answers will be accepted as correct if they are within 10^-5 of the correct answer.

#### Solutions

1. ##### dfs

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
    double maxavg = 0;
    pair<double, int> dfs(TreeNode * root) {
        if (!root) return {0, 0};
        auto [lsum, lsize] = dfs(root->left);
        auto [rsum, rsize] = dfs(root->right);
        lsum += root->val + rsum; lsize += 1 + rsize;
        maxavg = max(maxavg, lsum / lsize);
        return {lsum, lsize};
    }
    double maximumAverageSubtree(TreeNode* root) {
        dfs(root);
        return maxavg;
    }
};
```