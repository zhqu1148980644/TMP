---
title: Leaf Similar Trees
date: 2021-01-04
---
Consider all the leaves of a binary tree.  From left to right order, the values of those leaves form a leaf value sequence.



For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9, 8).

Two binary trees are considered leaf-similar if their leaf value sequence is the same.

Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.

 

Constraints:

Both of the given trees will have between 1 and 200 nodes.
Both of the given trees will have values between 0 and 200

#### Solutions

1. #### straight forward

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
    void fill(TreeNode * root, vector<int> & res) {
        if (!root) return;
        if (!root->left && !root->right)
            res.push_back(root->val);
        else {
            fill(root->left, res);
            fill(root->right, res);
        }
    }
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> v1, v2;
        fill(root1, v1), fill(root2, v2);
        return v1 == v2;
    }
};
```

2. ##### hash

- Borrowed from others.

```cpp
class Solution {
public:
    double hash(TreeNode * root, double n) {
        if (!root) return n;
        if (!root->left && !root->right)
            return n * 3 + root->val;
        else
            return hash(root->left, hash(root->right, n));
    }
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        return hash(root1, 0) == hash(root2, 0);
    }
};
```