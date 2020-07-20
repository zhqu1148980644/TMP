You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

```
Example:

Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   
```

#### Note:

-    There will only be '(', ')', '-' and '0' ~ '9' in the input string.
-    An empty tree is represented by "" instead of "()".

#### Solutions

1. ##### recursion

- After each recursive call, the `lo` pointer will always points to the character next to the right bracket of the subtree.

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
    TreeNode* str2tree(string s) {
        int lo = 0, hi = s.size();
        return buildbst(s, lo, hi);
    }
    TreeNode* buildbst(string & s, int & lo, int & hi) {
        if (lo >= hi)
            return nullptr;
        int sign = 1, num = 0;
        if (s[lo] == '-') {
            sign = -1; lo++;
        }
        while (isdigit(s[lo]))
            num = num * 10 + (s[lo++] - '0');
        TreeNode * root = new TreeNode(num * sign);
        if (s[lo] == '(') {
            root->left = buildbst(s, ++lo, hi);
            if (s[lo] == '(')
                root->right = buildbst(s, ++lo, hi);
        }
        // move lo out of the current subtree
        lo++;
        return root;
    }
};
```


2. ##### iteration with stack

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
    TreeNode* str2tree(string s) {
        if (!s.size())
            return nullptr;
        stack<TreeNode *> st;
        int num = stoi(s), cur = 0, len = s.size();

        TreeNode * root, * head;
        head = root = new TreeNode(num);
        while (cur < len && s[++cur] != '(');
        st.push(root);

        while (cur < len) {
            // s[cur] either be '(' or ')'
            if (s[cur++] == '(') {
                int sign = 1, num = 0;
                if (s[cur] == '-') {
                    sign = -1; cur++;
                }
                while (isdigit(s[cur]))
                    num = num * 10 + (s[cur++] - '0');
                root = new TreeNode(num * sign);
                if (!st.top()->left)
                    st.top()->left = root;
                else
                    st.top()->right = root;
                st.push(root);
            }
            else
                st.pop();
        }

        return head;
    }
};
```