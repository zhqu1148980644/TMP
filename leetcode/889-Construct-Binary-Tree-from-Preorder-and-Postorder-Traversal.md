Return any binary tree that matches the given preorder and postorder traversals.

Values in the traversals pre and post are distinct positive integers.

 

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]
 

Note:

1 <= pre.length == post.length <= 30
pre[] and post[] are both permutations of 1, 2, ..., pre.length.
It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.

#### Solutions

```
                 1
        2                5
    3       4       6         7

- the preorder traversal sequence:   1 234 567
- the postorder traversal sequence:    342 675 1
```

- From the figure above, we have
    - the first node of preorder traversal and the last node of postorder traversal are the root node.
    - the left subtree's length can be fetched by finding the apearance of the root node of the left subtree in sequence of postorder traversal. In this example, the left subtree's root node is `2`.

1. ##### recursion O(n)

- Recursively build tree by directly finding the splitting point.

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
    vector<int> pre, post;
    TreeNode * build(int prei, int posti, int n) {
        if (n <= 0) return nullptr;
        TreeNode * root = new TreeNode(pre[prei]);
        if (n != 1) {
            prei++; n--;
            int nl = 1;
            while (pre[prei] != post[posti + nl - 1]) nl++;
            int nr = n - nl;
            root->left = build(prei, posti, nl);
            root->right = build(prei + nl, posti + nl, nr);
        }
        return root;
    }
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int n = pre.size();
        this->pre = pre; this->post = post;
        return build(0, 0, n);
    }
};
```


or use hasmap to achieve real `O(n)(otherwise it's  nlog(n))` complexity.

```c++
class Solution {
public:
    vector<int> pre, post;
    unordered_map<int, int> pos;
    TreeNode * build(int prei, int posti, int n) {
        if (n <= 0) return nullptr;
        TreeNode * root = new TreeNode(pre[prei]);
        if (n != 1) {
            prei++; n--;
            int nl = pos[pre[prei]] - posti + 1;
            int nr = n - nl;
            root->left = build(prei, posti, nl);
            root->right = build(prei + nl, posti + nl, nr);
        }
        return root;
    }
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        for (int i = 0; i < post.size(); i++)
            pos[post[i]] = i;
        this->pre = pre; this->post = post;
        return build(0, 0, pre.size());
    }
};
```


2. ##### iteration

- Match the reversed preorder traversal sequence with that of the postorder traversal.

```
            1
        2
    3      5
4

reversed preorder: 4 3 2 1 ...
        postorder: 4 3 5

- Reversed preorder traversal sequence will differ with the postorder traversal sequence when we meets a uncompleted tree, ie: with right child. In this case. it's node `2`.
- In other words, whenever the currrent node in `pre` list equals to the index-forwarded postorder node, it represents the current subtree has been built up.

```
- reference: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/discuss/161268/C%2B%2BJavaPython-One-Pass-Real-O(N)

```c++
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        if (!pre.size()) return nullptr;
        TreeNode * root = new TreeNode(pre[0]);
        stack<TreeNode *> s;
        s.push(root);
        for (int i = 1, j = 0; i < pre.size(); i++) {
            while (s.top()->val == post[j])
                s.pop(), j++;
            TreeNode * node = new TreeNode(pre[i]);
            if (!s.top()->left)
                s.top()->left = node;
            else
                s.top()->right = node;
            s.push(node);
        }

        return root;
    }
};
```

3. ##### optimized recursion

- Instead of explicitly specifying the partition points, we can impose restrictions on when should the recursive building process ends and return.
- The idea behind this solution is the same as the previous one.

```c++
class Solution {
public:
    int prei = 0, posti = 0;
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        TreeNode * root = new TreeNode(pre[prei++]);
        if (root->val != post[posti])
            root->left = constructFromPrePost(pre, post);
        if (root->val != post[posti])
            root->right = constructFromPrePost(pre, post);
        posti++;
        return root;
    }
};
```