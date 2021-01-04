---
title: Search in a Binary Search Tree
date: 2021-01-04
---
Given the root node of a binary search tree (BST) and a value. You need to find the node in the BST that the node's value equals the given value. Return the subtree rooted with that node. If such node doesn't exist, you should return NULL.

For example, 

Given the tree:
        4
       / \
      2   7
     / \
    1   3

And the value to search: 2
You should return this subtree:

      2     
     / \   
    1   3
In the example above, if we want to search the value 5, since there is no node with value 5, we should return NULL.

Note that an empty tree is represented by NULL, therefore you would see the expected output (serialized tree format) as [], not null.

#### Solutions

1. ##### straight forward

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
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root) {
            if (val < root->val)
                root = root->left;
            else if (root->val < val)
                root = root->right;
            else
                return root;
        }

        return root;
    }
};
```

or

```cpp
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        return !root || root->val == val ? root 
                : (root->val < val ? searchBST(root->right, val) 
                    : searchBST(root->left, val));
    }
};
```