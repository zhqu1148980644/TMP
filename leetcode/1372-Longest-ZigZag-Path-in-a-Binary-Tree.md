Given a binary tree root, a ZigZag path for a binary tree is defined as follow:

Choose any node in the binary tree and a direction (right or left).
If the current direction is right then move to the right child of the current node otherwise move to the left child.
Change the direction from right to left or right to left.
Repeat the second and third step until you can't move in the tree.
Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).

Return the longest ZigZag path contained in that tree.

 


Example 1:

![](https://assets.leetcode.com/uploads/2020/01/22/sample_1_1702.png)
```
Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
Output: 3
Explanation: Longest ZigZag path in blue nodes (right -> left -> right).
```

Example 2:

![](https://assets.leetcode.com/uploads/2020/01/22/sample_2_1702.png)
```
Input: root = [1,1,1,null,1,null,null,1,1,null,1]
Output: 4
Explanation: Longest ZigZag path in blue nodes (left -> right -> left -> right).
Example 3:

Input: root = [1]
Output: 0
```
 

##### Constraints:

- Each tree has at most 50000 nodes..
- Each node's value is between [1, 100].


#### Solutions

1. ##### postorder traversal with recursion

- The idea is similar to dynamic programming while the maximum zigzag length of parent nodes can be calculated based on that of children nodes.

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
    pair<int, int> dfs(TreeNode * root) {
        if (!root) return {-1, -1};
        auto [ll, lr] = dfs(root->left);
        auto [rl, rr] = dfs(root->right);
        pair<int, int> cur {lr + 1, rl + 1};
        res = max(res, max(cur.first, cur.second));
        return cur;
    }
    int longestZigZag(TreeNode* root) {
        dfs(root);
        return res;
    }
};
```