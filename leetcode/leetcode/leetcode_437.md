---
title: Path Sum III
date: 2021-01-04
---
#### You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

```
Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
```

#### Solutions

- Finding the path equals to finding a `contiguous subarray` with the sum equals to the given sum which is done in `problem 560`.

1. ##### Backtracking plus hashmap

- Use a hashmap to record the sum at each node before the current node in the same backtracking path.

```cpp
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
    int count;
    int target;
    unordered_map<int, int> his;

public:
    void dfs(TreeNode * root, int cursum) {
        cursum += root->val;
        if (his.find(cursum - target) != his.end())
            this->count += his[cursum - target];

        his[cursum]++;
        if (root->left)
            dfs(root->left, cursum);
        if (root->right)
            dfs(root->right, cursum);
        his[cursum]--;
    }

    int pathSum(TreeNode* root, int sum) {
        target = sum; his[0]++;
        if (root) dfs(root, 0);
        return count;
    }
};
```

2. ##### iteration with stack plus hashmap

- Similar to problem 113.

```cpp
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
    int pathSum(TreeNode* root, int sum) {
        stack<TreeNode *> s;
        unordered_map<int, int> his; his[0]++;
        int cursum = 0, count = 0;
        TreeNode * prev = NULL;

        while (root || !s.empty()) {
            while (root) {
                cursum += root->val;
                if (his.find(cursum - sum) != his.end())
                    count += his[cursum - sum];
                his[cursum]++;
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != prev)
                root = root->right;
            else {
                // deduce the cursum's count
                // deduce cursum
                prev = root;
                his[cursum]--; s.pop();
                cursum -= root->val;
                root = NULL;
            }
        }
        return count;
    }
};
```