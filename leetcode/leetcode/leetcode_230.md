---
title: Kth Smallest Element in a BST
date: 2021-01-04
---
#### Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

```
Example 1:

Input: root = [3,1,4,null,2], k = 1
   3
  / \
 1   4
  \
   2
Output: 1

Example 2:

Input: root = [5,3,6,2,4,null,null,1], k = 3
       5
      / \
     3   6
    / \
   2   4
  /
 1
Output: 3
```

#### Follow up:
- What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

#### Solutions

- Any inorder traversal method would works well.

1. ##### inorder traversal with dfs

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
    int res, cur = 1;
    void inorder(TreeNode * root, int k) {
        if (!root) return;
        inorder(root->left, k);
        if (cur > k) return;
        if (cur == k)
            res = root->val;
        cur++;
        inorder(root->right, k);


    }
    int kthSmallest(TreeNode* root, int k) {
        inorder(root, k);
        return res;
    }
};
```

fancy python version.

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def kthSmallest(self, root: TreeNode, k: int) -> int:
        def inorder(root):
            if not root: return
            yield from inorder(root.left)
            yield root.val
            yield from inorder(root.right)
        gen = inorder(root)
        for i in range(k - 1):
            next(gen)
        return next(gen)
```

2. ##### iterative version with stack

```cpp
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode *> s;
        int count = 0;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            count++;
            root = s.top(); s.pop();
            if (count == k) return root->val;
            root = root->right;
        }
        return 0;
    }
};
```

3. ##### iteration with morris

- Codes below doesn't pre-exit like former solutions because there may be right children of leaf nodes point to ancestor nodes which could deconstruct the binary tree.

```cpp
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int count = 0, res;
        TreeNode * rdeep;

        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right != root) {
                    rdeep->right = root;
                    root = root->left;
                    continue;
                } else {
                    rdeep->right = nullptr;
                }
            }
            count++;
            if (count == k) res = root->val;
            root = root->right;
        }
        return res;
    }
};
```