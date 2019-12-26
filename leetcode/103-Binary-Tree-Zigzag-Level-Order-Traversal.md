#### Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

```
For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
```

#### Solutions

1. ##### queue

```c++
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode *> q;
        if (root) q.push(root);

        // lr == true means from left to right
        bool lr = true;
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size, 0);
            while (size--) {
                root = q.front(); q.pop();
                // Alterations
                level[lr ? level.size() - size - 1 : size] = root->val;
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            res.push_back(move(level));
            // reverse the order
            lr = !lr;
        }

        return res;
    }
};
```