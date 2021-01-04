---
title: Binary Tree Upside Down
date: 2021-01-04
---
Given the root of a binary tree, turn the tree upside down and return the new root.

You can turn a binary tree upside down with the following steps:

The original left child becomes the new root.
The original root becomes the new right child.
The original right child becomes the new left child.


The mentioned steps are done level by level, it is guaranteed that every node in the given tree has either 0 or 2 children.

 

Example 1:


Input: root = [1,2,3,4,5]
Output: [4,5,2,null,null,3,1]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
 

Constraints:

The number of nodes in the tree will be in the range [0, 10].
1 <= Node.val <= 10
Every node has either 0 or 2 children.


#### Solutions

1. ##### inordere traversal by recursion

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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (!root || !root->left) return root;
        auto [_, l, r] = *root;
        auto head = upsideDownBinaryTree(l);
        root->left = root->right = nullptr;
        l->left = r;
        l->right = root;
        upsideDownBinaryTree(r);
        return head;
    }
};
```

or

```cpp
class Solution {
public:
    TreeNode * head = nullptr;
    void inorder(TreeNode * root) {
        if (!root) return;
        auto [_, l, r] = *root;
        inorder(l);
        if (l) {
            l->left = r;
            l->right = root;
        }
        if (!head) head = root;
        root->left = root->right = nullptr;
        inorder(r);
    }

    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        inorder(root);
        return head;
    }
};
```

2. ##### inorder traversal with stack

```cpp
class Solution {
public:

    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        stack<TreeNode *> s;
        TreeNode * head = nullptr;

        while (root || s.size()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            if (root->left) {
                root->left->left = root->right;
                root->left->right = root;
            }
            if (!head) head = root;
            TreeNode * r = root->right;
            root->left = root->right = nullptr;
            root = r;
        }

        return head;
    }
};
```

3. ##### iteration

- Check in leetcode-cn

```cpp

```