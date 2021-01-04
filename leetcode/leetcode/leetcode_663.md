---
title: Equal Tree Partition
date: 2021-01-04
---
Given a binary tree with n nodes, your task is to check if it's possible to partition the tree to two trees which have the equal sum of values after removing exactly one edge on the original tree.

Example 1:
Input:     
    5
   / \
  10 10
    /  \
   2   3

Output: True
Explanation: 
    5
   / 
  10
      
Sum: 15

   10
  /  \
 2    3

Sum: 15
Example 2:
Input:     
    1
   / \
  2  10
    /  \
   2   20

Output: False
Explanation: You can't split the tree into two trees with equal sum after removing exactly one edge on the tree.
Note:
The range of tree node value is in the range of [-100000, 100000].
1 <= n <= 10000

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
    int sum(TreeNode * root) {
        return !root ? 0 : sum(root->left) + sum(root->right) + root->val;
    }
    int sum(TreeNode * root, int sumval, bool & find) {
        if (!root || find) return 0;
        int ls = sum(root->left, sumval, find);
        int rs = sum(root->right, sumval, find);
        int cursum = root->val + ls + rs;
        if (sumval - cursum == cursum)
            find = true;

        return cursum;
    }
    bool checkEqualTree(TreeNode* root) {
        int sumval = sum(root);
        bool find = false;
        sum(root->left, sumval, find);
        if (find) return true;
        sum(root->right, sumval, find);
        return find;
    }
};
```