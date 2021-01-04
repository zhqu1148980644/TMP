---
title: Maximum Width of Binary Tree
date: 2021-01-04
---
Given a binary tree, write a function to get the maximum width of the given tree. The width of a tree is the maximum width among all levels. The binary tree has the same structure as a full binary tree, but some nodes are null.

The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

Example 1:

Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:

Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:

Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:

Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).


Note: Answer will in the range of 32-bit signed integer.

##### Solutions

- Map each node to index when the tree is raveled and is layed out level by level. `root(i), leftchild(2 * i), rightchild(2*i + 1)`
- Then, record the leftmost nodes' index in each level.

1. ##### recursion

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
    unordered_map<int, unsigned long> m;
    unsigned long res = 0;
    void dfs(TreeNode * root, int d, unsigned long index) {
        if (!root) return;
        dfs(root->left, d + 1, index * 2);
        dfs(root->right, d + 1, index * 2 + 1);
        if (!m.count(d)) m[d] = index;
        res = max(index - m[d] + 1, res);
    }
    int widthOfBinaryTree(TreeNode* root) {
        dfs(root, 0, 0);
        return res;
    }
};
```

2. ##### level order traversal

```cpp
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        queue<pair<TreeNode *, unsigned long>> q;
        if (root) q.emplace(root, 1);
        unsigned long res = 0, mini, index;

        while (!q.empty()) {
            int size = q.size();
            mini = q.front().second;
            while (size--) {
                root = q.front().first;
                index = q.front().second; q.pop();
                if (root->left) q.emplace(root->left, 2 * index);
                if (root->right) q.emplace(root->right, 2 * index + 1);
            }
            res = max(index - mini + 1, res);
        }

        return res;
    }
};
``