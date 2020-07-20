Given two binary trees and imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not.

You need to merge them into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of new tree.

Example 1:

Input: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
Output: 
Merged tree:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7
 

Note: The merging process must start from the root nodes of both trees.

#### Solutions

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
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1 || !t2)
            return t1 ? t1 : t2;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }
};
```


2. ##### iteration

```c++
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1 || !t2) return t1 ? t1 : t2;
        TreeNode * root = t1;
        stack<TreeNode *> s1, s2;
        t1->val += t2->val;
        s1.push(t1); s2.push(t2);

        while (!s1.empty()) {
            while (t1) {
                if (t1->right && t2->right) {
                    t1->right->val += t2->right->val;
                    s1.push(t1->right); s2.push(t2->right);
                }
                else
                    t1->right = t1->right ? t1->right : t2->right;
                if (t1->left && t2->left) {
                    t1->left->val += t2->left->val;
                    t1 = t1->left, t2 = t2->left;
                }
                else {
                    t1->left = t1->left ? t1->left : t2->left;
                    t1 = nullptr;
                }
            }
            t1 = s1.top(); s1.pop();
            t2 = s2.top(); s2.pop();
        }
        return root;
    }
};
```