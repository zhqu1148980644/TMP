---
title: 01 Matrix
date: 2021-01-04
---
Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

 

```
Example 1:

Input:
[[0,0,0],
 [0,1,0],
 [0,0,0]]

Output:
[[0,0,0],
 [0,1,0],
 [0,0,0]]
Example 2:

Input:
[[0,0,0],
 [0,1,0],
 [1,1,1]]

Output:
[[0,0,0],
 [0,1,0],
 [1,2,1]]
```
 

Note:

The number of elements of the given matrix will not exceed 10,000.
There are at least one 0 in the given matrix.
The cells are adjacent in only four directions: up, down, left and right.


#### Solutions

1. ##### bfs

```cpp
#define node(x, y) (((x) * n + y))
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(); if (!m) return {{}};
        int n = matrix[0].size();
        queue<int> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == 0)
                    q.push(node(i, j));
                else // if not set 1 to -1, each 1 will be visited endlessly
                    matrix[i][j] = -1;
        

        int dirs[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
        while (!q.empty()) {
            int x = q.front() / n, y = q.front() % n;
            int curdis = matrix[x][y]; q.pop();
            for (auto & d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                // Avoid pushing each node into queue multiple times.
                if (nx < 0 || ny < 0 || nx >= m || ny >= n || matrix[nx][ny] >= 0)
                    continue;
                matrix[nx][ny] = curdis + 1;
                q.push(node(nx, ny));
            }
        }
        

        return matrix;
    }
};
```

2. ##### dynamic programming

- `dp[i][j]` represents the minimum distance between `matrix[i][j]` and the nearest zero.

```cpp
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(); if (!m) return {{}};
        int n = matrix[0].size();

        // top-left to bottom-right
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1)
                    matrix[i][j] = m + n;
                if (i > 0)
                    matrix[i][j] = min(matrix[i][j], matrix[i - 1][j] + 1);
                if (j > 0)
                    matrix[i][j] = min(matrix[i][j], matrix[i][j - 1] + 1);
            }
        // bottom-right to top-left
        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--) {
                if (i != m - 1)
                    matrix[i][j] = min(matrix[i][j], matrix[i + 1][j] + 1);
                if (j != n - 1)
                    matrix[i][j] = min(matrix[i][j], matrix[i][j + 1] + 1);
            }
        
        return matrix;
    }
};
```