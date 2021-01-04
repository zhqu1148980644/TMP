---
title: Minimum Number of Days to Disconnect Islan
date: 2021-01-04
---
Given a 2D grid consisting of 1s (land) and 0s (water).  An island is a maximal 4-directionally (horizontal or vertical) connected group of 1s.

The grid is said to be connected if we have exactly one island, otherwise is said disconnected.

In one day, we are allowed to change any single land cell (1) into a water cell (0).

Return the minimum number of days to disconnect the grid.

 

Example 1:



Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
Output: 2
Explanation: We need at least 2 days to get a disconnected grid.
Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.
Example 2:

Input: grid = [[1,1]]
Output: 2
Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]), 0 islands.
Example 3:

Input: grid = [[1,0,1,0]]
Output: 0
Example 4:

Input: grid = [[1,1,0,1,1],
               [1,1,1,1,1],
               [1,1,0,1,1],
               [1,1,0,1,1]]
Output: 1
Example 5:

Input: grid = [[1,1,0,1,1],
               [1,1,1,1,1],
               [1,1,0,1,1],
               [1,1,1,1,1]]
Output: 2
 

Constraints:

1 <= grid.length, grid[i].length <= 30
grid[i][j] is 0 or 1.

#### Solutions

1. ##### Union Find O (mn * mn)

- There are at mostly 3 cases, ie: operate 0, 1, 2 steps.

```cpp
struct UnionFind {
    vector<int> nodes;
    UnionFind(int size) : nodes(size) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        return nodes[node] == node ? node : (nodes[node] = find(nodes[node]));
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        nodes[f1] = f2;
        return true;
    }
};
class Solution {
public:
#define node(x, y) ((x) * n + (y))
    int m, n;
    // count the number of communities
    int dfs(vector<vector<int>> & grid) {
        UnionFind uf(m * n);
        int num = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!grid[i][j]) continue;
                num++;
                if (i + 1 < m && grid[i + 1][j]) {
                    if (uf.merge(node(i + 1, j), node(i, j)))
                        num--;
                }
                if (j + 1 < n && grid[i][j + 1]) {
                    if (uf.merge(node(i, j + 1), node(i, j)))
                        num--;
                }
            }
        }
        return num;
    }
    int minDays(vector<vector<int>>& grid) {
        m = grid.size(); if (!m) return 0;
        n = grid[0].size();
        UnionFind uf(m * n);
        // already being partitioned, need 0 step
        if (dfs(grid) != 1) return 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;
                grid[i][j] = 0;
                // if islands is splited after removing the current node
                if (dfs(grid) != 1) return 1;
                grid[i][j] = 1;
            }
        // other wise
        return 2;
    }
};

```