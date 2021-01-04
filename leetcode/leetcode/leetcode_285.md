---
title: Inorder Successor in BST
date: 2021-01-04
---
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

The successor of a node p is the node with the smallest key greater than p.val.

 

Example 1:


Input: root = [2,1,3], p = 1
Output: 2
Explanation: 1's in-order successor node is 2. Note that both p and the return value is of TreeNode type.
Example 2:


Input: root = [5,3,6,2,4,null,null,1], p = 6
Output: null
Explanation: There is no in-order successor of the current node, so the answer is null.
 

Note:

If the given node has no in-order successor in the tree, return null.
It's guaranteed that the values of the tree are unique.


#### Solutions


1. ##### inorder traversal O(n)

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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (p->right) {
            root = p->right;
            while (root->left)
                root = root->left;
            return root;
        }
        stack<TreeNode *> s;
        TreeNode * prev = nullptr;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            if (prev == p) return root;
            prev = root;
            root = root->right;
        }

        return nullptr;
    }
};
```

2. ##### binary search then find successor O(log(n))

- Use binary search to find the target node and record the visited path while searching.
- Then there are two cases
    - if the target node has right child, then the successor is the leftmost child of the right child subtree.
    - else, find the first faster whose left child is the previous node within the desendant path.

```cpp
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        stack<TreeNode *> s;
        while (root != p) {
            s.push(root);
            if (root->val < p->val)
                root = root->right;
            else
                root = root->left;
        }
        s.push(p);
        root = s.top();
        if (root->right) {
            root = root->right;
            while (root->left)
                root = root->left;
            return root;
        }
        else {
            s.pop();
            while (!s.empty() && s.top()->right == root) {
                root = s.top(); s.pop();
            }
            return s.empty() ? nullptr : s.top();
        }
        
    }
};
```

Or

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
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (p->right) {
            root = p->right;
            while (root->left)
                root = root->left;
            return root;
        }
        stack<TreeNode *> s;
        while (root != p) {
            s.push(root);
            if (root->val < p->val)
                root = root->right;
            else
                root = root->left;
        }
        root = p;
        while (!s.empty() && s.top()->right == root) {
            root = s.top(); s.pop();
        }
        return s.empty() ? nullptr : s.top();
        
    }
};
```

3. ##### binary search

- reference: https://leetcode-cn.com/problems/inorder-successor-in-bst/solution/simple-c-solution-by-yanjiechen-2/

```cpp
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode * res = nullptr;
        while (root) {
            if (p->val < root->val) {
                res = root;
                root = root->left;
            }
            else
                root = root->right;
        }
        return res;
    }
};
```