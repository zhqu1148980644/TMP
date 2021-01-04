---
title: Recover Binary Search Tree
date: 2021-01-04
---
#### Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

```
Example 1:

Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2
Example 2:

Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
```

#### Follow up:

A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?



#### Solutions

- In the previous problem 98, we implemented methods to validate if the tree is BST and can find all reverse-order node pairs. ie: `prev.val > cur.cal`
- Think of how to find out these two swapped nodes if we already have the inorder traversed sequence.
- There are two situations where the swap could be happen if you looked carefully on examples supplied in the problem.
    - Two swapped nodes are `not adjacent` to each other, then there will only be `one` reverse-ordered node pair in sequence of inorder traversal(it's supposed to be in ascending order). Find this node pair then swap could bring the sequence in ascending order again.
    - If two swapped nodes are `adjacent` to each other, then there will be `two` reverse-ordered node pairs. swap the first node of the first node pair with the second node of the second node piar would recover the tree;


1. ##### inorder traversal

recursion

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
    long prev = LONG_MIN;
    int rnum = 0;
    TreeNode * prevnode = NULL;
    TreeNode * first = NULL;
    TreeNode * second = NULL;

    void inorder(TreeNode * root) {
        if (root->left) inorder(root->left);
        if (rnum < 2 && !(prev < root->val)) {
            if (!first) first = prevnode;
            second = root; rnum++;
        }
        prev = root->val; prevnode = root;
        if (root->right) inorder(root->right);
    }

public:
    void recoverTree(TreeNode* root) {
        if (!root) return;
        inorder(root);
        swap(this->first->val, this->second->val);
    }
};
```

stack

```cpp
class Solution {
public:
    void recoverTree(TreeNode* root) {
        stack<TreeNode *> s;
        long prev = LONG_MIN;
        int rnum = 0;
        TreeNode * prevnode, * first, * second;
        first = second = prevnode = nullptr;

        while (root || !s.empty()) {
            if (root) {
                s.push(root);
                root = root->left;
            }
            else {
                root = s.top(); s.pop();
                if (root->val <= prev) {
                    if (rnum++ < 1) {
                        first = prevnode;
                        second = root;
                    }
                    else {
                        second = root;
                        break;
                    }
                }
                prevnode = root; prev = root->val;
                root = root->right;
            }
        }

        swap(first->val, second->val);
    }
};
```

morris

```cpp
class Solution {
public:
    void recoverTree(TreeNode* root) {
        long prev = LONG_MIN, rnum = 0;
        // first represents the first node of the first reverse-order pair.
        // second represent the second node of the last reverse-order pair.
        TreeNode * prevnode = NULL, * first = NULL, * second = NULL;
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
            if (rnum < 2 &&!(prev < root->val)) {
                if (!first) first = prevnode;
                second = root; rnum++;
            }
            prev = root->val; prevnode = root;
            root = root->right;
        }
        swap(first->val, second->val);
    }
};
```