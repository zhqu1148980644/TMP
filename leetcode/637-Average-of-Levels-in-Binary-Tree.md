Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.

#### Solutions

1. ##### level order traversal

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
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode *> q; if (root) q.push(root);

        vector<double> res;
        while (!q.empty()) {
            int size = q.size();
            double sum = 0, num = size;
            while (size--) {
                root = q.front(); q.pop();
                sum += root->val;
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            res.push_back(sum / num);
        }

        return res;
    }
};
```


2. ##### recursion


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
    vector<double> sums, nums;
    void dfs(TreeNode * root, int level) {
        if (!root) return;
        if (level >= nums.size()) {
            sums.push_back(root->val);
            nums.push_back(1);
        }
        else {
            sums[level] += root->val;
            nums[level]++;
        }
        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    }
    vector<double> averageOfLevels(TreeNode* root) {
        dfs(root, 0);
        for (int i = 0; i < sums.size(); i++)
            sums[i] /= nums[i];
        
        return sums;
    }
};
```