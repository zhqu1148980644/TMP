---
title: Sum Root to Leaf Numbers
date: 2021-01-04
---
#### Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

##### Note: 
A leaf is a node with no children.

```
Example:

Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
Example 2:

Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
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
    int res = 0;
    void preorder(TreeNode * root, int cur) {
        if (!root) return;
        cur = cur * 10 + root->val;
        if (!root->left && !root->right)
            res += cur;
        else {
            preorder(root->left, cur);
            preorder(root->right, cur);
        }
    }
    int sumNumbers(TreeNode* root) {
        preorder(root, 0);
        return res;
    }
};
```

Or without global variable.

```cpp
class Solution {
public:
    int preorder(TreeNode * root, int cur) {
        if (!root) return 0;
        cur = cur * 10 + root->val;
        if (!root->left && !root->right)
            return cur;
        else
            return preorder(root->left, cur)
                + preorder(root->right, cur);
    }
    int sumNumbers(TreeNode* root) {
        return preorder(root, 0);
    }
};
```

2. ##### iteration with stack

- Other traversal orders could also work.

```cpp
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        stack<TreeNode *> s;
        int res = 0, cur = 0;
        TreeNode * prev = nullptr;
        
        while (root || !s.empty()) {
            while (root) {
                s.push(root); cur = cur * 10 + root->val;
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != prev)
                root = root->right;
            else {
                s.pop();
                if (!root->left && !root->right)
                    res += cur;
                cur = (cur - root->val) / 10;
                prev = root;
                root = nullptr;
            }
        }
        return res;
    }
};
```