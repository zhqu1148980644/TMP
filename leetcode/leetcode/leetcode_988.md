---
title: Smallest String Starting From Leaf
date: 2021-01-04
---
Given the root of a binary tree, each node has a value from 0 to 25 representing the letters 'a' to 'z': a value of 0 represents 'a', a value of 1 represents 'b', and so on.

Find the lexicographically smallest string that starts at a leaf of this tree and ends at the root.

(As a reminder, any shorter prefix of a string is lexicographically smaller: for example, "ab" is lexicographically smaller than "aba".  A leaf of a node is a node that has no children.)

 

Example 1:



Input: [0,1,2,3,4,3,4]
Output: "dba"
Example 2:



Input: [25,1,3,1,3,0,2]
Output: "adz"
Example 3:



Input: [2,2,1,null,1,0,null,0]
Output: "abc"
 

Note:

The number of nodes in the given tree will be between 1 and 8500.
Each node in the tree will have a value between 0 and 25.

#### Solutions

1. ##### dfs

- The solution below is an example of wrong answer in which postorder traversal are used.
- For example: The string from the left child is `abab`, and the right one is `ab`, in normal case, we would choose `ab` as the smallest one, however, their true lexicographically order is not soly depends on the current, but also the current node's ascendant. if the parent node is `z`, then `ababz` would be smaller than `abz`.

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
    string smallestFromLeaf(TreeNode* root) {
        if (!root) return string(1, 'z' + 1);
        char curc = root->val + 'a';
        if (!root->left && !root->right)
            return string(1, curc);
        auto l = smallestFromLeaf(root->left) + curc;
        auto r = smallestFromLeaf(root->right) + curc;
        return l < r ? l : r;
    }
};
```

- the correct version

```cpp
class Solution {
public:
    string res = string(100, 'z');
    void dfs(TreeNode * root, string s) {
        if (!root) return;
        s.push_back(root->val + 'a');
        if (!root->left && !root->right) {
            reverse(s.begin(), s.end());
            if (s < res) res = s;
        }
        else {
            dfs(root->left, s);
            dfs(root->right, s);
        }
    }
    string smallestFromLeaf(TreeNode* root) {
        dfs(root, "");
        return res;
    }
};
```