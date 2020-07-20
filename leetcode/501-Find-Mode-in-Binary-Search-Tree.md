#### Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

#### Assume a BST is defined as follows:

-    The left subtree of a node contains only nodes with keys less than or equal to the node's key.
-    The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
-    Both the left and right subtrees must also be binary search trees.

 

```
For example:
Given BST [1,null,2,2],

   1
    \
     2
    /
   2

 

return [2].
```

#### Note: If a tree has more than one mode, you can return them in any order.

#### Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).


#### Solutions

- This problem is similar to find modes in a sorted array.

1. ##### inorder traversal

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
    int maxcount = 0, curcount = 0, prev = INT_MIN;
    vector<int> res;
    void inorder(TreeNode * root) {
        if (root->left)
            inorder(root->left);
        curcount = prev == root->val ? curcount + 1 : 1;
        if (curcount > maxcount) {
            maxcount = curcount;
            res = {root->val};
        }
        else if (curcount == maxcount)
            res.push_back(root->val);

        prev = root->val;
        if (root->right)
            inorder(root->right);
    }
    vector<int> findMode(TreeNode* root) {
        if (root) inorder(root);
        return res;
    }
};
```

2. ##### morris inorder traversal

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
    vector<int> findMode(TreeNode* root) {
        int max = 0, cur = 0, prev = INT_MIN;
        vector<int> res;
        TreeNode * rdeep;
        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right == root)
                    rdeep->right = nullptr;
                else {
                    rdeep->right = root;
                    root = root->left;
                    continue;
                }
            }
            cur = prev == root->val ? cur + 1 : 1;
            if (cur > max) {
                res = {root->val};
                max = cur;
            }
            else if (cur == max)
                res.push_back(root->val);
            prev = root->val;
            root = root->right;
        }

        return res;
    }
};
```