---
title: Delete Nodes And Return Forest
date: 2021-01-04
---
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest.  You may return the result in any order.

 

Example 1:



Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]
 

Constraints:

The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.

#### Solutions

1. ##### dfs

- Remember to cut the links between parent and child nodes when children need to be deleted.

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
    vector<TreeNode *> res;
    unordered_set<int> dels;
    bool dfs(TreeNode * root, bool padel) {
        if (!root) return false;
        bool curdel = dels.count(root->val);
        if (padel && !curdel) res.push_back(root);
        if (dfs(root->left, curdel))
            root->left = nullptr;
        if (dfs(root->right, curdel))
            root->right = nullptr;
        return curdel;
    }
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        for (auto n : to_delete)
            dels.insert(n);
        dfs(root, true);
        return res;
    }
};
```