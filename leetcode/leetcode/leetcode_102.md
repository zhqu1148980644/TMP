---
title: Binary Tree Level Order Traversal
date: 2021-01-04
---
#### Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

```
For example:
Given binary tree [3,9,20,null,null,15,7],
    3
/ \
9  20
    /  \
15   7
return its level order traversal as:
[
[3],
[9,20],
[15,7]
]
```

#### Solutions

1. ##### dfs with level tag

```cpp
class Solution {
private:
    vector<vector<int>> res;
public:

    void inorder(TreeNode * root, int level) {
        if (!root) return;
        if (res.size() < level + 1)
            res.push_back(vector<int>());
        res[level].push_back(root->val);
        inorder(root->left, level + 1);
        inorder(root->right, level + 1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        inorder(root, 0);
        return res;
    }
};
```


2. ##### bfs with queue

```cpp
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode *> q; if(root) q.push(root);
        vector<vector<int>> res;

        while (!q.empty()) {
            int size = q.size();
            vector<int> lres;
            while (size--) {
                root = q.front(); q.pop();
                lres.push_back(root->val);
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            res.push_back(lres);
        }

        return res;
    }
};
```


A non-queue python version

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if root is None:
            return []
        nodes = [[root]]
        while nodes[-1]:
            nodes.append([child
                        for node in nodes[-1]
                        for child in (node.left, node.right) if child]);
        res = [[node.val for node in level] for level in nodes[:-1]]

        return res
```
