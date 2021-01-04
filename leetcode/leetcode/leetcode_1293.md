---
title: Shortest Path in a Grid with Obstacles Elimination
date: 2021-01-04
---
Given a m * n grid, where each cell is either 0 (empty) or 1 (obstacle). In one step, you can move up, down, left or right from and to an empty cell.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m-1, n-1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.

 

Example 1:

Input: 
grid = 
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]], 
k = 1
Output: 6
Explanation: 
The shortest path without eliminating any obstacle is 10. 
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
 

Example 2:

Input: 
grid = 
[[0,1,1],
 [1,1,1],
 [1,0,0]], 
k = 1
Output: -1
Explanation: 
We need to eliminate at least two obstacles to find such a walk.
 

Constraints:

grid.length == m
grid[0].length == n
1 <= m, n <= 40
1 <= k <= m*n
grid[i][j] == 0 or 1
grid[0][0] == grid[m-1][n-1] == 0

#### Solutions

1. ##### bfs

```cpp
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        if (m == 1 && n == 1) return 0;
        vector<vector<vector<int>>> 
            visited(m, vector<vector<int>>(n, vector<int>(k + 1)));
        visited[0][0][0] = true;
        queue<tuple<int, int, int>> q;
        q.emplace(0, 0, 0);
        
        int step = 0;
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto [x, y, rm] = q.front(); q.pop();
                for (auto & d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                        continue;
                    int nrm = rm + (grid[nx][ny] == 1);
                    if (nrm > k || visited[nx][ny][nrm]) continue;
                    if (nx == m - 1 && ny == n - 1) return step + 1;
                    visited[nx][ny][nrm] = true;
                    q.emplace(nx, ny, nrm);
                }
            }
            step++;
        }

        return -1;
    }
};
```