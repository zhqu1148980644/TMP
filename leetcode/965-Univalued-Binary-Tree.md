A binary tree is univalued if every node in the tree has the same value.

Return true if and only if the given tree is univalued.

 

Example 1:


Input: [1,1,1,1,1,null,1]
Output: true
Example 2:


Input: [2,2,2,5,2]
Output: false
 

Note:

The number of nodes in the given tree will be in the range [1, 100].
Each node's value will be an integer in the range [0, 99].

#### Solutions

1. ##### straight forward

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
    int val = -1;
    bool isUnivalTree(TreeNode* root) {
        if (!root) return true;
        if (val == -1) val = root->val;
        else if (root->val != val) return false;
        return isUnivalTree(root->left) && isUnivalTree(root->right);
    }
};
```

or

```c++
class Solution {
public:
    bool isUnivalTree(TreeNode* root) {
        if (!root || (!root->left) && !root->right) return true;
        if (root->left && root->right)
            return root->val == root->left->val 
                && root->val == root->right->val
                && isUnivalTree(root->left)
                && isUnivalTree(root->right);
        else if (root->left)
            return root->left->val == root->val && isUnivalTree(root->left);
        else
            return root->right->val == root->val && isUnivalTree(root->right);
    }
};
```