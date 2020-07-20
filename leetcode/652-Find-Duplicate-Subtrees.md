Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1:

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:

      2
     /
    4
and

    4
Therefore, you need to return above trees' root in the form of a list.

#### Solutions

- Similar to `problem 572`

1. ##### postorder traversal with hash map

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode *> res;
    unordered_map<string, TreeNode *> m;
    string dfs(TreeNode * root) {
        if (!root) return "#";
        string lkey = dfs(root->left);
        string rkey = dfs(root->right);
        string key = to_string(root->val) + "," + lkey + "," + rkey;
        if (m.count(key)) {
            if (!m[key]) {
                m[key] = root;
                res.push_back(root);
            }
        }
        else
            m[key] = nullptr;
        return key; 
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        return res;
    }
};
```

or with custom hash key

```c++
class Solution {
public:
    unordered_map<size_t, TreeNode *> m;
    vector<TreeNode *> res;
    hash<string> hasher;
    char buff[100];

    size_t hash(TreeNode * root) {
        if (!root) return 1;
        auto hl = hash(root->left);
        auto hr = hash(root->right);
        sprintf(buff, "%d,%d|%d", root->val, hl, hr);
        size_t h = hasher(buff);
        if (m.count(h)) {
            if (!m[h])
                res.push_back(m[h] = root);
        }
        else
            m[h] = nullptr;
        return h;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        if (!root) return {};
        hash(root);
        return res;
    }
};
```