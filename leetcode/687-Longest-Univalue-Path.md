Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

The length of path between two nodes is represented by the number of edges between them.

 

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output: 2

 

Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output: 2

 

Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.

#### Solutions

1. ##### postorder recursion


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
    int res = 0;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        int l = dfs(root->left);
        int r =  dfs(root->right);
        if (root->left && root->left->val != root->val)
            l = 0;
        if (root->right && root->right->val != root->val)
            r = 0;
        res = max(res, l + r + 1);
        return max(l + 1, r + 1);
    }
    int longestUnivaluePath(TreeNode* root) {
        if (root) dfs(root);
        return max(res - 1, 0);
    }
};
```