Given a binary tree, you need to find the length of Longest Consecutive Path in Binary Tree.

Especially, this path can be either increasing or decreasing. For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path [1,2,4,3] is not valid. On the other hand, the path can be in the child-Parent-child order, where not necessarily be parent-child order.

Example 1:

Input:
        1
       / \
      2   3
Output: 2
Explanation: The longest consecutive path is [1, 2] or [2, 1].
 

Example 2:

Input:
        2
       / \
      1   3
Output: 3
Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
 

Note: All the values of tree nodes are in the range of [-1e7, 1e7].

#### Solutions

1. ##### postorder traversal with recursion

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
    pair<int, int> postorder(TreeNode * root) {
        if (!root) return {0, 0};
        auto [linc, ldec] = postorder(root->left);
        auto [rinc, rdec] = postorder(root->right);
        int lval = root->left ? root->left->val : INT_MIN;
        int rval = root->right ? root->right->val : INT_MIN;
        int inc, dec, val = root->val;
        inc = max(val + 1 == lval ? linc : 0, val + 1 == rval ? rinc : 0) + 1;
        dec = max(val - 1 == lval ? ldec : 0, val - 1 == rval ? rdec : 0) + 1;
        // if two subtree are both inc, then inc will be the largest and dec will be 1
        // if one subtree is in can another is dec, thus formula also works
        res = max(res, inc + dec - 1);
        return {inc, dec};
    }
    int longestConsecutive(TreeNode* root) {
        if (root) postorder(root);
        return res;
    }
};
```