---
title: Print Binary Tree
date: 2021-01-04
---
Print a binary tree in an m*n 2D string array following these rules:

The row number m should be equal to the height of the given binary tree.
The column number n should always be an odd number.
The root node's value (in string format) should be put in the exactly middle of the first row it can be put. The column and the row where the root node belongs will separate the rest space into two parts (left-bottom part and right-bottom part). You should print the left subtree in the left-bottom part and print the right subtree in the right-bottom part. The left-bottom part and the right-bottom part should have the same size. Even if one subtree is none while the other is not, you don't need to print anything for the none subtree but still need to leave the space as large as that for the other subtree. However, if two subtrees are none, then you don't need to leave space for both of them.
Each unused space should contain an empty string "".
Print the subtrees following the same rules.
Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   / 
  3 
 / 
4 
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
Note: The height of binary tree is in the range of [1, 10].

#### Solutions

1. ##### recursion

- Count the number of rows and columns of the results in the first traversal, then traverse again to fill the result table.

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
    pair<int, int> shape(TreeNode * root) {
        if (!root) return {0, 0};
        auto [wl, hl] = shape(root->left);
        auto [wr, hr] = shape(root->right);
        int w = 2 * max(wl, wr) + 1;
        int h = max(hl, hr) + 1;
        return  {w, h};
    }
    void fill(vector<vector<string>>::iterator rowit, TreeNode * root, int lo, int hi) {
        if (!root) return;
        int mid = lo + ((hi - lo) / 2);
        (*rowit)[mid] = to_string(root->val);
        fill(rowit + 1, root->left, lo, mid);
        fill(rowit + 1, root->right, mid + 1, hi);
    }
    vector<vector<string>> printTree(TreeNode* root) {
        auto [w, h] = shape(root);
        vector<vector<string>> res(h, vector<string>(w));
        fill(res.begin(), root, 0, w);
        return res;
    }
};
```

- it's clear that the number of columns equals the number of nodes in a full binary tree with the same height. ie: `2^h - 1`

```cpp
class Solution {
public:
    void fill(vector<vector<string>>::iterator rowit, TreeNode * root, int lo, int hi) {
        if (!root) return;
        int mid = lo + ((hi - lo) / 2);
        (*rowit)[mid] = to_string(root->val);
        fill(rowit + 1, root->left, lo, mid);
        fill(rowit + 1, root->right, mid + 1, hi);
    }
    vector<vector<string>> printTree(TreeNode* root) {
        function<int(TreeNode *)> height = [&](TreeNode * root) {
            if (!root) return 0;
            return 1 + max(height(root->left), height(root->right));
        };
        int h = height(root), w = (1 << h) - 1;

        vector<vector<string>> res(h, vector<string>(w));
        fill(res.begin(), root, 0, w);
        return res;
    }
};
```


2. ##### iteration

```cpp

```