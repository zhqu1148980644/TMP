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

```c++
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
- Borrowed from others

```c++
#define node(x, y) (((x) * ncol) + (y))
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int nrow = grid.size();
        int ncol = grid[0].size();
        queue<int> q;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (grid[i][j] == 1)
                    q.push(node(i, j));
        
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
                        && grid[nx][ny] == 0) {
                        q.push(nextnode);
                        grid[nx][ny] = 1;
                    }
                }
            }
        }

        return dis;
    }
};
```


2. ##### dynamic programming

- `dp[i] = min(dp[i - 1][j], dp[i][j - 1], dp[i + 1][j], dp[i][j + 1]) + 1`


```c++
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int nrow = grid.size();
        int ncol = grid[0].size();
        int tag = nrow * ncol + 1;
        vector<vector<int>> dp(nrow, vector<int>(ncol));
        //  top to bottom and left to right
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == 1)
                    continue;
                int left = j > 0 ? dp[i][j - 1] : tag;
                int up = i > 0 ? dp[i - 1][j] : tag;
                dp[i][j] = min(left, up) + 1;
            }
        // bottom to up and right to left
        int maxdis = -1;
        for (int i = nrow - 1; i >= 0; i--)
            for (int j = ncol - 1; j >= 0; j--) {
                if (grid[i][j] == 1)
                    continue;
                int right = j + 1 < ncol ? dp[i][j + 1] : tag;
                int bottom = i + 1 < nrow ? dp[i + 1][j] : tag;
                dp[i][j] = min(dp[i][j], min(right, bottom) + 1);
                if (dp[i][j] < tag && dp[i][j] > maxdis)
                    maxdis = dp[i][j];
            }
        
        return maxdis;
    }
};
```