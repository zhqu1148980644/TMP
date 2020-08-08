Given a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only 1 right child.

Example 1:
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \ 
1        7   9

Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9  
 

Constraints:

The number of nodes in the given tree will be between 1 and 100.
Each node will have a unique integer value from 0 to 1000.

#### Solutions

1. ##### inorder traversal with recursion

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
    TreeNode * prev = nullptr, * head = nullptr;
    TreeNode * inorder(TreeNode * root) {
        if (!root) return nullptr;
        inorder(root->left);
        root->left = nullptr;
        if (prev) prev->right = root;
        if (!head) head = root;
        prev = root;
        inorder(root->right);
        return head;
    }
    TreeNode* increasingBST(TreeNode* root) {
       return inorder(root); 
    }
};
```

2. ##### stack

```c++
class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode * prev = nullptr, * head = nullptr;
        stack<TreeNode *> s;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top(); s.pop();
            if (!head) head = root;
            if (prev) prev->right = root;
            prev = root;
            root->left = nullptr;
            root = root->right;
        }

        return head;
    }
};
```

3. ##### morris

- Caution: don't set the right child back to null as in ordinary morris traversal.

```c++
class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode * prev = nullptr, * head = nullptr, * rdeep;
        while (root) {
            if (root->left) {
                rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right != root) {
                    rdeep->right = root;
                    root = root->left;
                    continue;
                }
            }
            if (!head) head = root;
            if (prev) prev->right = root;
            prev = root;
            root->left = nullptr;
            root = root->right;
        }

        return head;
    }
};
```