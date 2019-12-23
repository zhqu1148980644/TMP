#### Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

```
Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```


#### Solutions

1. ##### recursion

```c++
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

    vector<TreeNode *> genTree(int start, int end) {
        vector<TreeNode *> res;
        if (start > end)
            res.push_back(nullptr);
        else if (start == end) {
            res.push_back(new TreeNode(start));
        } else {
            for (int i = start; i <= end; i++) {
                vector<TreeNode *> lefttree = genTree(start, i - 1);
                vector<TreeNode *> righttree = genTree(i + 1, end);
                for (auto & ltree : lefttree) {
                    for (auto & rtree : righttree) {
                        TreeNode * root = new TreeNode(i);
                        root->left = ltree;
                        root->right = rtree;
                        res.push_back(root);
                    }
                }
            }
        }
        return res;
    }

    vector<TreeNode *> generateTrees(int n) {
        if (!n)
            return vector<TreeNode *>();
        else
            return genTree(1, n);
    }
};
```


2. ##### recursion with mem cache

- Structures of trees built from `2 3` are the same as structures of trees built from `98 99`. They differ only in values but not structures.
    - yeah, structures from `2 3` are the same as structures from `1 2`.

- Codes in the first method recursively calculate tree structures from different values but with same structures.

```c++
typedef TreeNode node;
class Solution {
public:
    node * cloneTree(node * root, int offset) {
        if (!root)
            return NULL;
        else {
            node * croot = new TreeNode(root->val + offset);
            croot->left = cloneTree(root->left, offset);
            croot->right = cloneTree(root->right, offset);
            return croot;
        }
    }

    vector<TreeNode*> generateTrees(int n) {
        if (!n) return vector<node *>();
        vector<vector<node *>> dp(n + 1, vector<node *>());
        dp[0].push_back(nullptr);
        for (int len = 1; len <= n; len++) {
            for (int rootval = 1; rootval <= len; rootval++) {
                int lenl = rootval - 1;
                int lenr = len - rootval;
                for (auto & ltree : dp[lenl])
                    for (auto & rtree : dp[lenr]) {
                        TreeNode * root = new TreeNode(rootval);
                        root->left = ltree;
                        root->right = cloneTree(rtree, rootval);
                        dp[len].push_back(root);
                    }
            }
        }
        return dp[n];
    }
};
```