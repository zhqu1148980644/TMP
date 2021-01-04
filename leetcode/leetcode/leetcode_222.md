---
title: Count Complete Tree Nodes
date: 2021-01-04
---
#### Given a complete binary tree, count the number of nodes.

#### Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

```
Example:

Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
```

#### Solutions

1. ##### recursion

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
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
```

2. ##### recursion with complete binary tree

- For a full binary tree, the total number of nodes is `2**h - 1`.  (root has height 1).
- As a complete binary tree fills nodes in the left most of the last level, all levels before the last level is full.
    - If the height of the left subtree equals the height of the right subtree. The left subtree is full, we can quickly get the total number of nodes in the left subtree.
    - Else the right subtree is full.

```cpp
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        int left = countHeight(root->left);
        int right = countHeight(root->right);

        if (left == right)
            // 2 ** h  - 1  + root(1) + nodes of right tree
            return (1 << left) + countNodes(root->right); 
        else
            // nodes of left tree + root(1) + 2 ** h - 1
            return countNodes(root->left) + (1 << right);
    }

    int countHeight(TreeNode * root) {
        int h = 0;
        while (root) {
            h++;
            root = root->left;
        }
        return h;
    }
};
```


3. ##### search for the last element


- Use binary search to search for the index of the last element in the last level.

```cpp
class Solution {
public:
    int height(TreeNode * root) {
        int h = 0;
        while (root) {
            h++;
            root = root->left;
        }
        return h;
    }
    bool exists(TreeNode * root, int target, int h) {
        int lo = 0, hi = pow(2, h - 1);
        for (int i = 1; i < h; i++) {
            int mid = lo + ((hi - lo) / 2);
            if (target < mid) {
                root = root->left;
                hi = mid;
            }
            else {
                lo = mid + 1;
                root = root->right;
            }
            if (!root) break;
        }
        return root;
    }
    int countNodes(TreeNode* root) {
        int h = height(root);
        if (h <= 1) return pow(2, h) - 1;
        int lo = 0, hi = pow(2, h - 1);
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            bool e = exists(root, mid, h);
            if (e)
                lo = mid + 1;
            else
                hi = mid;
        }

        return pow(2, h - 1) -1 + lo;
    }
};
```