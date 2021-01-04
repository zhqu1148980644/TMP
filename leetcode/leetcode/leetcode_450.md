---
title: Delete Node in a BST
date: 2021-01-04
---
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).

Example:

root = [5,3,6,2,4,null,7]
key = 3

    5
   / \
  3   6
 / \   \
2   4   7

Given key to delete is 3. So we find the node with value 3 and delete it.

One valid answer is [5,4,6,2,null,null,7], shown in the following BST.

    5
   / \
  4   6
 /     \
2       7

Another valid answer is [5,2,6,null,4,null,7].

    5
   / \
  2   6
   \   \
    4   7


#### Solutions

1. ##### recursion

- Ensure the property of binary search tree not be corrupted.

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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        else if (root->val < key)
            root->right = deleteNode(root->right, key);
        else if (root->val > key)
            root->left = deleteNode(root->left, key);
        else {
            if (!root->left && !root->right)
                return nullptr;
            else if (root->right) {
                TreeNode * succ = root->right;
                while (succ->left)
                    succ = succ->left;
                root->val = succ->val;
                root->right = deleteNode(root->right, root->val);   
            }
            else {
                TreeNode * pres = root->left;
                while (pres->right)
                    pres = pres->right;
                root->val = pres->val;
                root->left = deleteNode(root->left, root->val);
            }
        }
        return root;
    }
};
```


or

```cpp
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        else if (root->val < key)
            root->right = deleteNode(root->right, key);
        else if (root->val > key)
            root->left = deleteNode(root->left, key);
        else {
            if (!root->left && !root->right)
                return nullptr;
            else if (root->right) {
                TreeNode * ldeep = root->right;
                TreeNode * prev = nullptr;
                while (ldeep->left) {
                    prev = ldeep;
                    ldeep = ldeep->left;
                }
                // the successor may have right children, do not abandon it
                if (prev) prev->left = ldeep->right;
                if (ldeep != root->right)
                    ldeep->right = root->right;
                ldeep->left = root->left;
                root = ldeep;
            }
            else {
                TreeNode * rdeep = root->left;
                TreeNode * prev = nullptr;
                while (rdeep->right) {
                    prev = rdeep;
                    rdeep = rdeep->right;
                }
                // the precursor may have left children, do not abandon it
                if (prev) prev->right = rdeep->left;
                if (rdeep != root->left)
                    rdeep->left = root->left;
                root = rdeep;
            }
        }
        return root;
    }
};
```