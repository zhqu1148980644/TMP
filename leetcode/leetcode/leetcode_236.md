---
title: Lowest Common Ancestor of a Binary Tree
date: 2021-01-04
---
#### Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

 

```
Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
```

 

#### Note:

-    All of the nodes' values will be unique.
-    p and q are different and both values will exist in the binary tree.


#### Solutions

1. ##### postorder traversal with counting

- Use inorder traversal to find the `first` root node contains both the given two nodes.

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
    TreeNode * res = nullptr;
    int count = 0;
    void dfs(TreeNode * root, TreeNode * p, TreeNode * q) {
        if (!root || count == 2) return;
        int precount = count;
        dfs(root->left, p, q);
        dfs(root->right, p, q);
        if (root == p || root == q)
            count++;
        if (count - precount == 2 && !res)
            res = root;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);
        return res;
    }
};
```

2. ##### recusion

- borrowed from others.
- This version would be a little slower in cases when two target nodes are in a relationship of ancestor and descendant.

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // here if root == null is the key.
        if (root == nullptr || root == p || root == q)
            return root;
        TreeNode * left = lowestCommonAncestor(root->left, p, q);
        TreeNode * right = lowestCommonAncestor(root->right, p, q);
        // if two target nodes was found in both children, then this node is the LCA.
        // For ancestors of this node, only one of two child containing this LCA will return non-null node(this LCA).
        // Thus the correctness can be maintained.
        if (left && right)
            return root;
        return left ? left : right;
    }
};
```

3. ##### inorder traversal, find the first common father using hashmap o(n) S(log(n))

- Traverse the binary tree and record each node's parent in a hashmap until fathers of `p` and `q` are found.
- Find the first common ancestor of `p` and `q` along their lineage tree.

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        unordered_map<TreeNode *, TreeNode *> fathers;
        stack<TreeNode *> s;
        while ((!fathers.count(p) || !fathers.count(q))) {
            while (root) {
                s.push(root);
                if (root->left) fathers[root->left] = root;
                if (root->right) fathers[root->right] = root;
                root = root->left;
            }
            // if the first node is the target, s.top() will cause error.
            if (s.empty()) break;
            root = s.top(); s.pop();
            root = root->right;
        }

        // push p and p's ancestor into p's family tree.
        unordered_set<TreeNode *> p_ftree;
        p_ftree.insert(p);
        while (fathers.count(p))
            p_ftree.insert(p = fathers[p]);

        // Find the first node which is first common ancestor.
        while (!p_ftree.count(q) && fathers.count(q))
            q = fathers[q];

        return q;
    }
};
```

4. ##### inorder traversal with iteration

- Use `lcalevel` to record the highest level(backwards from leafs) that contains both two target nodes.

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode *> s;
        int find = 0;
        int lca_level = INT_MAX;
        TreeNode * lca = nullptr;
        while (root || !s.empty()) {
            if (root) {
                s.push(root);
                root = root->left;
            } else {
                root = s.top(); s.pop();
                find += root == p || root == q;
                // record the highest level
                if (find && s.size() < lca_level) {
                    lca = root;
                    lca_level = s.size();
                }
                if (find >= 2)
                    break;

                root = root->right;
            }
        }
        return lca;
    }
};
```

4. ##### postorder traversal
