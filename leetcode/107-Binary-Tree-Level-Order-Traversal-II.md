#### Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

```
For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
```

#### Solutions

- The only difference between this problem and problem 102 is the order of levels.

- `Reverse` the final results would be feasible since the height of a binary search tree will be `log(n)` in average.

- Or you can use a linked list to insert new vectors at the front. however, converting the linked list to vector cost the same time as reversing.

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode *> q; if (root) q.push(root);

        while (!q.empty()) {
            int size = q.size();
            vector<int> lres;
            while (size--) {
                root = q.front(); q.pop();
                lres.push_back(root->val);
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            res.push_back(lres);
        }
        // reverse the result
        reverse(res.begin(), res.end());
        return res;
    }
};
```
