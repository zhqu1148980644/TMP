#### Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

```
Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```

#### Solutions


1. ##### recursion

- For a soted array, the `middle node` is supposed to be the `root node` of the whole binary tree, then the middle node of the left part array is the root node of the left subtree and vice versa for the right subtree.

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
    TreeNode * buildRoot(vector<int> & nums, int lo, int hi) {
        if (hi <= lo) return nullptr;
        int mid = lo + ((hi - lo) >> 1);
        TreeNode * root = new TreeNode(nums[mid]);
        root->left = buildRoot(nums, lo, mid);
        root->right = buildRoot(nums, mid + 1, hi);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildRoot(nums, 0, nums.size());
    }
};
```

2. ##### iteration

- The key point is to trasfer the range info when expanding the binary trees.
- Here I used a queue in a bfs style, other data structures or traversal methods works too.

```c++
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        queue<pair<TreeNode *, pair<int, int>>> q;
        if (!nums.size()) return NULL;
        TreeNode * root = new TreeNode(0), * _root = root;
        q.push(make_pair(root, make_pair(0, nums.size())));
        int lo, hi;

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            root = cur.first; 
            lo = cur.second.first, hi = cur.second.second;
            int mid = lo + ((hi - lo) >> 1);
            root->val = nums[mid];
            if (lo < mid) {
                // Since the mid value is still need to be calculated in the next iteration, we choose to set node value in the next iteration.
                root->left = new TreeNode(0);
                q.push(make_pair(root->left, make_pair(lo, mid)));
            }
            if (hi > mid + 1) {
                root->right = new TreeNode(0);
                q.push(make_pair(root->right, make_pair(mid + 1, hi)));
            }
        }
        return _root;
    }
};
```