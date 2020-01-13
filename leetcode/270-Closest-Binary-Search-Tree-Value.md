#### Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

#### Note:

-    Given target value is a floating point.
-    You are guaranteed to have only one unique value in the BST that is closest to the target.

```
Example:

Input: root = [4,2,5,1,3], target = 3.714286

    4
   / \
  2   5
 / \
1   3

Output: 4
```

#### Solutions

- The same as binary search.

1. ##### recursion

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
    void dfs(TreeNode* root, double target, double & diff) {
        if (!root) return;
        if (root->val == target) {
            diff = 0;
            return;
        }
        else {
            if (abs(root->val - target) <= abs(diff))
                diff = root->val - target;
            if (target < root->val)
                dfs(root->left, target, diff);
            else
                dfs(root->right, target, diff);
        }
    }
    int closestValue(TreeNode* root, double target) {
        double diff = root->val - target;
        dfs(root, target, diff);
        return target + diff;
    }
};
```

2. ##### iteration

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
    int closestValue(TreeNode* root, double target) {
        double mindiff = root->val - target;
        while (root) {
            if (root->val == target)
                return target;
            if (abs(root->val - target) < abs(mindiff))
                mindiff = root->val - target;
            root = target < root->val ? root->left : root->right;
        }
        return mindiff + target;
    }
};
```

- More elegant approach
- reference: https://leetcode-cn.com/problems/closest-binary-search-tree-value/solution/wei-hu-qu-jian-duan-dian-de-die-dai-xie-fa-by-zjuw/

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
    int closestValue(TreeNode* root, double target) {
        double l, r;
        l = r = root->val;
        while (root) {
            if (target < root->val) {
                r = root->val;
                root = root->left;
            }
            else {
                l = root->val;
                root = root->right;
            }
        }

        return abs(l - target) < abs(r - target) ? l : r;
    }
};
```