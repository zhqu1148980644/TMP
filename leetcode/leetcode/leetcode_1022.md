---
title: Sum of Root To Leaf Binary Numbers
date: 2021-01-04
---
Given a binary tree, each node has value 0 or 1.  Each root-to-leaf path represents a binary number starting with the most significant bit.  For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.

For all leaves in the tree, consider the numbers represented by the path from the root to that leaf.

Return the sum of these numbers.

 

Example 1:



Input: [1,0,1,0,1,0,1]
Output: 22
Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
 

Note:

The number of nodes in the tree is between 1 and 1000.
node.val is 0 or 1.
The answer will not exceed 2^31 - 1.

#### Solutions

1. ##### dfs

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
    int dfs(TreeNode * root, int cur) {
        if (!root) return 0;
        cur = (cur << 1) | root->val;
        if (!root->left && !root->right)
            return cur;
        return dfs(root->left, cur) + dfs(root->right, cur);
    }
    int sumRootToLeaf(TreeNode* root) {
        return dfs(root, 0);
    }
};
```

2. ##### iteration

- Use inorder traversal as example, preorder is fine too.

```cpp
class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        stack<pair<TreeNode *, int>> s;
        int cur = 0, res = 0;

        while (root || s.size()) {
            while(root) {
                cur = (cur << 1) | root->val;
                s.emplace(root, cur);
                root = root->left;
            }
            root = s.top().first;
            cur = s.top().second;
            s.pop();
            if (!root->left && !root->right)
                res += cur;
            root = root->right;
        }

        return res;
    }
};
```