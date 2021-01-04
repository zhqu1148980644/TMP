---
title: Bomb Enemy
date: 2021-01-04
---
Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note: You can only put the bomb at an empty cell.

```
Example:

Input: [["0","E","0","0"],["E","0","W","E"],["0","E","0","0"]]
Output: 3 
Explanation: For the given grid,

0 E 0 0 
E 0 W E 
0 E 0 0


Placing a bomb at (1,1) kills 3 enemies.
```

#### Solutions


1. ##### dynamic programming O(n2) S(n)

- Borrowed from stephan.
- `rowsum` represents all enemies can be killed in a region without any walls. Whenever meets a block whose's left block is a wall, count all enemies starting at this block until a wall is reached. Then all zeros in this non-wall region can `reuse` this counts.
- `colsum` is a vector stores counts of the previous row in all columns. The couting process of `colsum[j]` is the same as `rowsum`.

```cpp
class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int nrow = grid.size(); if (!nrow) return 0;
        int ncol = grid[0].size();

        int rowsum;
        vector<int> columm(ncol);
        int res = 0;

        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (j == 0 || grid[i][j - 1] == 'W') {
                    rowsum = 0;
                    for (int c = j; c < ncol && grid[i][c] != 'W'; c++)
                        rowsum += grid[i][c] == 'E';
                }
                if (i == 0|| grid[i - 1][j] == 'W') {
                    columm[j] = 0;
                    for (int r = i; r < nrow && grid[r][j] != 'W'; r++)
                        columm[j] += grid[r][j] == 'E';
                }
                if (grid[i][j] == '0')
                    res = max(res, rowsum + columm[j]);
            }
        return res;
    }
};
```


