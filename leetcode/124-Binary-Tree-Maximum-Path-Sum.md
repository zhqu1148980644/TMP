Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

```
Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42
```

#### Solutions

-  Caution: A path does not contain branches.

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
    int maxsum = INT_MIN;

    int maxgain(TreeNode * root) {
        if (!root) return 0;
        int leftgain = maxgain(root->left);
        int rightgain = maxgain(root->right);

        if (root->val + leftgain + rightgain > maxsum)
            maxsum = root->val + leftgain + rightgain;
        // since a path can not contain branches, we choose the maximum one
        int gain = root->val + max(leftgain, rightgain);
        // if the pathsum < 0, no contribution for path passes through the parent node
        return gain > 0 ? gain : 0;
    }

    int maxPathSum(TreeNode* root) {
        maxgain(root);
        return maxsum;
    }
};
```


2. ##### postorder  O(n) S(log(n))

- Replace the system stack with custom stack.
- `cursum` represents the maximum path sum across the current node(not higher than this).
- For a certain root node, as the right child will be the previous visited node, we can use a variable `right` to record the right child's `cursum`, While the left child is not, we instead use a `stack` to store `cursum` of these left children.

```c++
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        stack<TreeNode *> s;
        stack<int> lefts;
        int maxsum = INT_MIN, cursum, left, right;
        cursum = left = right = 0;
        TreeNode * prev = nullptr;

        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != prev) {
                root = root->right;
            }
            else {
                // Codes above are ordinary postorder traversal codes.
                s.pop(); prev = root;
                cursum = root->val;
                if (root->left) {
                    left = lefts.top(); lefts.pop();
                }
                // maximum equals to add them together.
                maxsum = max(maxsum, left + right + cursum);
                // Since a path can not contain branches, we choose the maximum child.
                cursum = cursum + max(left, right);
                if (cursum < 0) cursum = 0;
                left = right = 0;
                // if this node is the right child of parent node, store in right variable, otherwise store in stack.
                if (s.size() && s.top()->right == root)
                    right = cursum;
                else
                    lefts.push(cursum);
                root = nullptr;
            }
        }
        return maxsum;
    }
};
```