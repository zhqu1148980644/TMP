A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.

Write a data structure CBTInserter that is initialized with a complete binary tree and supports the following operations:

CBTInserter(TreeNode root) initializes the data structure on a given tree with head node root;
CBTInserter.insert(int v) will insert a TreeNode into the tree with value node.val = v so that the tree remains complete, and returns the value of the parent of the inserted TreeNode;
CBTInserter.get_root() will return the head node of the tree.
 

Example 1:

Input: inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
Output: [null,1,[1,2]]
Example 2:

Input: inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
Output: [null,3,4,[1,2,3,4,5,6,7,8]]
 

Note:

The initial given tree is complete and contains between 1 and 1000 nodes.
CBTInserter.insert is called at most 10000 times per test case.
Every value of a given or inserted node is between 0 and 5000.

#### Solutions

1. ##### level order traversal

- Store all nodes in the last full(with size it should be) level.

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
class CBTInserter {
public:
    int cur = -1;
    TreeNode * root;
    vector<TreeNode *> level;
    CBTInserter(TreeNode* root) : root(root) {
        if (!root) return;
        queue<TreeNode *> q;
        q.push(root);

        while (q.size()) {
            level.clear();
            int size = q.size(), index = 0;
            while (size--) {
                root = q.front(); q.pop();
                level.push_back(root);
                if (cur != -1) continue;
                if (!root->left || !root->right)
                    cur = index;
                else {
                    q.push(root->left);
                    q.push(root->right);
                }
                index++;
            }
            if (cur != -1) break;
        }
    }
    
    int insert(int v) {
        TreeNode * parent = level[cur];
        if (!parent->left)
            parent->left = new TreeNode(v);
        else {
            parent->right = new TreeNode(v);
            if (++cur == level.size()) {
                vector<TreeNode *> parents;
                swap(parents, level);
                for (auto p : parents) {
                    level.push_back(p->left);
                    level.push_back(p->right);
                }
                cur = 0;
            }
        }
        return parent->val;
    }
    
    TreeNode* get_root() {
        return root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
```

2. ##### deque

- borrowed from the official answer.
- In this version, only uncompleted nodes would be stored and the front of deque is the first parent node needs to be filled.


```c++
class CBTInserter {
public:
    TreeNode * root;
    deque<TreeNode *> parents;
    CBTInserter(TreeNode* root) : root(root) {
        if (!root) return;
        queue<TreeNode *> q; q.push(root);
        while (!q.empty()) {
            root = q.front(); q.pop();
            if (!root->left || !root->right)
                parents.push_back(root);
            if (root->left) q.push(root->left);
            if (root->right) q.push(root->right);
        }
    }
    
    int insert(int v) {
        auto parent = parents.front();
        auto child = new TreeNode(v);
        if (!parent->left)
            parent->left = child;
        else {
            parent->right = child;
            parents.pop_front();
        }
        parents.push_back(child);

        return parent->val;
    }
    
    TreeNode* get_root() {
        return root;
    }
};
```