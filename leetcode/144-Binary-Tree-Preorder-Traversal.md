#### Given a binary tree, return the preorder traversal of its nodes' values.

```
Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]
```

#### Follow up: 
Recursive solution is trivial, could you do it iteratively?


#### Solutions

1. ##### recursion  O(n) S(log(n))

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
private:
    vector<int> res;

    void preorder(TreeNode * root) {
        res.push_back(root->val);
        if (root->left) preorder(root->left);
        if (root->right) preorder(root->right);
    }

public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root) preorder(root);
        return res;
    }
};
```

2. ##### iteration with stack  O(n) S(log(n))

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res; if (!root) return res;
        stack<TreeNode *> s; s.push(root);
        while (!s.empty()) {
            root = s.top(); s.pop();
            res.push_back(root->val);
            if (root->right) s.push(root->right);
            if (root->left) s.push(root->left);
        }
        return res;
    }
};
```

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res; if (!root) return res;
        stack<TreeNode *> s; s.push(root);
        while (!s.empty()) {
            root = s.top(); s.pop();
            while (root) {
                res.push_back(root->val);
                if (root->right) s.push(root->right);
                root = root->left;
            }
        }
        return res;
    }
};
```

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res; if (!root) return res;
        stack<TreeNode *> s; s.push(nullptr);
        while (root) {
            res.push_back(root->val);
            if (root->right) s.push(root->right);
            if (root->left) root = root->left;
            else {
                root = s.top(); s.pop();
            }
        }
        return res;
    }
};
```

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        vector<int> res;
        while (root || !s.empty()) {
            if (root) {
                res.push_back(root->val);
                if (root->right)
                    s.push(root->right);
                root = root->left;
            } else {
                root = s.top(); s.pop();
            }
        }
        return res;
    }
};

```

3. ##### Morris traversal O(n) S(1)

- Use the same strategy used in `probem 94`.
- Then difference between preorder and inorder is that visit the current node whenever meet a new node instead of visiting it after we tracebacked to it.

```c++
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;

        while (root) {
            if (root->left) {
                TreeNode * rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right == root) {
                    rdeep->right = NULL;
                    root = root->right;
                } else {
                    res.push_back(root->val);
                    rdeep->right = root;
                    root = root->left;
                }
            } else {
                res.push_back(root->val);
                root = root->right;
            }
        }
        return res;
    }
};
```