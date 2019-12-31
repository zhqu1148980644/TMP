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
        gotoLeft(root);
    }

    TreeNode * next() {
        return s.top();
    }

    void gotoLeft(TreeNode * root) {
        while (root) {
            s.push(root);
            root = root->left;
        }
    }
    void toNext() {
        auto root = s.top(); s.pop();
        gotoLeft(root->right);
    }

    bool hasNext() {
        return !s.empty();
    }
};

class Solution {
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        BSTIterator bsi1(root1);
        BSTIterator bsi2(root2);
        vector<int> res;

        while (bsi1.hasNext() && bsi2.hasNext()) {
            if (bsi1.next()->val <= bsi2.next()->val) {
                res.push_back(bsi1.next()->val);
                bsi1.toNext();
            } else {
                res.push_back(bsi2.next()->val);
                bsi2.toNext();
            }
        }

        while (bsi1.hasNext()) {
            res.push_back(bsi1.next()->val);
            bsi1.toNext();
        }
        while (bsi2.hasNext()) {
            res.push_back(bsi2.next()->val);
            bsi2.toNext();
        }

        return res;
    }

};
```


2. ##### merge after traversal

```c++
class Solution {
    void dfs(vector<int> & vec, TreeNode * root) {
        if (!root) return;
        dfs(vec, root->left);
        vec.push_back(root->val);
        dfs(vec, root->right);
    }
public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> vec1;
        vector<int> vec2;
        dfs(vec1, root1);
        dfs(vec2, root2);
        vector<int> res;

        int i = 0, j = 0;
        while (i < vec1.size() && j < vec2.size()) {
            if (vec1[i] <= vec2[j])
                res.push_back(vec1[i++]);
            else
                res.push_back(vec2[j++]);
        }
        while (i < vec1.size())
            res.push_back(vec1[i++]);
        while (j < vec2.size())
            res.push_back(vec2[j++]);
        return res;
    }
};
```