---
title: Cousins in Binary Tree
date: 2021-01-04
---
In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are cousins.

 

Example 1:


Input: root = [1,2,3,4], x = 4, y = 3
Output: false
Example 2:


Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
Example 3:



Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
 

Constraints:

The number of nodes in the tree will be between 2 and 100.
Each node has a unique integer value from 1 to 100.

#### Solutions

1. ##### dfs

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode * f1 = nullptr, * f2 = nullptr;
    int l1 = INT_MIN, l2 = INT_MAX;
    void dfs(TreeNode * root, TreeNode * parent, int k, int x, int y) {
        if (!root || (f1 && f2)) return;
        if (root->val == x) {
            f1 = parent; l1 = k;
        }
        else if (root->val == y) {
            f2 = parent; l2 = k;
        }
        else {
            dfs(root->left, root, k + 1, x, y);
            dfs(root->right, root, k + 1, x, y);
        }
    }
    bool isCousins(TreeNode* root, int x, int y) {
        dfs(root, 0, 0, x, y);
        return f1 != f2 && l1 == l2;
    }
};
```

2. ##### bfs

```cpp
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        queue<TreeNode *> q;
        if (root) q.push(root);

        TreeNode * f1 = nullptr, * f2 = nullptr;
        while (q.size()) {
            int size = q.size();
            while (size--) {
                root = q.front(); q.pop();
                for (auto c : {root->left, root->right}) {
                    if (!c) continue;
                    if (c->val == x) f1 = root;
                    if (c->val == y) f2 = root;
                    q.push(c);
                }
            }            
            if (f1 || f2)
                return f1 && f2 && f1 != f2;
        }
        return false;
    }
};
```