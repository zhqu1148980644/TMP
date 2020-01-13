#### Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

```
Example:
Given a binary tree

          1
         / \
        2   3
       / \     
      4   5    

Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
```

#### Note: The length of path between two nodes is represented by the number of edges between them. 

#### Solutions

- Note: the maximum diameter(path) will not necessarily pass the root node.

1. ##### recursion

- Use recursion to calculate depth of each node and updatet the maximum diameter in the meantime.

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
private:
    int maxd = INT_MIN;
public:
    int maxdepth(TreeNode * root) {
        if (!root) return 0;
        int l = maxdepth(root->left);
        int r = maxdepth(root->right);
        this->maxd = max(this->maxd, l + r);
        return max(l, r) + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        maxdepth(root);
        return maxd;
    }
};
```