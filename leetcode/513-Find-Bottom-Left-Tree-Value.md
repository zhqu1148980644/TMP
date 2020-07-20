Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

    2
   / \
  1   3

Output:
1
Example 2:
Input:

        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7

Output:
7
Note: You may assume the tree (i.e., the given root node) is not NULL.

#### Soltuions

1. ##### use inorder traversal to find the leftmost node in each level

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
    TreeNode * res = nullptr; int maxd = -1;
    void dfs(TreeNode * root, int depth) {
        if (!root) return;
        dfs(root->left, depth + 1);
        if (depth > maxd)
            res = root;
        maxd = max(maxd, depth);
        dfs(root->right, depth + 1);
    }
    int findBottomLeftValue(TreeNode* root) {
        if (root) dfs(root, 0);
        return res->val;
    }
};
```

or iteration version

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
    int findBottomLeftValue(TreeNode* root) {
        stack<pair<TreeNode *, int>> s;
        int maxd = -1, curd = -1;
        TreeNode * res = nullptr;
        while (!s.empty() || root) {
            while (root) {
                s.push({root, ++curd});
                root = root->left;
            }
            root = s.top().first;
            curd = s.top().second; s.pop();
            if (curd > maxd)
                res = root;
            maxd = max(maxd, curd);
            root = root->right;
        }
        return res->val;
    }
};
```

2. ##### level order traversal

```c++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        TreeNode * res = nullptr;
        
        while (!q.empty()) {
            int size = q.size();
            res = q.front();
            while (size--) {
                root = q.front(); q.pop();
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
        }

        return res->val;
    }
};
```