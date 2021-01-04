---
title: Recover a Tree From Preorder Traversal
date: 2021-01-04
---
We run a preorder depth first search on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

If a node has only one child, that child is guaranteed to be the left child.

Given the output S of this traversal, recover the tree and return its root.

 

Example 1:



Input: "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]
Example 2:



Input: "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]
 

Example 3:



Input: "1-401--349---90--88"
Output: [1,401,null,349,88,90]
 

Note:

The number of nodes in the original tree is between 1 and 1000.
Each node will have a value between 1 and 10^9.

#### Solutions

1. ##### dfs

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
    unordered_map<int, int> depth;
    TreeNode * build(const string & s, int & cur, int d) {
        if (cur >= s.size()) return nullptr;
        int len = s.find_first_not_of('-', cur) - cur;
        if (len != d) return nullptr;
        cur += len;
        int val = 0;
        while (cur < s.size() && isdigit(s[cur]))
            val = val * 10 + (s[cur++] - '0');
        TreeNode * root = new TreeNode(val);
        root->left = build(s, cur, d + 1);
        root->right = build(s, cur, d + 1);
        return root;
    }
    TreeNode* recoverFromPreorder(string S) {
        int cur = 0;
        return build(S, cur, 0);
    }
};
```

2. ##### itration

- Simply simulate what we have done when using the system stack.

```cpp
class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        stack<TreeNode *> s;
        TreeNode * root = nullptr;
        
        int cur = 0, len = 0;
        while (cur < S.size()) {
            if (len == -1)
                len = S.find_first_not_of('-', cur) - cur;
            if (len != s.size()) {
                s.pop(); continue;
            }
            cur += len; len = -1;
            int val = 0;
            while (cur < S.size() && isdigit(S[cur]))
                val = val * 10 + (S[cur++] - '0');
            TreeNode * node = new TreeNode(val);
            if (!s.size())
                s.push(root = node);
            else {
                if (!s.top()->left)
                    s.push(s.top()->left = node);
                else
                    s.push(s.top()->right = node);
            }
        }

        return root;
    }
};
```