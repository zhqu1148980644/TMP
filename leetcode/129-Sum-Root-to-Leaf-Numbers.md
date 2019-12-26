#### Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

##### Note: 
A leaf is a node with no children.

```
Example:

Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
Example 2:

Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
```

#### Solutions

1. ##### recursion


Naive one. 

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
    vector<int> path;
    int totalsum = 0;

    void preorder(TreeNode * root) {
        path.push_back(root->val);
        if (!root->left && !root->right) {
            int s = 0;
            for (int i = 0; i < path.size(); i++)
                s = s * 10 + path[i];
            totalsum += s;
        } else {
            if (root->left) preorder(root->left);
            if (root->right) preorder(root->right);
        }
        path.pop_back();
    }
    int sumNumbers(TreeNode* root) {
        if (root) preorder(root);

        return totalsum;
    }
};
```

- Since nodes near the root node will be shared by many paths, massive redundant computations are wasted in the first solution.

```c++
class Solution {
public:
    vector<int> path;
    int totalsum = 0;

    void preorder(TreeNode * root, int num) {
        if(!root) return;
        num += root->val;
        if (!root->left && !root->right)
            totalsum += num;
        else {
            preorder(root->left, num * 10);
            preorder(root->right, num * 10);
        }
    }
    int sumNumbers(TreeNode* root) {
        if (root) preorder(root, 0);

        return totalsum;
    }
};
```

Or without global variable.

```c++
class Solution {
public:
    int summleaf(TreeNode * root, int num) {
        if (!root) return 0;
        num += root->val;
        if (!root->left && !root->right)
            return num;
        else
            return summleaf(root->left, num * 10) 
                 + summleaf(root->right, num * 10);
    }
    int sumNumbers(TreeNode* root) {
        return summleaf(root, 0);
    }
};
```

2. ##### iteration with stack

- Other traversal orders could also work.

```c++
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        stack<TreeNode *> s;
        int numsum = 0, curnum = 0;
        TreeNode * prev = nullptr;

        while (root || !s.empty()) {
            while (root) {
                curnum = curnum * 10 + root->val;
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (!root->left && !root->right)
                numsum += curnum;
            if (root->right && root->right != prev)
                root = root->right;
            else {
                curnum = (curnum - root->val) / 10; 
                prev = root; s.pop();
                root = nullptr;
            }
        }
        return numsum;
    }
};
```