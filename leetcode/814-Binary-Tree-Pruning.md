We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]
 
Explanation: 
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.


Example 2:
Input: [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]



Example 3:
Input: [1,1,0,1,1,0,1,0]
Output: [1,1,0,1,1,null,1]



Note:

The binary tree will have at most 100 nodes.
The value of each node will only be 0 or 1.

#### Solutions

- Ensure no daunting pointers in real codes.

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
    bool hasone(TreeNode * root) {
        if (!root) return false;
        bool checkl = hasone(root->left);
        bool checkr = hasone(root->right);
        if (root->left && !checkl)
            root->left = nullptr;
        if (root->right && !checkr)
            root->right = nullptr;
        return checkl || checkr || root->val == 1;
    }
    TreeNode* pruneTree(TreeNode* root) {
        return hasone(root) ? root : nullptr; 
    }
};
```


2. ##### postorder with iteration

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
    TreeNode* pruneTree(TreeNode* root) {
        TreeNode * prev = nullptr, * head = root;
        stack<TreeNode *> s;
        stack<bool> lefts;
        bool rights, cur;
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
                bool left = false, right = false;
                if (root->left) {
                    left = lefts.top(); lefts.pop();
                    if (!left) root->left = nullptr;
                }
                if (root->right) {
                    right = rights;
                    if (!right) root->right = nullptr;
                }
                cur = root->val == 1 || left || right;
                if (s.size())
                    if (root == s.top()->left)
                        lefts.push(cur);
                    else
                        rights = cur;
                prev = root;
                root = nullptr;
            }
        }
        return cur ? head : nullptr;
    }
};
```