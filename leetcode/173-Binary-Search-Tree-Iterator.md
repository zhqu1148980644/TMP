#### Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

 


#### Example:

![](https://assets.leetcode.com/uploads/2018/12/25/bst-tree.png)

```
BSTIterator iterator = new BSTIterator(root);
iterator.next();    // return 3
iterator.next();    // return 7
iterator.hasNext(); // return true
iterator.next();    // return 9
iterator.hasNext(); // return true
iterator.next();    // return 15
iterator.hasNext(); // return true
iterator.next();    // return 20
iterator.hasNext(); // return false
```
 

#### Note:

- next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
- You may assume that next() call will always be valid, that is, there will be at least a next smallest number in the BST when next() is called.


#### Solutions

1. ##### inorder traversal with stack

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
class BSTIterator {
private:
    stack<TreeNode *> s;
    TreeNode * cur;

public:
    BSTIterator(TreeNode* root) {
        cur = root;
    }

    /** @return the next smallest number */
    int next() {
        while (cur) {// go deep left
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top(); s.pop();
        int res = cur->val;
        cur = cur->right;
        return res;
    }
    /*  the same
    BSTIterator(TreeNode * root) {
        goleft(root);
    }
    int next() {
        cur = s.top(); s.pop();
        goleft(cur->right)
        return cur->val;
    }
    */

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty() || cur;
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```
