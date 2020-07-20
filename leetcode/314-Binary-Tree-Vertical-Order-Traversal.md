Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples 1:

Input: [3,9,20,null,null,15,7]

   3
  /\
 /  \
 9  20
    /\
   /  \
  15   7 

Output:

[
  [9],
  [3,15],
  [20],
  [7]
]
Examples 2:

Input: [3,9,8,4,0,1,7]

     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7 

Output:

[
  [4],
  [9],
  [3,0,1],
  [8],
  [7]
]
Examples 3:

Input: [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5)

     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2

Output:

[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]

#### Solutions

1. ##### dfs with row and col mark

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
    int mincol = INT_MAX, maxcol = INT_MIN;
    vector<pair<pair<int, int>, int>> v;
    void dfs(TreeNode * root, int c, int r) {
        if (root->left) dfs(root->left, c - 1, r + 1);
        v.emplace_back(make_pair(c, r), root->val);
        if (root->right) dfs(root->right, c + 1, r + 1);
        mincol = min(mincol, c);
        maxcol = max(maxcol, c);
    }
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) return {};
        dfs(root, 0, 0);
        stable_sort(v.begin(), v.end(), [](auto & p1, auto & p2){
            // must be <
            return p1.first < p2.first;
        });
        vector<vector<int>> res(maxcol - mincol + 1);
        for (auto & [p, val] : v)
            res[p.first - mincol].push_back(val);

        return res;
    }
};
```

2. ##### bfs with column mark

```c++
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) return {};
        queue<pair<TreeNode *, int>> q;
        if (root) q.push({root, 0});

        int minc = INT_MAX, maxc = INT_MIN;
        vector<pair<int, int>> v;
        while (!q.empty()) {
            root = q.front().first;
            int c = q.front().second; q.pop();
            if (root->left)
                q.push({root->left, c - 1});
            if (root->right)
                q.push({root->right, c + 1});
            v.push_back({c, root->val});
            minc = min(minc, c); maxc = max(maxc, c);
        }
        stable_sort(v.begin(), v.end(), [&](auto & p1, auto & p2) {
            return p1.first < p2.first;
        });
        vector<vector<int>> res(maxc - minc + 1);
        for (auto & [c, val] : v)
            res[c - minc].push_back(val);
        return res;
    }
};
```