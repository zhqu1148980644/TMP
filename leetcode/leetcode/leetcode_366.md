---
title: Find Leaves of Binary Tree
date: 2021-01-04
---
Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.

 

Example:

Input: [1,2,3,4,5]
  
          1
         / \
        2   3
       / \     
      4   5    

Output: [[4,5,3],[2],[1]]
 

Explanation:

1. Removing the leaves [4,5,3] would result in this tree:

          1
         / 
        2          
 

2. Now removing the leaf [2] would result in this tree:

          1          
 

3. Now removing the leaf [1] would result in the empty tree:

          []         


#### Solutions

- Collect nodes with the same height(from leaf to the current node).

1. ##### postorder traversal with recursion

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
    vector<vector<int>> res;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        int h = max(dfs(root->left), dfs(root->right)) + 1;
        if (h > res.size()) res.resize(h);
        res[h - 1].push_back(root->val);
        return h;
    }
    vector<vector<int>> findLeaves(TreeNode* root) {
        dfs(root);
        return res;
    }
};
```

2. ##### iteration