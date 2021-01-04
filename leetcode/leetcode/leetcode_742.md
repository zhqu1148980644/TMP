---
title: Closest Leaf in a Binary Tree
date: 2021-01-04
---
Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node to target k in the tree.

Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree. Also, a node is called a leaf if it has no children.

In the following examples, the input tree is represented in flattened form row by row. The actual root tree given will be a TreeNode object.

Example 1:

Input:
root = [1, 3, 2], k = 1
Diagram of binary tree:
          1
         / \
        3   2

Output: 2 (or 3)

Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
Example 2:

Input:
root = [1], k = 1
Output: 1

Explanation: The nearest leaf node is the root node itself.
Example 3:

Input:
root = [1,2,3,4,null,null,null,5,null,6], k = 2
Diagram of binary tree:
             1
            / \
           2   3
          /
         4
        /
       5
      /
     6

Output: 3
Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
Note:
root represents a binary tree with at least 1 node and at most 1000 nodes.
Every node has a unique node.val in range [1, 1000].
There exists some node in the given binary tree for which node.val == k.

#### Solutions

1. ##### dynamic programming O(n) S(n)

- `mindis[cur] = min(mindis[cur], mindis(parent) + 1)`
- Use postorder traversal to calculate the mininum distance between self and leaf nodes within the current subtree.
- Then traverse again to update the mininum distance with parent's mindis.

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
    unordered_map<TreeNode *, pair<int, int>> m;
    int res = INT_MAX;
    pair<int, int> dfs(TreeNode * root) {
        if (!root) return {INT_MAX, INT_MAX};
        if (!root->left && !root->right)
            return m[root] = {0, root->val};
        auto [lh, vl] = dfs(root->left);
        auto [rh, vr] = dfs(root->right);
        if (lh < rh)
            return m[root] = {lh + 1, vl};
        else
            return m[root] = {rh + 1, vr};
    }
    void dp(TreeNode * root, TreeNode * parent, int target) {
        if (!root || res != INT_MAX) return;
        if (m[root].first > m[parent].first + 1)
            m[root] = {m[parent].first + 1, m[parent].second};
        dp(root->left, root, target);
        dp(root->right, root, target);
        if (root->val == target)
            res = m[root].second;

        return;
    }
    int findClosestLeaf(TreeNode* root, int k) {
        dfs(root);
        dp(root, root, k);
        return res;
    }
};
```

2. ##### convert the binary tree into graph

- After the unordered graph has been built, use bfs to find the first node with 1 degree(leaf node).

```cpp
class Solution {
public:
    using G = unordered_map<TreeNode *, vector<TreeNode *>>;
    void build(TreeNode * root, TreeNode * parent, G & g) {
        if (!root || (!root->left && !root->right)) return;
        g[root].push_back(parent);
        g[root].push_back(root->left);
        g[root].push_back(root->right);
        build(root->left, root, g);
        build(root->right, root, g);
    }
    int findClosestLeaf(TreeNode* root, int k) {
        G g;
        build(root, nullptr, g);

        root = nullptr;
        for (auto & [node, v] : g)
            if (node->val == k)
                root = node;

        if (!root) return k;
        unordered_set<TreeNode *> visited;
        queue<TreeNode *> q; q.push(root);
        visited.insert(root);

        while (!q.empty()) {
            root = q.front(); q.pop();
            if (!g.count(root)) return root->val;
            for (auto out : g[root]) {
                if (!out || visited.count(out)) continue;
                if (!g.count(out)) return out->val;
                q.push(out);
                visited.insert(out);
            }
        }

        return k;
    }
};
```