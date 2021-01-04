---
title: Binary Tree Cameras
date: 2021-01-04
---
Given a binary tree, we install cameras on the nodes of the tree. 

Each camera at a node can monitor its parent, itself, and its immediate children.

Calculate the minimum number of cameras needed to monitor all nodes of the tree.

 

Example 1:


Input: [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.
Example 2:


Input: [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.

Note:

The number of nodes in the given tree will be in the range [1, 1000].
Every node has value 0.

#### Solutions

1. ##### dynamic programming

- `dp0` represents all children except the root has been monitored.
- `dp1` represents all nodes has been monitored with no camera settled at the root node.
- `dp2` is the same as `dp1` except the camera settled.

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
    vector<int> dfs(TreeNode * root) {
        if (!root) return {0, 0, 0x3f3f3f3f};
        auto ls = dfs(root->left);
        auto rs = dfs(root->right);
        int dp0 = ls[1] + rs[1];
        int dp1 = min(ls[2] + rs[2], min(ls[1] + rs[2], ls[2] + rs[1]));
        int dp2 = min(ls[0], min(ls[1], ls[2])) 
                + min(rs[0], min(rs[1], rs[2])) + 1;
        return {dp0, dp1, dp2};
    }
    int minCameraCover(TreeNode* root) {
        auto cost = dfs(root);
        return min(cost[1], cost[2]);
    }
};
```

2. ##### greedy strategy

- start adding cameras from leafs to root using postorder traversal.

```cpp
class Solution {
public:
    int res = 0;
    // 0 represents not being monitored
    // 1 represents installed camera
    // 2 represents being monitored(by it's child) but with no camera.
    int dfs(TreeNode * root) {
        if (!root) return 2;
        int l = dfs(root->left);
        int r = dfs(root->right);
        if (l == 0 || r == 0) {
            res++;
            return 1;
        }
        else if (l == 1 || r == 1)
            return 2;
        else
            return 0;
    }
    int minCameraCover(TreeNode* root) {
        if (dfs(root) == 0) res++;
        return res;
    }
};
```