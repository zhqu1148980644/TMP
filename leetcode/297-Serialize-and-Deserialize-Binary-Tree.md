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

2. ##### levelorder traversal with queue

- The same format as above.

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
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode *> q;
        if (root) q.push(root);
        string res;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto cur = q.front(); q.pop();
                if (cur) {
                    res += to_string(cur->val) + ",";
                    q.push(cur->left);
                    q.push(cur->right);
                }
                else
                    res.push_back(',');
            }
        }
        cout << res << endl;
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (!data.size()) return nullptr;
        int start = 0;
        while (start < data.size() && data[start] != ',')
            start++;
        TreeNode * root, * cur;
        root = cur = new TreeNode(stoi(data.substr(0, start)));

        queue<TreeNode *> q;
        q.push(root);
        start++;
        TreeNode ** child[2];

        while (!q.empty() && start < data.size()) {
            int size = q.size();
            while (size--) {
                cur = q.front(); q.pop();
                child[0] = &(cur->left);
                child[1] = &(cur->right);
                for (int i = 0; i < 2; i++) {
                    if (data[start] == ',')
                        *child[i] = nullptr;
                    else {
                        int pre = start;
                        while (start < data.size() && data[start] != ',')
                            start++;
                        *child[i] = new TreeNode(stoi(data.substr(pre, start - pre)));
                        q.push(*child[i]);
                    }
                    start++;
                }
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```