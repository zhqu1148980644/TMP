#### Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

```
Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
```
 

#### Note: There are at least two nodes in this BST.


#### Solutions

1. ##### inorder traversal with recursion

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
    void miniDiff(TreeNode * root, int & diff, int & prev) {
        if (!root) return;
        miniDiff(root->left, diff, prev);
        if (prev >= 0 && root->val - prev < diff)
            diff = root->val - prev;
        prev = root->val;
        miniDiff(root->right, diff, prev);
    }

    int getMinimumDifference(TreeNode* root) {
        int diff = INT_MAX;
        int prev = -1;
        miniDiff(root, diff, prev);
        return diff;
    }
};
```

##### other inorder traversal methods

- Use morris traversal as example

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
    int getMinimumDifference(TreeNode* root) {
        TreeNode * prev = nullptr, * rdeep;
        int mindiff = INT_MAX;
        
        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right == root)
                    rdeep->right = nullptr;
                else {
                    rdeep->right = root;
                    root = root->left;
                    continue;
                }
            }
            if (prev && root->val - prev->val < mindiff)
                mindiff = root->val - prev->val;
            prev = root;
            root = root->right;
        }

        return mindiff;
    }
};
```