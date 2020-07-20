##### Given a binary tree, flatten it to a linked list in-place.

```
For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

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
```

#### Solutions

- Notice: Must set every node's `left` child to `NULL`;

1. ##### preorder traversal

- It's clear that nodes from the top left to the lower right in the flattened tree follow a preorder traversal order. Thus we can use a `prev` pointer to record the previous visited node and set `it's` right child to the  current node when traversing the tree in preorder.
- Do not forget to store the right child before flattening the left child tree as the right pointer will be pointed to the left child tree when the function returned.

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
    TreeNode * head = nullptr;

    void flatten(TreeNode* root) {
        if(!root) return;
        if (!head) head = root;
        else {
            head->left = nullptr;
            head->right = root;
            head = head->right;
        }
        TreeNode * right = root->right;
        flatten(root->left);
        flatten(right);
    }
};
```

- iteration with morris
- in the original morris method, whenever we come back to he root node, we always have to search for the rightmost child in the left child tree. In the meantime, we can link the flattened left tree as the root node's right child and link this right child to the tail of the flattened left tree.

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode * r = root;
        while (root) {
            if (root->left) {
                TreeNode * rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                if (rdeep->right != root) {
                    rdeep->right = root;
                    root = root->left;
                } else {
                    rdeep->right = root->right;
                    root->right = root->left;
                    root->left = nullptr;
                    root = rdeep->right;
                }
            } else
                root = root->right;
        }
    }
};
```

- More concise version
- reference: https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--26/
- Remove the `if-else` expression in the previous version.

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode * r = root;
        while (root) {
            if (root->left) {
                TreeNode * rdeep = root->left;
                while (rdeep->right && rdeep->right != root)
                    rdeep = rdeep->right;
                rdeep->right = root->right;
                root->right = root->left;
                root->left = nullptr;
            }
            // always go to the right child.
            root = root->right;
        }
    }
};
```


2. ##### postorder traversal

- Reverse of the flattened sequence is the same as (reversed version)post traversal sequence.
- recursion `left right root`
- In preorder mode, the father's right child will be modified when returned from the function call.
- We can use postorder traversal to prevent this modification though with additional cost in finding the right most child in a flattened tree.

Recursive version.

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        flatten(root->left);
        flatten(root->right);
        TreeNode * right = root->right;
        root->right = root->left;
        root->left = nullptr;
        while (root->right)
            root = root->right;
        root->right = right;
    }
};
```

- recursion `right left root`
- borrowed from others
- This method is totally a reversed version of the first solution.
- The iead is to reverse the traversal order to `right left root`, this can be seen as a bottom-up approach.
- Use a `last` pointer to represent the visited node in the returned function.

```c++
class Solution {
public:
    TreeNode * last = nullptr;
    void flatten(TreeNode* root) {
        if (root) {
            flatten(root->right);
            flatten(root->left);
            root->right = last;
            root->left = nullptr;
            last = root;
        }
    }
};
```

- Iteration with stack `right left root`

```c++
class Solution {
public:
    void flatten(TreeNode* root) {
        stack<TreeNode *> s;
        TreeNode * prev = nullptr;

        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->right;
            }
            root = s.top();
            if (root->left && root->left != prev)
                root = root->left;
            else {
                root->right = prev;
                root->left = nullptr;
                prev = root;
                root = nullptr;
                s.pop();
            }
        }
    }
};
```