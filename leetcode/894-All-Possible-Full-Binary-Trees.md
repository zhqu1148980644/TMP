A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one possible tree.

Each node of each tree in the answer must have node.val = 0.

You may return the final list of trees in any order.

 

Example 1:

Input: 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Explanation:

 

Note:

1 <= N <= 20

#### Solutions

1. ##### recursion with memoization

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
    vector<vector<TreeNode *>> memo;

    vector<TreeNode *> build(int N) {
        if (memo[N].size()) return memo[N];
        vector<TreeNode *> res;
        for (int i = 1; i < N - 1; i += 2) {
            for (auto lc : build(i))
                for (auto rc : build(N - i - 1)) {
                    TreeNode * root = new TreeNode(0);
                    root->left = lc;
                    root->right = rc;
                    res.push_back(root);
                }
        }
        return memo[N] = res;
    }
    vector<TreeNode*> allPossibleFBT(int N) {
        memo = vector<vector<TreeNode *>>(N + 1);
        memo[1] = {new TreeNode(0)};
        return build(N);
    }
};
```