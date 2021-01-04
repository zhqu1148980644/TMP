---
title: Detect Cycles in 2D Gri
date: 2021-01-04
---
Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

Return true if any cycle of the same value exists in grid, otherwise, return false.

 

Example 1:



Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
Output: true
Explanation: There are two valid cycles shown in different colors in the image below:

Example 2:



Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
Output: true
Explanation: There is only one valid cycle highlighted in the image below:

Example 3:



Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
Output: false
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m <= 500
1 <= n <= 500
grid consists only of lowercase English letters.


#### Solutions

1. ##### graph cycle

- check if threre exists a cycle in the graph with each cell treated as a node and four directions as edges.

```cpp
class Solution {
public:
#define node(x, y) ((x) * n + (y))
    int m, n;
    vector<char> g;
    vector<vector<bool>> memo;
    int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    bool dfs(vector<vector<char>> & grid, int x, int y, int prev) {
        if (memo[x][y]) return false;
        // cycle found
        if (grid[x][y] == 0) return true;
        char back = grid[x][y]; grid[x][y] = 0;
        int cur = node(x, y);
        for (int d = 0; d < 4; d++) {
            // can not visit the previous node
            if (!(g[cur] & (1 << d))) continue;
            int nx = x + dirs[d][0], ny = y + dirs[d][1];
            if (node(nx, ny) == prev) continue;
            if (dfs(grid, nx, ny, cur))
                return true;
        }
        grid[x][y] = back;
        memo[x][y] = true;
        return false;
    }

    bool containsCycle(vector<vector<char>>& grid) {
        if (!grid.size()) return false;
        m = grid.size(); n = grid[0].size();
        memo = vector<vector<bool>>(m, vector<bool>(n));
        g = vector<char>(m * n);
        // build graph
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                int node1 = node(i, j);
                if (j + 1 < n && grid[i][j] == grid[i][j + 1]) {
                        g[node1] |= (1 << 0);
                        g[node1 + 1] |= (1 << 1);
                }
                if (i + 1 < m && grid[i][j] == grid[i + 1][j]) {
                        g[node1] |= (1 << 2);
                        g[node1 + n] |= (1 << 3);
                }
            }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (dfs(grid, i, j, -1)) {
                    return true;
                }
            }
        return false;
    }
};
```


2. ##### Union Find

- comes from zerotrac2

```cpp
struct UnionFind {
    vector<int> nodes;
    UnionFind(int size) : nodes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        return nodes[node] == node ? node : (nodes[node] = find(nodes[node]));
    }
    // return false means two nodes are already being connected.
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        else nodes[f1] = f2;
        return true;
    }
};
class Solution {
public:
#define node(x, y) ((x) * n + (y))
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size(); if (!m) return false;
        int n = grid[0].size();
        UnionFind uf(m * n);
        // only try to connect right/down side node
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (i + 1 < m && grid[i][j] == grid[i + 1][j]
                    && !uf.merge(node(i, j), node(i + 1, j)))
                    return true;
                if (j + 1 < n && grid[i][j] == grid[i][j + 1] 
                    && !uf.merge(node(i, j), node(i, j + 1)))
                    return true;
            }
        return false;
    }
};
```