---
title: Count Univalue Subtrees
date: 2021-01-04
---
Given a binary tree, count the number of uni-value subtrees.

A Uni-value subtree means all nodes of the subtree have the same value.

Example :

Input:  root = [5,1,5,5,5,null,5]

              5
             / \
            1   5
           / \   \
          5   5   5

Output: 4

#### Solutions

1. ##### postorder traversal with recursion

```cpp
class Solution {
public:
    int res = 0;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        if ((!root->left || l == root->val) && (!root->right || r == root->val)) {
            res++; return root->val;
        }
        return INT_MIN;
    }
    int countUnivalSubtrees(TreeNode* root) {
        if (root) dfs(root);
        return res;
    }
};
```

2. ##### postorder with stack

```cpp
class Solution {
public:
    int countUnivalSubtrees(TreeNode* root) {
        stack<TreeNode *> s;
        stack<int> lefts; int right;
        TreeNode * prev = nullptr;
        int res = 0;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != prev)
                root = root->right;
            else {
                int cur = INT_MIN;
                if ((!root->left || lefts.top() == root->val) 
                && (!root->right || right == root->val)) {
                    cur = root->val; res++;
                }
                if (root->left) lefts.pop();
                // must pop before check if left child
                s.pop();
                if (!s.empty() && s.top()->left == root)
                    lefts.push(cur);
                else
                    right = cur;
                prev = root;
                root = nullptr;
            }
        }
        return res;
    }
};
```