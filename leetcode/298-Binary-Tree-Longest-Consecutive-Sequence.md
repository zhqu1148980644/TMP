Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

Example 1:

Input:

   1
    \
     3
    / \
   2   4
        \
         5

Output: 3

Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
Example 2:

Input:

   2
    \
     3
    / 
   2    
  / 
 1

Output: 2 

Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.


#### Solutions

1. ##### postorder traversal with iteration

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
    int longestConsecutive(TreeNode* root) {
        stack<TreeNode *> s;
        vector<int> lcslen = {0};
        TreeNode * prev = nullptr;
        int curlen, res = 0;
        while (root || !s.empty()) {
            while (root) {
                if (!s.empty() && s.top()->val + 1 == root->val)
                    curlen = lcslen.back() + 1;
                else
                    curlen = 1;
                lcslen.push_back(curlen);
                res = max(curlen, res);
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != prev)
                root = root->right;
            else {
                s.pop();
                lcslen.pop_back();
                prev = root;
                root = nullptr;
            }
        }
        return res;
    }
};
```


2. ##### recursion

- bottom up

```c++
class Solution {
public:
    int res = 0;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        int cur = 1;
        if (root->left && root->val + 1 == root->left->val)
            cur = max(cur, l + 1);
        if (root->right && r + 1 > cur && root->val + 1 == root->right->val)
            cur = max(cur, r + 1);
        res = max(res, cur);
        return cur;
    }
    int longestConsecutive(TreeNode* root) {
        dfs(root);
        return res;
    }
};
```