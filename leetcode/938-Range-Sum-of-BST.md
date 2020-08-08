Given the root node of a binary search tree, return the sum of values of all nodes with value between L and R (inclusive).

The binary search tree is guaranteed to have unique values.

 

Example 1:

Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
Output: 32
Example 2:

Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
Output: 23
 

Note:

The number of nodes in the tree is at most 10000.
The final answer is guaranteed to be less than 2^31.

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
    int rangeSumBST(TreeNode* root, int L, int R) {
        if (!root) return 0;
        if (root->val < L)
            return rangeSumBST(root->right, L, R);
        else if (root->val > R)
            return rangeSumBST(root->left, L, R);
        else
            return root->val 
                 + rangeSumBST(root->left, L, root->val) 
                 + rangeSumBST(root->right, root->val, R);
    }
};
```

2. ##### iteration with stack

```c++
class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        stack<TreeNode *> s;
        int res = 0;
        while (root || s.size()) {
            while (root) {
                s.push(root);
                root = root->val >= L ? root->left : nullptr;
            }
            root = s.top(); s.pop();
            if (root->val >= L && root->val <= R)
                res += root->val;
            root = root->val <= R ? root->right : nullptr;
        }
        return res;
    }
};
```

3. ###### iteration with queue

```c++
class Solution {
public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        int res = 0;

        while (!q.empty()) {
            root = q.front(); q.pop();
            if (root->val >= L && root->val <= R)
                res += root->val;
            if (root->left && root->val >= L)
                q.push(root->left);
            if (root->right && root->val <= R)
                q.push(root->right);
        }

        return res;
    }
};
```