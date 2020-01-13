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

```c++
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

2. ##### complete binary tree

- For a full binary tree, the total number of nodes is `2**h - 1`.  (root has height 1).
- As a complete binary tree fills nodes in the left most of the last level, all levels before the last level is full.
    - If the height of the left subtree equals the height of the right subtree. The left subtree is full, we can quickly get the total number of nodes in the left subtree.
    - Else the right subtree is full.

```c++
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