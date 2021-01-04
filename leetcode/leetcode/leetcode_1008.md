---
title: Construct Binary Search Tree from Preorder Traversal
date: 2021-01-04
---
Return the root node of a binary search tree that matches the given preorder traversal.

(Recall that a binary search tree is a binary tree where for every node, any descendant of node.left has a value < node.val, and any descendant of node.right has a value > node.val.  Also recall that a preorder traversal displays the value of the node first, then traverses node.left, then traverses node.right.)

It's guaranteed that for the given test cases there is always possible to find a binary search tree with the given requirements.

Example 1:

Input: [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

 

Constraints:

1 <= preorder.length <= 100
1 <= preorder[i] <= 10^8
The values of preorder are distinct.

#### Solutions

1. ##### straight forward

- Use a upperbound to make the recursive building process automatically ends and returns.

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode * build(vector<int> & pre, int & cur, int bound) {
        if (cur >= pre.size() || pre[cur] > bound) return nullptr;
        TreeNode * root = new TreeNode(pre[cur++]);
        root->left = build(pre, cur, root->val);
        root->right = build(pre, cur, bound);
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int index = 0;
        return build(preorder, index, INT_MAX);
    }
};
```

2. ##### stack

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if (!preorder.size()) return nullptr;
        stack<TreeNode *> s;
        TreeNode dummy(INT_MAX);
        s.push(&dummy);
        TreeNode * fa = &dummy;

        for (auto val : preorder) {
            while (val > s.top()->val) {
                fa = s.top(); s.pop();
            }
            TreeNode * root = new TreeNode(val);
            if (val > fa->val)
                fa->right = root;
            else
                fa->left = root;
            s.push(fa = root);
        }

        return dummy.left;
    }
};
```