#### Given two binary search trees root1 and root2.

Return a list containing all the integers from both trees sorted in ascending order.

 

```
Example 1:


Input: root1 = [2,1,4], root2 = [1,0,3]
Output: [0,1,1,2,3,4]
Example 2:

Input: root1 = [0,-10,10], root2 = [5,1,7,0,2]
Output: [-10,0,0,1,2,5,7,10]
Example 3:

Input: root1 = [], root2 = [5,1,7,0,2]
Output: [0,1,2,5,7]
Example 4:

Input: root1 = [0,-10,10], root2 = []
Output: [-10,0,10]
Example 5:


Input: root1 = [1,null,8], root2 = [8,1]
Output: [1,1,8,8]
```
 

#### Constraints:

- Each tree has at most 5000 nodes.
- Each node's value is between [-10^5, 10^5].

#### Solutions

1. ##### merige when traversing

- Compared to the bst iterator in `probem 173`, a minor change needs to be applied.

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
struct BSTIterator {
    stack<TreeNode *> s;
    BSTIterator(TreeNode * root) {
        goleft(root);
    }
    void goleft(TreeNode * root) {
        while (root) {
            s.push(root);
            root = root->left;
        }
    }
    operator bool() {
        return s.size();
    }
    int operator*() {
        return s.top()->val;
    }
    BSTIterator & operator++() {
        TreeNode * root = s.top(); s.pop();
        goleft(root->right);
        return *this;
    }
};
class Solution {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        BSTIterator it1(root1), it2(root2);
        vector<int> res;
        while (it1 || it2) {
            if (it1 && (!it2 || *it1 <= *it2)) {
                res.push_back(*it1); ++it1;
            }
            else {
                res.push_back(*it2); ++it2;
            }
        }
        return res;
    }
};
```


2. ##### merge after traversal

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
    void dfs(TreeNode * root, vector<int> & v) {
        if (!root) return;
        dfs(root->left, v);
        v.push_back(root->val);
        dfs(root->right, v);
    }
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> v1, v2;
        dfs(root1, v1); dfs(root2, v2);
        vector<int> res(v1.size() + v2.size());
        int i = 0, j = 0, n1 = v1.size(), n2 = v2.size(), w = 0;
        while (w < res.size())
            res[w++] = (i < n1 && (j == n2 || v1[i] <= v2[j])) ? v1[i++] : v2[j++];

        return res;
    }
};
```