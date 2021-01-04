---
title: Path Sum II
date: 2021-01-04
---
#### Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.

```
Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
Return:

[
   [5,4,11,2],
   [5,8,4,5]
]
```


#### Solutions

- The same as previous problem except we need to record all path with the given sum.

1. ##### backtrack

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
private:
    vector<vector<int>> res;
    vector<int> path;

    void dfs(TreeNode * root, int sum) {
        path.push_back(root->val);
        if (!root->left && !root->right) {
            if (root->val == sum)
                res.push_back(path);
        } else {
            if (root->left)
                dfs(root->left, sum - root->val);
            if (root->right)
                dfs(root->right, sum - root->val);
        }
        path.pop_back();
    }

public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (root) dfs(root, sum);
        return res;
    }
};
```


2. ##### iteration with stack

- preorder or postder?
- The same as the method used in previous problem.

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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        // No need to make new path vector for recording nodes
        // s itself is composed by all nodes of the current path
        TreeNode * prev = NULL;
        vector<TreeNode *> s;
        vector<vector<int>> res;

        int total;
        while (root || !s.empty()) {
            while (root) {
                total += root->val;
                s.push_back(root);
                root = root->left;
            }
            root = s.back();
            // check if we are at the leaf node.
            if (!root->left && !root->right && total == sum) {
                vector<int> path;
                for (auto & pnode : s)
                    path.push_back(pnode->val);
                res.push_back(path);
            }
            // if we need to  visit the right.
            // root->right == prev means we are just backtracked from the right child.
            if (root->right && root->right != prev) {
                root = root->right;
            } else {
                prev = root; s.pop_back();
                total -= root->val;
                root = NULL;
            }
        }
        return res;
    }
};
```