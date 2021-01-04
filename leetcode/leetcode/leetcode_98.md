---
title: Validate Binary Search Tree
date: 2021-01-04
---
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

#### The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

```
Example 1:

    2
   / \
  1   3

Input: [2,1,3]
Output: true
Example 2:

    5
   / \
  1   4
     / \
    3   6

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
```


#### Solutions

1. ##### (preorder)check lower bound and upper bound for each node

- Maintain a lowerbound and upper bound when traversing each item. 

Recursion

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
    bool isvalid(TreeNode * root, long lower, long upper) {
        if (!root) return true;
        return (root->val > lower && root->val < upper) 
                && isvalid(root->left, lower, root->val) 
                && isvalid(root->right, root->val, upper);
    }
public:
    bool isValidBST(TreeNode* root) {
        long lower = LONG_MIN, upper = LONG_MAX;
        return isvalid(root, lower, upper);
    }
};
```

Or a dfs stack version(preorder).

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode *> s;
        stack<pair<long, long>> bounds;
        if (root) s.push(root);
        bounds.push({LONG_MIN, LONG_MAX});

        while (!s.empty()) {
            root = s.top(); s.pop();
            auto b = bounds.top(); bounds.pop();
            if (root->val <= b.first || root->val >= b.second)
                return false;
            if (root->right) {
                s.push(root->right);
                bounds.push({root->val, b.second});
            }
            if (root->left) {
                s.push(root->left);
                bounds.push({b.first,root->val});
            }
        }

        return true;
    }
};
```

2. ##### Sequence of inorder traversal is in ascending order

Recursion

```cpp
class Solution {
private:
    long prev = LONG_MIN;
    bool isvalid(TreeNode * root) {
        bool leftvalid = root->left ? isvalid(root->left) : true;
        bool curvalid = root->val > prev; prev = root->val;
        bool rightvalid = root->right ? isvalid(root->right) : true;
        return curvalid && leftvalid && rightvalid;
    }

public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        return isvalid(root);
    }
};
```

Stack

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long prev = LONG_MIN;
        stack<TreeNode *> s;

        while (root || !s.empty()) {
            if (root) {
                s.push(root);
                root = root->left;
            } else {
                root = s.top(); s.pop();
                if (!(prev < root->val)) return false;
                prev = root->val;
                root = root->right;
            }
        }
        return true;
    }
};
```


Morris

It seems like there is no way to pre-exit when finding an item breaks the bst rule, because there may be leaf node whose right child has not been set to NULL.

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long prev = LONG_MIN;
        bool valid = true;
        while (root) {
            if (root->left) {
                TreeNode * rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right != root) {
                    rdeep->right = root;
                    root = root->left;
                    continue;
                } else
                    rdeep->right = NULL;
            }
            if (valid && !(prev < root->val))
                valid = false;
            prev = root->val;
            root = root->right;
        }
        return valid;
    }
};
```