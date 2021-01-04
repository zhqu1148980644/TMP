---
title: Minimum Depth of Binary Tree
date: 2021-01-04
---
#### Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

#### Note: 
A leaf is a node with no children.

```
Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.
```

#### Solutions

1. ##### recursion(dfs)

```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        if (root->left && root->right)
            return 1 + min(minDepth(root->left), minDepth(root->right));
        else
            // remove redundant control flow
            return 1 + minDepth(root->left) + minDepth(root->right);

    }
};
```

2. ##### iteration(bfs) with queue

- This one will be much faster than the previous one because the loop will exit when the first time meets the lowest depth node wheras the previous will always traverse the full tree.

```cpp
class Solution {
public:
    int minDepth(TreeNode * root) {
        if (!root) return 0;
        queue<TreeNode *> q;
        q.push(root);
        int depth = 0;
        while (!q.empty()) {
            int size = q.size();
            depth++;
            while (size--) {
                TreeNode * node = q.front(); q.pop();
                if (!node->left && !node->right)
                    return depth;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return 0;
    }
};
```