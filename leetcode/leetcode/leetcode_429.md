---
title: N ary Tree Level Order Traversal
date: 2021-01-04
---
Given an n-ary tree, return the level order traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

 

Example 1:



Input: root = [1,null,3,2,4,null,5,6]
Output: [[1],[3,2,4],[5,6]]
Example 2:



Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
 

Constraints:

The height of the n-ary tree is less than or equal to 1000
The total number of nodes is between [0, 10^4]

#### Solutions

1. ##### bfs

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node *> q;
        if (root) q.push(root);

        vector<vector<int>> res;
        while (!q.empty()) {
            int size = q.size();
            res.push_back({});
            while (size--) {
                root = q.front(); q.pop();
                res.back().push_back(root->val);
                for (auto & child : root->children)
                    if (child) q.push(child);
            }
        }

        return res;
    }
};
```


2. ##### dfs