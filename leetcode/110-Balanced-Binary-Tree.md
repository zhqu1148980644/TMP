#### Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

 

```
Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.
```

#### Solutions

1. ##### recursion

- Calculating the height of subtrees and checking if two subtrees are balanced at the same time.
- Use `-1` as indication of unbalanced tree.

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
    int  depth(TreeNode * root) {
        if (!root) return 0;
        int lh = depth(root->left);
        int rh = depth(root->right);
        if (lh == -1 || rh == -1)
            return -1;
        else if (abs(lh - rh) > 1)
            return -1;
        else
            return max(lh, rh) + 1;
    }
    bool isBalanced(TreeNode* root) {
        return depth(root) != -1;
    }
};
```