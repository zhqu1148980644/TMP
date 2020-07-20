You need to find the largest value in each row of a binary tree.

Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]

#### Solutions

1. ##### dfs with recursion

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
    vector<int> res;
    void dfs(TreeNode * root, int depth) {
        if (!root) return;
        if (res.size() <= depth)
            res.push_back(INT_MIN);
        res[depth] = max(res[depth], root->val);
        dfs(root->left, depth + 1);
        dfs(root->right, depth + 1);
    }
    vector<int> largestValues(TreeNode* root) {
        if (root) dfs(root, 0);
        return res;
    }
};
```

2. ##### level order traversal

```c++
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue<TreeNode *> q; if (root) q.push(root);
        vector<int> res;

        while (!q.empty()) {
            int size = q.size();
            int maxval = INT_MIN;
            while (size--) {
                root = q.front(); q.pop();
                maxval = max(maxval, root->val);
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right); 
            }
            res.push_back(maxval);
        }

        return res;
    }
};
```