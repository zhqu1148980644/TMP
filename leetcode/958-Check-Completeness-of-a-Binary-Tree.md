Given a binary tree, determine if it is a complete binary tree.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

 

Example 1:



Input: [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
Example 2:



Input: [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.
 
Note:

The tree will have between 1 and 100 nodes.

#### Solutions

1. ##### bfs with queue

- Return false in two cases:
    - Whenever meets a node with no children(eigher left or right), all nodes after must have no children.
    - The left child is none while the right child is not.

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
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        bool check = false;
        while (q.size()) {
            int size = q.size();
            while (size--) {
                root = q.front(); q.pop();
                if (check && (root->left || root->right))
                    return false;
                if (!root->left && root->right)
                    return false;
                if (root->left)
                    q.push(root->left);
                else check = true;
                if (root->right)
                    q.push(root->right);
                else check = true;
            }
        }

        return true;
    }
};
```

borrowed from others
These two solutions check whether there is a `nonnull` node `after` a `nullnode`.

```c++
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        bool end = false;
        while (!q.empty()) {
            root = q.front(); q.pop();
            if (!root) {
                // here will be executed multiple times for passing null nodes.
                end = true;
                continue;
            }
            if (end) return false;
            q.push(root->left);
            q.push(root->right);
        }
        return true;
    }
};
```

or

```c++
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        TreeNode * prev = root;
        while (!q.empty()) {
            root = q.front(); q.pop();
            if (!prev && root)
                return false;
            if (root) {
                q.push(root->left);
                q.push(root->right);
            }
            prev = root;
        }
        return true;
    }
};
```

2. ##### recusion

- When the root node's index starts at `1`, the index of the last element would be the same as the size of the tree.
    - left child: `2 * index`  right child: `2 * index + 1`

```c++
class Solution {
public:
    double size = 0, maxindex = 0;
    void dfs(TreeNode * root, double index) {
        if (!root) return;
        size++;
        maxindex = max(maxindex, index);
        dfs(root->left, 2 * index);
        dfs(root->right, 2 * index + 1);
    }
    bool isCompleteTree(TreeNode* root) {
        dfs(root, 1);
        return maxindex == size;
    }
};
```