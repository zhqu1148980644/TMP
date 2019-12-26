#### Invert a binary tree.

```
Example:

Input:

     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

#### Trivia:
This problem was inspired by this original tweet by Max Howell:

Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so f*** off.


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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        TreeNode * right = root->right;
        root->right = invertTree(root->left);
        root->left = invertTree(right);
        return root;
    }
};
```

2. ##### iteration

inorder

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        TreeNode * r = root;
        stack<TreeNode *> s;

        while (root || !s.empty()) {
            if (root) {
                s.push(root);
                root = root->left;
            }
            else {
                root = s.top(); s.pop();
                TreeNode * right = root->right;
                root->right = root->left;
                root->left = right;
                root = right;
            }
        }
        return r;
    }
};
```

preorder

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        TreeNode * r = root;
        stack<TreeNode *> s;

        while (root || !s.empty()) {
            if (root) {
                TreeNode * right = root->right;
                root->right = root->left;
                root->left = right;
                if (right) s.push(right);
                root = root->right;
            }
            else {
                root = s.top(); s.pop();
            }
        }
        return r;
    }
};
```

level order

```c++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        TreeNode * r = root;
        queue<TreeNode *> q;
        if (root) q.push(root);

        while (!q.empty()) {
            root = q.front(); q.pop();
            if (root->left) q.push(root->left);
            if (root->right) q.push(root->right);
            TreeNode * right = root->right;
            root->right = root->left;
            root->left = right;
        }

        return r;
    }
};
```

....