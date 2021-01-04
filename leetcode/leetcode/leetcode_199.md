---
title: Binary Tree Right Side View
date: 2021-01-04
---
#### Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

```
Example:

Input: [1,2,3,null,5,null,4]
Output: [1, 3, 4]
Explanation:

   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
```

#### Solutions

A right side view of a binary tree is the sequence composed of each level's rightmost nodes.

1. ##### bfs with queue

- Bfs traversial is level traversial.

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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        queue<TreeNode *> q;
        if (root) q.push(root);
        while (!q.empty()) {
            int size = q.size();
            TreeNode * top;
            while (size--) {
                top = q.front(); q.pop();
                if (top->left) q.push(top->left);
                if (top->right) q.push(top->right);
            }
            // The last item in a level.
            res.push_back(top->val);
        }
        return res;
    }
};
```

2. ##### preorder dfs

- dfs also works as long as we can record the level of each node when traversing.
- To make dfs work correctly and simple, we traverse starting from the right child.

```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        stack<pair<TreeNode *, int>> s;
        if(root) s.push({root, 0});
        vector<int> res;

        while (!s.empty()) {
            root = s.top().first;
            int level = s.top().second;
            s.pop();
            if (level == res.size())
                res.push_back(root->val);
            if (root->left)
                s.push({root->left, level + 1});
            if (root->right)
                s.push({root->right, level + 1});
        }
        return res;
    }
};
```

When using the recursive approach, we can pass the level info through function call.

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def rightSideView(self, root: TreeNode) -> List[int]:
        def dfs(root, level):
            if root:
                if level == len(res):
                    res.append(root.val)
                dfs(root.right, level + 1)
                dfs(root.left, level + 1)
        res = []
        dfs(root, 0)
        return res
```