Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.

A node is deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is that node, plus the set of all descendants of that node.

Return the node with the largest depth such that it contains all the deepest nodes in its subtree.

 

Example 1:

Input: [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation:



We return the node with value 2, colored in yellow in the diagram.
The nodes colored in blue are the deepest nodes of the tree.
The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
Both the input and output have TreeNode type.
 

Note:

The number of nodes in the tree will be between 1 and 500.
The values of each node are unique.

#### Solutions

1. ##### postorder traversal with recursion

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
    TreeNode * res = nullptr;
    int maxdep = INT_MIN;
    int deepest(TreeNode * root, int depth = 0) {
        if (!root) return depth - 1;
        int l = deepest(root->left, depth + 1);
        int r = deepest(root->right, depth + 1);
        int curmaxd = max(l, r);
        // two cases need to update node
        // 1. self is the maximum depth node
        // 2. both left and right child hash the maximum depth
        if (curmaxd > maxdep || (l == r && l == maxdep)) {
            res = root;
            maxdep = curmaxd;
        }
        return curmaxd;
    }
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (root) deepest(root, 0);
        return res;
    }
};
```