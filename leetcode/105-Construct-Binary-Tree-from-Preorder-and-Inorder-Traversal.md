#### Given preorder and inorder traversal of a tree, construct the binary tree.

#### Note:
You may assume that duplicates do not exist in the tree.

```
For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
```

#### Solutions

1. ##### recursion with range

- As the root node is the first node visited in preorder traversal, then for each preorder array, the first element represents the root node of the binary search tree. After finding out the root node, which part of the array belongs to the left subtree/right tree?
- As the sequence of inorder traversal is in ascending order, and the left subtree is always smaller than the right subtree in a binary search tree, we can split the inorder traversal sequence into two parts demarcated by the root node. The root node come from preorder sequence mentioned before.
    - Knowning the partion point of the inorder traversal sequence, it's easy to get the length of the left subtree/right subtree. ie: the length of the left/right subarray.
    - Suppose the length of left subarray is `l`, then left tree in preorder traversal sequence is `preorder[1: 1 + l]` and `preorder[1 + l:]` for right subtree.
- In each step we can find the `root node`, nodes in preorder's head part that belongs to the `left subtree`, nodes in preorder's tail part that belongs to the `right subtree`. It's clear that this problem can be solved by a recursive approach.


- image reference: https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solution/c-tu-jie-guo-cheng-by-aris-7/
![](https://pic.leetcode-cn.com/46d519bf7e567485e76c373851318c871fe36b15a7957e7fc4d992b0a7e3c570-1566200965090.png)

Python code directly expressed this idea.

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        if len(preorder) == 0:
            return None
        mid = inorder.index(preorder[0])
        root = TreeNode(preorder[0])
        root.left = self.buildTree(preorder[1: mid + 1], inorder[:mid])
        root.right = self.buildTree(preorder[mid + 1:], inorder[mid + 1:])
        return root
```

- Since the building process is actually a `preorder` traversal, we can simply increment `pre` to get root nodes in the recursion process.
- `left` and `right` are used to terminate the recursion. i.e. finding out which part of the subarray in `preorder` belongs to the left/right subtree.

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
    vector<int>  preorder;
    vector<int> inorder;
    unordered_map<int, int> m;
    int preidx = 0;

public:

    TreeNode * build(int left, int right) {
        if (left == right)
            return NULL;
        int rootval = preorder[preidx];
        TreeNode * root = new TreeNode(rootval);

        preidx++;
        root->left = build(left, m[rootval]);
        root->right = build(m[rootval] + 1, right);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        this->preorder = preorder;
        this->inorder = inorder;

        int index = 0;
        for (auto & item : inorder)
            m[item] = index++;

        return build(0, inorder.size());
    }
};
```


2. ##### optimized recursion with no hashmap

- borrowed from stephan
- reference: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/discuss/34543/Simple-O(n)-without-map
- Instead of explicitly specifying the range of nodes, he uses a stop marker to terminate the recursive call.
    - For left child tree, the stop marker is the root's value.
    - For right child tree, the stop marker is the stop marker received as parameter from the parent call.
- It's hard to proof the correctness of this method, however, I successfully applied the same method described here to recover the binary tree from postorder and preorder traversal.

```c++
class Solution {
    vector<int> * preorder;
    vector<int> * inorder;
    unordered_map<int, int> m;
    int preindex = 0;
    int inindex = 0;

public:

    TreeNode * build(int stop) {
        if (inindex >= inorder->size() || (*inorder)[inindex] == stop)
            return nullptr;
        else {
            TreeNode * root = new TreeNode((*preorder)[preindex++]);
            root->left = build(root->val);
            inindex++;
            root->right = build(stop);
            return root;
        }
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        this->preorder = &preorder;
        this->inorder = &inorder;

        return build(INT_MAX);
    }
};
```

3. ##### iteration version

- reference: comments in https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/discuss/34555/The-iterative-solution-is-easier-than-you-think!

- The idea is to emulate the preorder traversal process by matching the visiting path to the given preorder traversal sequence. Think of how to traverse the binary tree in preorder:
    - Go to the left most leaf by iteratively building the root/left node.
    - Go backwards to find the father's right child.
    - The preorder traversal offers us the root node sequence in preorder.
    - The inorder traversal tells us which node is the end of the left subtree.
        - The preorder and inorder differs when inorder meets a right child if we traverse backwards from the left most leaf node.
        - When this happens, then the disagreed node in preorder sequence is the the right child of the previous node.

```c++
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) return nullptr;
        stack<TreeNode *> s;
        TreeNode * root = new TreeNode(preorder[0]), * head = root;
        s.push(root);

        int pre = 1, ino = 0;
        while (!s.empty()) {
            // when s.top()->val == inorder[ino]
            // we are at the left most leaf node of the current root node.
            while (s.top()->val != inorder[ino]) {
                root = root->left = new TreeNode(preorder[pre++]);
                s.push(root);
            }
            // Go back, till we find the first right child ie: inorder[ino]
            // This can be happened in both left tree or right tree.
            // when s is empty, we are at the root node of the whole tree.
            while (!s.empty() && s.top()->val == inorder[ino]) {
                root = s.top(); s.pop();
                ino++;
            }
            // link this right child as her father's right child.
            // Note: inorder[ino] doesn't equal to preorder[pre].
            // inorder[ino] is the successor of the inorder[ino - 1] which is the left most leaf node of preorder[pre].
            if (pre < preorder.size()) {
                root = root->right = new TreeNode(preorder[pre++]);
                s.push(root);
            }
            // we are will go into this right child's tree in the next iteration.
        }
        return head;
    }
};

```