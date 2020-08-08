Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.

In one move, we may choose two adjacent nodes and move one coin from one node to another.  (The move may be from parent to child, or from child to parent.)

Return the number of moves required to make every node have exactly one coin.

 

Example 1:



Input: [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.
Example 2:



Input: [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root [taking two moves].  Then, we move one coin from the root of the tree to the right child.
Example 3:



Input: [1,0,2]
Output: 2
Example 4:



Input: [1,0,0,null,3]
Output: 4
 

Note:

1<= N <= 100
0 <= node.val <= N

#### Solutions

1. ##### greedy

- From the official answer
- Counting the number of coins need(overload) for each node from leafs to root.
    - `overload > 0` means there are redundant coins in child node. `overload < 0` means the child node is short of coins.
    - When the `sum of absolute overloads` in chidren is larger than 1, these number of coins must be `passed over` the current node either from parent to children or reveresly. Then the final sum is the sum of these nonzero overloads(absolute sum).

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
    int res = 0;
    int dfs(TreeNode * root) {
        if (!root) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        // if l + r != 0, there must be abs(l) + abs(r) coins will pass by this node
        res += abs(l) + abs(r);
        // deduce self
        return l + r + root->val - 1;
    }
    int distributeCoins(TreeNode* root) {
        dfs(root);
        return res;
    }
};
```