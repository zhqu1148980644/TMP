---
title: Same Tree
date: 2021-01-04
---
#### Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.

```
Example 1:

Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true
Example 2:

Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

Output: false
Example 3:

Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false
```

#### Solutions

1. ##### recursion(dfs)


```cpp
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p && q)
            return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        else return !p && !q;
    }
};
```

2. ##### iteration(dfs/bfs) with queue or stack

stack

```cpp
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        stack<TreeNode *> s1, s2;
        while (p || q || !s1.empty() || !s2.empty()) {
            if (p || q) {
                if (!(p && q)) return false;
                s1.push(p); s2.push(q);
                p = p->left; q = q->left;
            }
            else {
                if (s1.empty() || s2.empty())
                    return false;
                p = s1.top(); s1.pop();
                q = s2.top(); s2.pop();
                if (p->val != q->val)
                    return false;
                p = p->right; q = q->right;
            }
        }

        return true;
    }
};
```

Queue

```cpp
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<TreeNode *> Q;
        Q.push(p); Q.push(q);

        while (!Q.empty()) {
            p = Q.front(); Q.pop();
            q = Q.front(); Q.pop();
            if (!p && !q) continue;
            if (!p || !q || p->val != q->val)
                return false;
            Q.push(p->left); Q.push(q->left);
            Q.push(p->right); Q.push(q->right);
        }

        return true;
    }
};
```