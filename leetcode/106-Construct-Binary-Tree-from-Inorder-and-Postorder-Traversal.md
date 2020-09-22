#### Given inorder and postorder traversal of a tree, construct the binary tree.

#### Note:
You may assume that duplicates do not exist in the tree.

```
For example, given

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
```


#### Solutions

- It's clear hat the reversed version of the postorder traversal is similar to the preorder traversal, except that the right node is visited before the left node. Thus by selecting the root nodes backwards and reversing the visiting order of left/right node, you can apply the same idea/method to this problem as in `problem 105`.
    - preorder: `root left ritght` reversed postorder: `root right left`.

1. ##### recursion


python version

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> TreeNode:
        if not len(postorder):
            return None
        mid = inorder.index(postorder[-1])

        root = TreeNode(postorder[-1])
        root.right = self.buildTree(inorder[mid + 1:], postorder[mid: -1])
        root.left = self.buildTree(inorder[: mid], postorder[: mid])

        return root
```

Or terminate the recursion by delivering the `range` info of inorder sequence and select root nodes by gradually `decreasing` the position of root node in postorder traversal sequence with cooperated `root right left` traversal.

- Notes: the selection of postindex and range is independent of each other, you can use `left-close-right-close` for range and `open` for posindex too.

```c++
class Solution {
    vector<int> postorder;
    unordered_map<int, int> m;
    int posindex;

    TreeNode * build(int start, int end) {
        if (start >= end) return nullptr;
        TreeNode * root = new TreeNode(postorder[posindex]);
        int mid = m[postorder[posindex--]];
        root->right = build(mid + 1, end);
        root->left = build(start, mid);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        posindex = postorder.size() - 1;
        this->postorder = postorder;
        for (int i = 0; i < inorder.size(); i++)
            this->m[inorder[i]] = i;
        return build(0, postorder.size());
    }
};
```


2. ##### recusion without hashmap

- See `problem 105` for detail.

```c++
class Solution {
public:
    int pos, ino;

    TreeNode * postbuild(vector<int> & inorder, vector<int> & postorder, int stop) {
        if (ino < 0 || inorder[ino] == stop)
            return nullptr;
        TreeNode * root = new TreeNode(postorder[pos--]);
        root->right = postbuild(inorder, postorder, root->val);
        ino--;
        root->left = postbuild(inorder, postorder, stop);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        ino = pos = postorder.size() - 1;
        return postbuild(inorder, postorder, INT_MIN);
    }
};
```

3. ##### iteration with stack

- See `problem 105` for details.
- Emulate binary tree traversal in order of `root right left`.(reversed postorder).

```c++
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        stack<TreeNode *> s;
        int ino = postorder.size() - 1, pos = ino;
        TreeNode * head, * root;
        if (postorder.size())
            s.push(root = head = new TreeNode(postorder[pos--]));
        else
            return nullptr;
        while (!s.empty()) {
            while (s.top()->val != inorder[ino]) {
                root = root->right = new TreeNode(postorder[pos--]);
                s.push(root);
            }
            while (!s.empty() && s.top()->val == inorder[ino]) {
                root = s.top(); s.pop();
                ino--;
            }
            if (ino >= 0) {
                root = root->left = new TreeNode(postorder[pos--]);
                s.push(root);
            }
        }

        return head;
    }
};
```