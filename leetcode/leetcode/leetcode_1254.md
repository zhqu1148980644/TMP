---
title: Number of Closed Islands
date: 2021-01-04
---
Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

 

Example 1:



Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation: 
Islands in gray are closed because they are completely surrounded by water (group of 1s).
Example 2:



Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1
Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2
 

Constraints:

1 <= grid.length, grid[0].length <= 100
0 <= grid[i][j] <=1

#### Solutions

1. ##### dfs

```cpp
class Solution {
public:
    int m, n;
    bool dfs(vector<vector<int>> & grid, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n) return false;
        if (grid[i][j] == 3 || grid[i][j] == 1) return true;
        grid[i][j] = 3;
        bool down = dfs(grid, i + 1, j);
        bool right = dfs(grid, i, j + 1);
        bool up = dfs(grid, i - 1, j);
        bool left = dfs(grid, i, j - 1);
        return down && right && up && left;
    }
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size();
        int res = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res += grid[i][j] == 0 && dfs(grid, i, j);

        return res;
    }
};
```