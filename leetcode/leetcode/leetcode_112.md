---
title: Path Su
date: 2021-01-04
---
#### Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

#### Note: 
A leaf is a node with no children.

```
Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
```

#### Solutions

1. ##### recursion(dfs)

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
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right)
            return root->val == sum;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum-root->val);
    }
};
```

2. ##### iteration(postder ?) with stack

- Because the number may be negative, we can not pre-exit(prune).

```cpp
class Solution {
public:
    bool hasPathSum(TreeNode * root, int sum) {
        stack<TreeNode *> s;
        int SUM = 0;
        TreeNode *  cur = root;
        TreeNode *  pre = NULL;
        while (cur || !s.empty()) {
            // go left down.
            while (cur) {
                s.push(cur);
                SUM += cur->val;
                cur = cur->left;
            }
            cur = s.top();
            // check if we are in leaf node.
            if (!cur->left && !cur->right && SUM == sum)
                return true;
            // check if we have visited right node. visit if not.
            if (cur->right && pre != cur->right) {
                cur = cur->right;

            } else {
                pre = cur;
                s.pop();
                SUM -= cur->val;
                // back to the last node.
                cur = NULL;
            }
        }
        return false;
    }
};
```
