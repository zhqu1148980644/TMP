---
title: Serialize and Deserialize Binary Tree
date: 2021-01-04
---
#### Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

```
Example: 

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
```

#### Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

#### Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

#### Solutions

1. ##### preorder traversal with recursion

- Format: Nodes are separated by commas, an empty string between two commas represents a nullptr.

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
class Codec {
public:
    void preorderSe(TreeNode * root, string & res) {
        if (!root)
            res.push_back(',');
        else {
            res += to_string(root->val) + ",";
            preorderSe(root->left, res);
            preorderSe(root->right, res);
        }
    }

    string serialize(TreeNode* root) {
        string res;
        preorderSe(root, res);
        return res;
    }

    int preorderDe(string & data, int i, TreeNode ** root) {
        if (data[i] == ',') {
            *root = nullptr;
            return i + 1;
        }
        else {
            int end = i;
            while (data[end] != ',') end++;
            TreeNode * cur = new TreeNode(stoi(data.substr(i, end - i)));
            *root = cur;
            end = preorderDe(data, end + 1, &(cur->left));
            end = preorderDe(data, end, &(cur->right));
            return end;
        }
    }

    TreeNode* deserialize(string data) {
        TreeNode * root;
        preorderDe(data, 0, &root);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```


or

- After the subtree has been built, the `st` will be at the end comma of the last element in subtree.

```cpp
class Codec {
public:

    void preorderSe(TreeNode * root, string & res) {
        if (!root)
            res.push_back(',');
        else {
            res += to_string(root->val) + ",";
            preorderSe(root->left, res);
            preorderSe(root->right, res);
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        preorderSe(root, res);
        return res;
    }

    TreeNode * preorderDe(string & data, int & st) {
        if (data[st] == ',')
            return nullptr;
        else {
            int len = 0;
            while (data[st] != ',' && ++st) len++;
            TreeNode * root = new TreeNode(stoi(data.substr(st - len, len)));
            root->left = preorderDe(data, ++st);
            root->right = preorderDe(data, ++st);
            return root;
        }
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int st = -1;
        return preorderDe(data, ++st);
    }
};
```

2. ##### levelorder traversal with queue

- The same format as above except the ordering of nodes is replaced by level order.

```cpp
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        string res;
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            if (cur) {
                res += to_string(cur->val) + ",";
                q.push(cur->left);
                q.push(cur->right);
            }
            else
                res.push_back(',');
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (!data.size()) return nullptr;
        int st = 0;
        while (st < data.size() && data[st] != ',')
            st++;
        TreeNode * root, * cur;
        root = cur = new TreeNode(stoi(data.substr(0, st)));

        queue<TreeNode *> q; q.push(root);
        TreeNode ** child[2];

        while (!q.empty() && st < data.size()) {
            int size = q.size();
            while (size--) {
                cur = q.front(); q.pop();
                child[0] = &(cur->left);
                child[1] = &(cur->right);
                for (int i = 0; i < 2; i++) {
                    st++;
                    if (data[st] == ',')
                        *child[i] = nullptr;
                    else {
                        int len = 0;
                        while (st < data.size() && data[st] != ',' && ++len)
                            st++;
                        *child[i] = new TreeNode(stoi(data.substr(st - len, len)));
                        q.push(*child[i]);
                    }
                }
            }
        }
        return root;
    }
};
```


Or

```cpp
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        string res;
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            if (cur) {
                res += to_string(cur->val) + ",";
                q.push(cur->left);
                q.push(cur->right);
            }
            else
                res.push_back(',');
        }
        return res;
    }

    TreeNode* deserialize(string data) {
        if (!data.size()) return nullptr;
        // st is actually the end of the last element, which is a comma
        auto createnode = [&data](int & st) {
            st++; int len = 0;
            while (data[st] != ',' && ++len) st++;
            return len ? new TreeNode(stoi(data.substr(st - len, len))) : nullptr;
        };
        int st = -1;
        queue<TreeNode *> q; TreeNode * root;
        q.push(root = createnode(st));

        while (!q.empty() && st < data.size()) {
            TreeNode * cur = q.front(); q.pop();
            if (cur->left = createnode(st))
                q.push(cur->left);
            if (cur->right = createnode(st))
                q.push(cur->right);
        }
        return root;
    }
};
```