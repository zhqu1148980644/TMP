---
title: Number of Enclaves
date: 2021-01-04
---
Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)

A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.

Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves.

 

Example 1:

Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation: 
There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
Example 2:

Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation: 
All 1s are either on the boundary or can reach the boundary.
 

Note:

1 <= A.length <= 500
1 <= A[i].length <= 500
0 <= A[i][j] <= 1
All rows have the same size.

#### Solutions

1. ##### Union Find

- Merge iall islands connected with border with a virtual border node.

```cpp
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        return nodes[node] == node 
            ? node : (nodes[node] = find(nodes[node]));
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        sizes[f2] += sizes[f1];
        nodes[f1] = f2;
        return true;
    }
};
class Solution {
public:
#define node(x, y) ((x) * n + (y))
    int numEnclaves(vector<vector<int>>& A) {
        int m = A.size(), n = A[0].size();
        UnionFind uf(m * n + 1);
        int border = m * n;

        int numland = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (!A[i][j]) continue;
                numland++;
                int cur = node(i, j);
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                    uf.merge(cur, border);
                if (i + 1 < m && A[i + 1][j])
                    uf.merge(cur, node(i + 1, j));
                if (j + 1 < n && A[i][j + 1])
                    uf.merge(cur, node(i, j + 1));
            }
        // border has size 1, numland - (bordersize - 1)
        return numland - uf.sizes[uf.find(border)] + 1;
    }
};
```

2. ##### dfs

- bfs works too.

```cpp
class Solution {
public:
    int m, n;
    void dfs(vector<vector<int>> & A, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n || A[i][j] != 1)
            return;
        A[i][j] = 2;
        dfs(A, i + 1, j);
        dfs(A, i, j + 1);
        dfs(A, i - 1, j);
        dfs(A, i, j - 1);
    }
    int numEnclaves(vector<vector<int>>& A) {
        m = A.size(), n = A[0].size();
        for (int i = 0; i < m; i++) {
            dfs(A, i, 0);
            dfs(A, i, n - 1);
        }
        for (int j = 0; j < n; j++) {
            dfs(A, 0, j);
            dfs(A, m - 1, j);   
        }

        int isolate = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                isolate += A[i][j] == 1;

        return isolate;
    }
};
```