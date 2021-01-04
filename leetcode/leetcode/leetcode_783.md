---
title: Minimum Distance Between BST Nodes
date: 2021-01-04
---
Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of any two different nodes in the tree.

Example :

Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.

The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \    
    1   3  

while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and node 2.
Note:

The size of the BST will be between 2 and 100.
The BST is always valid, each node's value is an integer, and each node's value is different.
This question is the same as 530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/

#### Soltuions

1. ##### stack

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
    int minDiffInBST(TreeNode* root) {
        stack<TreeNode *> s;
        TreeNode * prev = nullptr;
        int res = INT_MAX;

        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            if (prev && root->val - prev->val < res)
                res= root->val - prev->val;
            prev = root;
            root = root->right;
        }

        return res;
    }
};
```