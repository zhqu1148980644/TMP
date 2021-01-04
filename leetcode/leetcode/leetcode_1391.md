---
title: Check if There is a Valid Path in a Gri
date: 2021-01-04
---
Given a m x n grid. Each cell of the grid represents a street. The street of grid[i][j] can be:

    1 which means a street connecting the left cell and the right cell.
    2 which means a street connecting the upper cell and the lower cell.
    3 which means a street connecting the left cell and the lower cell.
    4 which means a street connecting the right cell and the lower cell.
    5 which means a street connecting the left cell and the upper cell.
    6 which means a street connecting the right cell and the upper cell.

You will initially start at the street of the upper-left cell (0,0). A valid path in the grid is a path which starts from the upper left cell (0,0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.

Notice that you are not allowed to change any street.

Return true if there is a valid path in the grid or false otherwise.

 
![](https://assets.leetcode.com/uploads/2020/03/05/main.png)

```
Example 1:

Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).

Example 2:

Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)

Example 3:

Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).

Example 4:

Input: grid = [[1,1,1,1,1,1,3]]
Output: true

Example 5:

Input: grid = [[2],[2],[2],[2],[2],[2],[6]]
Output: true
```

 

#### Constraints:
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    1 <= grid[i][j] <= 6


#### Solutions

1. ##### dfs

```cpp
class Solution {
public:
    int m, n;
    vector<vector<bool>> meet;
    vector<vector<vector<int>>> dir = {{{0, 1}, {0, -1}}, 
                                    {{-1, 0}, {1, 0}}, 
                                    {{0, -1}, {1, 0}},
                                    {{0, 1}, {1, 0}},
                                    {{0, -1}, {-1, 0}},
                                    {{-1, 0}, {0, 1}}};
    bool find(int i, int j, vector<vector<int>> & grid, const vector<int> & pre) {
        if (i < 0 || j < 0 || i >= m || j >= n || meet[i][j])
            return false;
        auto & d = dir[grid[i][j] - 1];
        if (pre.size()) {
            bool correct = false;
            for (int i = 0; i < 2; i++)
                correct |= d[i][0] + pre[0] == 0 && d[i][1] + pre[1] == 0;
            if (!correct) return false;
        }
        meet[i][j] = true;
        return (i == m - 1 && j == n - 1)
            || find(i + d[0][0], j + d[0][1], grid, d[0])
            || find(i + d[1][0], j + d[1][1], grid, d[1]);
    }

    bool hasValidPath(vector<vector<int>>& grid) {
        m = grid.size(); if (!m) return false;
        n = grid[0].size();
        meet = vector<vector<bool>>(m, vector<bool>(n, false));

        return find(0, 0, grid, {});
    }
};
```

2. ##### build graph


3. ##### union find