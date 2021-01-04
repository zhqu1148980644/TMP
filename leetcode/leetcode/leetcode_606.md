---
title: Construct String from Binary Tree
date: 2021-01-04
---
You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.

#### Solutions

- This problem is coupled with `problem 536`


1. ##### preorder traversal with recursion

```cpp
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
    void encode(TreeNode * root, string & res) {
        if (!root) return;
        res += to_string(root->val);
        if (root->left || root->right) {
            res += "("; encode(root->left, res); res += ")";
        }
        if (root->right) {
            res += "("; encode(root->right, res); res += ")";
        }
    }
    string tree2str(TreeNode* t) {
        string res;
        encode(t, res);
        return res;
    }
};
```

2. ##### postorder traversal with iteration

```cpp
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
    string tree2str(TreeNode* t) {
        TreeNode * root = t;
        stack<TreeNode *> s;

        string res;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                res += to_string(root->val);
                if (root->left)
                    res += "(";
                else if (root->right)
                    res += "()";
                root = root->left;
            }
            root = s.top();
            if (root->right && root->right != t) {
                res += "(";
                root = root->right;
            }
            else {
                t = root;
                s.pop();
                res += ")";
                root = nullptr;
            }
        }
        if (res.size()) res.pop_back();
        return res;
    }
};
```

3. ##### preorder traversal wtih iteration

```cpp


```