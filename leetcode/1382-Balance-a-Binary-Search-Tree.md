Given a binary search tree, return a balanced binary search tree with the same node values.

A binary search tree is balanced if and only if the depth of the two subtrees of every node never differ by more than 1.

If there is more than one answer, return any of them.

 

Example 1:

![](https://assets.leetcode.com/uploads/2019/08/22/1515_ex1_out.png)

```
Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2,null,null] is also correct.
```

#### Constraints:

The number of nodes in the tree is between 1 and 10^4.
The tree nodes will have distinct values between 1 and 10^5.


#### Solutions


1. ##### build tree from inorder traversal sequence


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
    vector<int> nodes;
    void dfs(TreeNode * root) {
        if (!root) return;
        dfs(root->left);
        nodes.push_back(root->val);
        dfs(root->right);
    }
    TreeNode * buildBst(int lo, int hi) {
        if (lo > hi) return nullptr;
        int mid = lo + ((hi - lo) >> 1);
        TreeNode * root = new TreeNode(nodes[mid]);
        root->left = buildBst(lo, mid - 1);
        root->right = buildBst(mid + 1, hi);
        return root;
    }
    TreeNode* balanceBST(TreeNode* root) {
        dfs(root);
        return buildBst(0, (int)nodes.size() - 1);
    }
};
```