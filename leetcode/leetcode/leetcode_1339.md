---
title: Maximum Product of Splitted Binary Tree
date: 2021-01-04
---
Given a binary tree root. Split the binary tree into two subtrees by removing 1 edge such that the product of the sums of the subtrees are maximized.

Since the answer may be too large, return it modulo 10^9 + 7.

 

```
Example 1:

Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)

Example 2:

Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation:  Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)

Example 3:

Input: root = [2,3,9,10,7,8,6,5,4,11,1]
Output: 1025

Example 4:

Input: root = [1,1]
Output: 1
```

 

#### Constraints:

-    Each tree has at most 50000 nodes and at least 2 nodes.
-    Each node's value is between [1, 10000].


#### Solutions

1. ##### postorder with recursion

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
    long res = 0;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        return root->val + dfs(root->left) + dfs(root->right);
    }
    long postorder(TreeNode * root, int sum) {
        if (!root) return 0;
        long lsum = postorder(root->left, sum);
        long rsum = postorder(root->right, sum);
        res = max(res, max(lsum * (sum - lsum), rsum * (sum - rsum)));
        return lsum + rsum + root->val;
    }
    int maxProduct(TreeNode* root) {
        int sum = dfs(root);
        postorder(root, sum);
        return res % 1000000007;
    }
};
```