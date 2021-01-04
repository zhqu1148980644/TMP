---
title: Second Minimum Node In a Binary Tree
date: 2021-01-04
---
#### Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property root.val = min(root.left.val, root.right.val) always holds.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

```
Example 1:

Input: 
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.

 

Example 2:

Input: 
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
```

#### Solutions

1. ##### recursion

- borrowed from others

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
    int findLarger(TreeNode * root, int min) {
        if (!root) return -1;
        if (root->val > min)
            return root->val;
        int left = findLarger(root->left, min);
        int right = findLarger(root->right, min);
        if (left > min && right > min)
            return std::min(left, right);
        else
            return std::max(left, right);
    }
    int findSecondMinimumValue(TreeNode* root) {
        return findLarger(root, root->val);
    }
};
```

- Another concise version.
- borrowed from others.


```cpp
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if (!root->left)
            return -1;
        int left = root->left->val;
        int right = root->right->val;
        if (left == root->val)
            left = findSecondMinimumValue(root->left);
        if (right == root->val)
            right = findSecondMinimumValue(root->right);

        if (right != -1 && left != -1)
            return min(left, right);

        if (left != -1)
            return left;
        else
            return right;
    }
};
```

2. ##### bfs with queue

- Do not pre-exit when finding a node with larger value, if there are still nodes with values equal to the minimum value in the current level, the second minimum value may exit in deeper levels.
- Exit only if the minimum value of the current level is larger than the minimum value.

```cpp
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        int min = root->val;
        int nextmin = -1;
        while (!q.empty()) {
            int size = q.size();
            int levelmin = q.front()->val;
            while (size--) {
                root = q.front(); q.pop();
                if (root->val < levelmin)
                    levelmin = root->val;
                if (root->val == min) {
                    if (root->left) q.push(root->left);
                    if (root->right) q.push(root->right);
                }
                else if (nextmin == -1 || root->val < nextmin)
                    nextmin = root->val;
            }
            if (levelmin > min) break;
        }
        return nextmin;
    }
};
```