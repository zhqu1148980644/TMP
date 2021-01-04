---
title: Walls and Gates
date: 2021-01-04
---
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

Example: 

Given the 2D grid:

INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:

  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4

#### Solutions

1. ##### bfs O(mn)

- The key point is to start searching from `multiple gates` simultaneously.

```cpp
class Solution {
public:
    int nrow, ncol;
    inline int node(int x, int y) {
        return x * ncol + y;
    }
    void wallsAndGates(vector<vector<int>>& rooms) {
        nrow = rooms.size(); if (!rooms.size()) return;
        ncol = rooms[0].size();
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        queue<int> q;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (!rooms[i][j]) q.push(node(i, j));
        
        while (!q.empty()) {
            int i = q.front() / ncol;
            int j = q.front() % ncol; q.pop();
            for (auto & d : dirs) {
                int x = i + d[0], y = j + d[1];
                if (x < 0 || y < 0 
                || x >= nrow || y >= ncol 
                || rooms[x][y] != 2147483647)
                    continue;
                rooms[x][y] = rooms[i][j] + 1;
                q.push(node(x, y));
            }
        }
    }
};
```