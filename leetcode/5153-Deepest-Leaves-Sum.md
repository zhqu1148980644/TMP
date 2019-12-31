#### Given a binary tree, return the sum of values of its deepest leaves.
 


![](https://assets.leetcode.com/uploads/2019/07/31/1483_ex1.png)
```
Example 1:



Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15
```
 

#### Constraints:

- The number of nodes in the tree is between 1 and 10^4.
- The value of nodes is between 1 and 100.


#### Solutions

1. ##### dfs with recursion

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
    int maxlevel = 0;
    int maxsum = 0;

    void dfs(TreeNode * root, int curlevel) {
        if (!root) return;
        if (curlevel > maxlevel) {
            maxlevel = curlevel;
            maxsum = root->val;
        } else if (curlevel == maxlevel)
            maxsum += root->val;
        dfs(root->left, curlevel + 1);
        dfs(root->right, curlevel + 1);
    }

public:
    int deepestLeavesSum(TreeNode* root) {
        dfs(root, 0);
        return maxsum;
    }
};
```

2. ##### bfs with queue

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
    int deepestLeavesSum(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        int sumval;
        while (!q.empty()) {
            int size = q.size();
            sumval = 0;
            while (size--) {
                root = q.front(); q.pop();
                sumval += root->val;
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
        }
        return sumval;
    }
};
```