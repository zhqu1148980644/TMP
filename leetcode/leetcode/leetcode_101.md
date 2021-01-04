---
title: Symmetric Tree
date: 2021-01-04
---
#### Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

```
For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
 

But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3
```
 

#### Note:
Bonus points if you could solve it both recursively and iteratively.


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
    bool issym(TreeNode * left, TreeNode * right) {
        if (!left && !right)
            return true;
        else if (!left || !right)
            return false;
        else
            return (left->val == right->val) 
                && issym(left->left, right->right)
                && issym(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) {
        return root ? issym(root->left, root->right) : true;
    }
};
```

2. ##### dfs with stack

- Make sure the visiting order of left child and right child is opposit in two child trees.
- For example, traversal orders of left child tree and right child tree are:
    - left root right
    - right root left

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        stack<TreeNode *> lefts;
        stack<TreeNode *> rights;
        TreeNode * left = root->left;
        TreeNode * right = root->right;
        while (left || right || !lefts.empty() || !rights.empty()) {
            while (left) {
                lefts.push(left);
                left = left->left;
            }
            while (right) {
                rights.push(right);
                right = right->right;
            }
            if (lefts.size() != rights.size()) return false;
            left = lefts.top(); lefts.pop();
            right = rights.top(); rights.pop();
            if (left->val != right->val) return false;
            left = left->right;
            right = right->left;
        }
        return true;
    }
};
```

3. ##### bfs with queue

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode *> lq; lq.push(root->left);
        queue<TreeNode *> rq; rq.push(root->right);

        while (!lq.empty() && !rq.empty()) {
            TreeNode * l = lq.front(); lq.pop();
            TreeNode * r = rq.front(); rq.pop();
            if (l && r) {
                if (l->val != r->val)
                    return false;
                lq.push(l->left); lq.push(l->right);
                rq.push(r->right); rq.push(r->left);
            }
            else if (l || r)
                return false;
        }

        return lq.empty() && rq.empty();
    }
};
```

Or

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode *> q;
        q.push(root->left); q.push(root->right);

        while (!q.empty()) {
            TreeNode * l = q.front(); q.pop();
            TreeNode * r = q.front(); q.pop();
            if (l && r) {
                if (l->val != r->val)
                    return false;
                q.push(l->left); q.push(r->right);
                q.push(l->right); q.push(r->left);
            }
            else if (l || r)
                return false;

        }

        return true;

    }
};
```