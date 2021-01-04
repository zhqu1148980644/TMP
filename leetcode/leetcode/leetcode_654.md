---
title: Maximum Binary Tree
date: 2021-01-04
---
Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].

#### Solutions

1. ##### recursion  worst O(n2) avg O(nlog(n))

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
    template <typename It>
    TreeNode * build(It lo, It hi) {
        if (lo >= hi)
            return nullptr;
        auto maxit = max_element(lo, hi);
        TreeNode * root = new TreeNode(*maxit);
        root->left = build(lo, maxit);
        root->right = build(maxit + 1, hi);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return build(nums.begin(), nums.end());
    }
};
```


2. ##### mono stack O(n)

- monotonically decreasing stack.

```cpp
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        nums.push_back(INT_MAX);
        stack<TreeNode *> s;

        // 3 2 1 6 0 5
        for (auto n : nums) {
            TreeNode * cur = new TreeNode(n);
            while (!s.empty() && s.top()->val < n) {
                TreeNode * mid = s.top(); s.pop();
                // s: 6 0:    5   5 < 6, thus 0 is the left child of 5
                if (s.empty() || s.top()->val > n)
                    cur->left = mid;
                else
                    // s: 3 2 1:   6    2 < 6, thus 1 is the right child of 2
                    s.top()->right = mid;
            }
            s.push(cur);
        }
        
        return s.top()->left;
    }
};
```


3. ##### insertion O(n)

- reference: https://leetcode-cn.com/problems/maximum-binary-tree/solution/jian-ji-dai-ma-bu-di-gui-bu-dui-lie-huo-zhe-zhan-y/
- Maintain a maximum tree while building.
    - If the current number is bigger than the root node of the maximum tree, simply link this tree as the `right child`.
    - Else, traversing ``deep right unitll find a node(or nullnode) with value smaller than the current number, link the smaller subtree as the `left child` to form a new maximum tree, then link this maximum tree at the deepmost right child.
        - Why link as left child ? Because they are visited before and their values are smaller than the current number.

```cpp
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        TreeNode dummy;
        
        
        for (auto n : nums) {
            TreeNode * cur = new TreeNode(n);
            TreeNode * parent = &dummy, * rchild = dummy.right;
            while (rchild && rchild->val > n) {
                parent = rchild;
                rchild = rchild->right;
            }
            cur->left = rchild;
            parent->right = cur;
        }

        return dummy.right;
    }
};
```