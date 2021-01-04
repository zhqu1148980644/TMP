---
title: All Nodes Distance K in Binary Tree
date: 2021-01-04
---
We are given a binary tree (with root node root), a target node, and an integer value K.

Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.

 

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

Output: [7,4,1]

Explanation: 
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.



Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.
 

Note:

The given tree is non-empty.
Each node in the tree has unique values 0 <= node.val <= 500.
The target node is a node in the tree.
0 <= K <= 1000.

#### Solutions

1. ##### postorder traversal with recursion O(n) S(log(n))

- Use postorder traversal to record the distance between the target node and it's ascendant nodes.
- Then dfs starting with the target's descendants(include itself).

```cpp
class Solution {
public:
    vector<int> res;
    unordered_map<TreeNode *, int> path;

    void distancek(TreeNode * root, int K) {
        if (!root) return;
        if (K == 0)
            res.push_back(root->val);
        else {
            TreeNode * l = root->left, * r = root->right;
            if (l && !path.count(l)) distancek(l, K - 1);
            if (r && !path.count(r)) distancek(r, K - 1);
        }
    }
    void build_path(TreeNode * root, TreeNode * & target, int & dis, int hi) {
        if (!root) return;
        // when the current node is the target, start setting distance backwards
        if (root == target) target = nullptr;
        if (target && dis <= hi) build_path(root->left, target, dis, hi);
        if (target && dis <= hi) build_path(root->right, target, dis, hi);
        if (!target) path[root] = dis++;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        int dis = 0;
        TreeNode * stopnode = target;
        build_path(root, stopnode, dis, K);

        // dfs self
        distancek(target, K);
        // dfs ascendants
        for (auto [pnode, dis] : path)
            if (pnode != target)
                distancek(pnode, K - dis);
    
        return res;
    }
};
```

or simplified version

```cpp
class Solution {
public:
    vector<int> res;
    TreeNode * prev = nullptr;
    void findk(TreeNode * root, int K) {
        if (!root || prev == root) return;
        if (K == 0)
            res.push_back(root->val);
        else {
            findk(root->left, K - 1);
            findk(root->right, K - 1);
        }
    }
    int build_path(TreeNode * root, TreeNode * target, int K) {
        if (!root) return INT_MIN;
        int dis = root == target ? -1 : INT_MIN;
        if (dis == INT_MIN) dis = build_path(root->left, target, K);
        if (dis == INT_MIN) dis = build_path(root->right, target, K);
        if (dis != INT_MIN && dis <= K) {
            findk(root, K - ++dis);
            prev = root;
        }
        return dis;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        build_path(root, target, K);
        return res;
    }
};
```

2. ##### bfs with parents links O(n)

- Use hashmap to record each node's parent node.
- Then bfs search each node's left/right/parent node.

```cpp
class Solution {
public:
    unordered_map<TreeNode *, TreeNode *> parents;
    void dfs(TreeNode * root, TreeNode * & target, TreeNode * parent) {
        if (!root) return;
        if (root == target)
            target = nullptr;
        if (target) dfs(root->left, target, root);
        if (target) dfs(root->right, target, root);
        if (!target && parent) parents[root] = parent;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        TreeNode * stopnode = target;
        dfs(root, stopnode, nullptr);
        
        vector<int> res;
        unordered_set<TreeNode *> seen;
        seen.insert(target);
        queue<TreeNode *> q;
        q.push(target);
        K++;
        while (!q.empty() && K--) {
            int size = q.size();
            while (size--) {
                auto node = q.front(); q.pop();
                if (!K) res.push_back(node->val);
                if (K && parents.count(node)) {
                    q.push(parents[node]);
                    seen.insert(parents[node]);
                }
                if (K && node->left && !seen.count(node->left)) {
                    q.push(node->left);
                    seen.insert(node->left);
                }
                if (K && node->right && !seen.count(node->right)) {
                    q.push(node->right);
                    seen.insert(node->left);
                }
            }
        }
        return res;
    }
};
```


3. ##### map nodes to indexes in complete binary tree O(nlog(n)) S(n)

- reference: https://leetcode-cn.com/problems/all-nodes-distance-k-in-binary-tree/solution/c-zuo-biao-hua-chu-li-by-da-li-wang/

```cpp
class Solution {
public:
    unordered_map<TreeNode *, long long> index;
    void dfs(TreeNode * root, long long i) {
        if (!root) return;
        index[root] = i;
        dfs(root->left, 2 * i + 1);
        dfs(root->right, 2 * i + 2);
    }
    int dis(int i1, int i2) {
        int res = 0;
        // move the lower one upward.
        while (i1 != i2) {
            if (i1 > i2)
                i1 = (i1 - 1) / 2;
            else
                i2 = (i2 - 1) / 2;
            res++;
        }
        return res;
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        dfs(root, 0);
        vector<int> res;
        int ti = index[target];
        for (auto [node, si] : index)
            if (dis(si, ti) == K)
                res.push_back(node->val);

        return res;
    }
};
```

- Another similar method: https://leetcode-cn.com/problems/all-nodes-distance-k-in-binary-tree/solution/javajiang-zheng-ke-shu-bian-ma-zhi-hou-jin-xing-ch/