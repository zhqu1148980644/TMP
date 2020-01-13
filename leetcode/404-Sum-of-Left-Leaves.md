#### Find the sum of all left leaves in a given binary tree.

```
Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
```

#### Solutions

Be carefull with this case: 9 is not left leaf
    3
   / \
  9  20
   \
    7


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
    int sumOfLeftLeaves(TreeNode* root) {
        if (!root)
            return 0;
        if (root->left && !root->left->left && !root->left->right)
            return root->left->val + sumOfLeftLeaves(root->right);

        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
};
```

2. ##### iteration

- Level order traversal as example.

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
    int sumOfLeftLeaves(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);

        int sum = 0;
        while (!q.empty()) {
            root = q.front(); q.pop();
            if (root->left) {
                if (!root->left->left && !root->left->right)
                    sum += root->left->val;
                else
                    q.push(root->left);
            }
            if (root->right)
                q.push(root->right);
        }
        return sum;
    }
};
```