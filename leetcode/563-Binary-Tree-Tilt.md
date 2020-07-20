#### Given a binary tree, return the tilt of the whole tree.

The tilt of a tree node is defined as the absolute difference between the sum of all left subtree node values and the sum of all right subtree node values. Null node has tilt 0.

The tilt of the whole tree is defined as the sum of all nodes' tilt.

```
Example:

Input: 
         1
       /   \
      2     3
Output: 1
Explanation: 
Tilt of node 2 : 0
Tilt of node 3 : 0
Tilt of node 1 : |2-3| = 1
Tilt of binary tree : 0 + 0 + 1 = 1
```

#### Note:

-    The sum of node values in any subtree won't exceed the range of 32-bit integer.
-    All the tilt values won't exceed the range of 32-bit integer.


#### Solutions

1. ##### postorder with recursion

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
    int res = 0;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        int lh = dfs(root->left);
        int rh = dfs(root->right);
        res += abs(lh - rh);
        return lh + rh + root->val;
    }
    int findTilt(TreeNode* root) {
        if (root) dfs(root);
        return res;
    }
};
```

2. ##### iteration with stack


- use stack to record the sum of left tree and a single variable to record the sum of right tree.

```c++
class Solution {
public:
    int findTilt(TreeNode* root) {
        stack<TreeNode *> s;
        TreeNode * prev = nullptr;
        stack<int> lefts; int right = 0;
        int res = 0;
        
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != prev)
                root = root->right;
            else {
                s.pop();
                int left = 0;
                if (root->left) {
                    left = lefts.top(); lefts.pop();
                }
                res += abs(left - right);
                if (!s.empty() && s.top()->left == root) {
                    lefts.push(left + right + root->val);
                    right = 0;
                }
                else
                    right = left + right + root->val;
                prev = root;
                root = nullptr;
            }
        }
        return res;
    }
};
```