---
title: Two Sum IV Input is a BST
date: 2021-01-04
---
Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:

Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
 

Example 2:

Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False

#### Solutions

1. ##### hashset

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
    unordered_set<int> sum;
    bool search(TreeNode * root, int target) {
        if (!root) return false;
        if (root->left && search(root->left, target))
            return true;
        if (sum.count(target - root->val))
            return true;
        sum.insert(root->val);
        if (root->right && search(root->right, target))
            return true;
        return false;
    }
    bool findTarget(TreeNode* root, int k) {
        return search(root, k);
    }
};
```


2. ##### two pointers

```cpp
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> v;
        function<void(TreeNode *)> inorder = [&](TreeNode * root) {
            if (!root) return;
            inorder(root->left);
            v.push_back(root->val);
            inorder(root->right);
        };
        inorder(root);
        int i = 0, j = v.size() - 1;
        while (i < j) {
            int sum = v[i] + v[j];
            if (sum > k)
                j--;
            else if (sum < k)
                i++;
            else
                return true;
        }
        return false;
    }
};
```

3. ##### successor and precursor

```cpp
class Solution {
public:
    TreeNode * successor(TreeNode * root, stack<TreeNode *> & s) {
        if (root->right) {
            s.push(root);
            root = root->right;
            while (root->left) {
                s.push(root);
                root = root->left;
            }
        }
        else {
            while (s.top()->right == root) {
                root = s.top(); s.pop();
            }
            root = s.top(); s.pop();
        }
        return root;
    }
    TreeNode * precursor(TreeNode * root, stack<TreeNode *> & s) {
        if (root->left) {
            s.push(root);
            root = root->left;
            while (root->right) {
                s.push(root);
                root = root->right;
            }
        }
        else {
            while (s.top()->left == root) {
                root = s.top(); s.pop();
            }
            root = s.top(); s.pop();
        }
        return root;
    }
    bool findTarget(TreeNode* root, int k) {
        stack<TreeNode *> ls, rs;
        TreeNode * l = root, * r = root;
        while (l->left) {
            ls.push(l); l = l->left;
        }
        while (r->right) {
            rs.push(r); r = r->right;
        }
        
        while (l != r) {
            int sum = l->val + r->val;
            if (sum < k)
                l = successor(l, ls);
            else if (sum > k)
                r = precursor(r, rs);
            else
                return true;
        }
        return false;
    }
};
```