---
title: Binary Tree Inorder Traversal
date: 2021-01-04
---
#### Given a binary tree, return the inorder traversal of its nodes' values.

```
Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
```

####  Follow up: 

Recursive solution is trivial, could you do it iteratively?


#### Solutions

1. ##### recursion O(n) S(log(n))

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
private:
    vector<int> res;
public:
    void inorder(TreeNode * root) {
        if (root->left)
            inorder(root->left);
        res.push_back(root->val);
        if (root->right)
            inorder(root->right);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        if (root) inorder(root);
        return res;
    }
};
```

2. ##### Iteration with stack O(n) S(log(n))

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode * root) {
        vector<int> res;
        stack<TreeNode *> s;
        while (true) {
            if (root) {
                s.push(root);
                root = root->left;
            } else if (!s.empty()) {
                root = s.top(); s.pop();
                res.push_back(root->val);
                root = root->right;
            } else
                break;
        }
        return res;
    }
};
```

OR

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode * root) {
        vector<int> res;
        stack<TreeNode *> s;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};
```

OR

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode *> s;
        while (root || !s.empty()) {
            if (root) {
                s.push(root);
                root = root->left;
            } else {
                root = s.top(); s.pop();
                res.push_back(root->val);
                root = root->right;
            }
        }
        return res;
    }
};
```

3. ##### Morris traversal O(n) S(1)

- The key is how to go back to the root node when we reach the rightmost leaf node and how to determine if the left child tree has been visited.
- When the current node is `cur`
    - if `cur->left` and the `right child` of the rightmost leaf node or `precursor` is `NULL`
        - set precursor's right child to `cur`
        - visit left child
    - otherwise, neither `cur` doesn't contain left child or the left child tree has been visited, go visit `cur`'s right child.
        - When we are at the rightmost leaf node of a tree, the left child is `NULL` thus we will(set by rule one) go visit the right child which is the current tree's parent node.


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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode * rleaf;
        // In each while loop, we will visit a new node.
        while (root) {
            // no left, go right
            if (!root->left) {
                res.push_back(root->val);
                root = root->right;
            } else {
                rleaf = root->left;
                // find root node's precursor
                while (rleaf->right && rleaf->right != root)
                    rleaf = rleaf->right;
                // When the right child of precursor is root, left tree has been visited, reset          and go visit right.
                if (rleaf->right == root) {
                    rleaf->right = NULL;
                    res.push_back(root->val);
                    root = root->right;
                // set the right child to root, go visit left
                } else {
                    rleaf->right = root;
                    root = root->left;
                }
            }
        }
        return res;
    }
};
```