Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level X such that the sum of all the values of nodes at level X is maximal.

 

Example 1:



Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.
 

Note:

The number of nodes in the given tree is between 1 and 10^4.
-10^5 <= node.val <= 10^5

#### Solutions

1. ##### dfs

- Note that there is no way to get the sum of each level untill all elements in each level are visited.

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
    vector<int> sums = {0};
    void dfs(TreeNode * root, int level) {
        if (!root) return;
        if (level >= sums.size())
            sums.push_back(0);
        sums[level] += root->val;
        dfs(root->left, level + 1);
        dfs(root->right, level + 1);
    } 
    int maxLevelSum(TreeNode* root) {
        dfs(root, 1);

        int maxsum = *max_element(sums.begin(), sums.end());
        return sums.find()
        for (int i = 1; i < sums.size(); i++)
            if (sums[i] == maxsum)
                return i;
        return -1;
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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);

        int maxsumk = -1, maxsum = INT_MIN;
        int k = 1;
        while (q.size()) {
            int size = q.size();
            int sum = 0;
            while (size--) {
                root = q.front(); q.pop();
                sum += root->val;
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            if (sum > maxsum) {
                maxsumk = k;
                maxsum = sum;
            }
            k++;
        }

        return maxsumk;
    }
};
```