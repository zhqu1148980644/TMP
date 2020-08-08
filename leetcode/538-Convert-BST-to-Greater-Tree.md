#### Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

```
Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13
```

#### Solutions

- Visit nodes in a reversed inorder manner.

1. ##### inorder traversal with recursion

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
    int sum = 0;
public:
    TreeNode* convertBST(TreeNode* root) {
        if (root) {
            convertBST(root->right);
            sum += root->val;
            root->val = sum;
            convertBST(root->left);
        }
        return root;
    }
};
```


2. ##### inorder with stack

```c++
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int accum = 0;
        stack<TreeNode *> s;
        TreeNode * head = root;

        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->right;
            }
            root = s.top(); s.pop();
            root->val = accum += root->val;
            root = root->left;
        }

        return head;
    }
};
```


3. ##### inorder with morris method

```c++
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int accum = 0;
        TreeNode * ldeep, * head = root;

        while (root) {
            if (root->right) {
                ldeep = root->right;
                while (ldeep->left && ldeep->left != root)
                    ldeep = ldeep->left;
                if (ldeep->left == root)
                    ldeep->left = nullptr;
                else {
                    ldeep->left = root;
                    root = root->right;
                    continue;
                }
            }
            root->val = accum += root->val;
            root = root->left;
        }

        return head;
    }
};
```