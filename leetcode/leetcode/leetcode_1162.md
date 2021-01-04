---
title: As Far from Land as Possible
date: 2021-01-04
---
Given an N x N grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized and return the distance.

The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

If no land or water exists in the grid, return -1.



```
Example 1:

Input: [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation: 
The cell (1, 1) is as far as possible from all the land with distance 2.

Example 2:

Input: [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation: 
The cell (2, 2) is as far as possible from all the land with distance 4.
```



#### Note:

-    1 <= grid.length == grid[0].length <= 100
-    grid[i][j] is 0 or 1


#### Solutions


1. ##### bfs from lands with queue

- A water cell can be firstly reached by it's nearest land cell in a breath first approach.

```cpp
#define node(x, y) (((x) * ncol) + (y))
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int nrow = grid.size();
        int ncol = grid[0].size();
        queue<int> q;
        vector<bool> visited(nrow * ncol, false);
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (grid[i][j] == 1) {
                    q.push(node(i, j));
                    visited[node(i, j)] = true;
                }
        
        if (q.size() == nrow * ncol)
            return -1;

        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        int dis = -1;
        int x, y, nx, ny;
        while (!q.empty()) {
            int size = q.size();
            dis++;
            while (size--) {
                x = q.front() / ncol;
                y = q.front() % ncol;
                q.pop();
                for (int d = 0; d < 4; d++) {
                    nx = x + dx[d];
                    ny = y + dy[d];
                    int nextnode = node(nx, ny);
                    if (nx >= 0 && ny >= 0 
                        && nx < nrow && ny < ncol
                        && grid[nx][ny] == 0
                        && !visited[nextnode]) {
                        q.push(nextnode);
                        visited[nextnode] = true;
                    }
                }
            }
        }

        return dis;
    }
};
```

- Instead of using bool table to prevent visiting each water multiple times, we can use inplace tag.

```cpp
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        int num1 = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (!grid[i][j]) continue;
                num1++;
                q.emplace(i, j);
            }
        if (num1 == 0 || num1 == m * n) return -1;
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        int dis = 0;
        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto [x, y] = q.front(); q.pop();
                for (auto & d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx < 0 || ny < 0 || 
                        nx >= m || ny >= n || grid[nx][ny])
                        continue;
                    grid[nx][ny] = 2;
                    q.emplace(nx, ny);
                }
            }
            dis++;
        }

        return dis - 1;
    }
};
```


2. ##### dynamic programming

- `dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i + 1][j], dp[i][j + 1]) + 1`


```cpp
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int INF = 0x3f3f3f3f;
        vector<vector<int>> dp(m, vector<int>(n));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if  (grid[i][j] == 1) continue;
                int left = j ? dp[i][j - 1] : INF;
                int up = i > 0 ? dp[i - 1][j] : INF;
                dp[i][j] = min(left, up) + 1;
            }
        
        int res = -1;
        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j]) continue;
                int right = j + 1 < n ? dp[i][j + 1] : INF;
                int botom = i + 1 < m ? dp[i + 1][j] : INF;
                dp[i][j] = min(dp[i][j], min(right, botom) + 1);
                res = max(res, dp[i][j]);
            }
        
        return res > m * n ? -1 : res;
    }
};
```