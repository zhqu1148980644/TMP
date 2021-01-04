---
title: Spiral Matrix III
date: 2021-01-04
---
On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing east.

Here, the north-west corner of the grid is at the first row and column, and the south-east corner of the grid is at the last row and column.

Now, we walk in a clockwise spiral shape to visit every position in this grid. 

Whenever we would move outside the boundary of the grid, we continue our walk outside the grid (but may return to the grid boundary later.) 

Eventually, we reach all R * C spaces of the grid.

Return a list of coordinates representing the positions of the grid in the order they were visited.

 

Example 1:

Input: R = 1, C = 4, r0 = 0, c0 = 0
Output: [[0,0],[0,1],[0,2],[0,3]]


 

Example 2:

Input: R = 5, C = 6, r0 = 1, c0 = 4
Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]


 

Note:

1 <= R <= 100
1 <= C <= 100
0 <= r0 < R
0 <= c0 < C

#### Solutions

1. ##### simulation

- Whenever the order has been changed 2 times, steps needs to be forward increases by `1`.

```cpp
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        vector<vector<int>> res(R * C);
        int w = 0, cnt = 0, step = 1, dx = 0, dy = 1;
        res[w++] = {r0, c0};
        while (w < res.size()) {
            for (int i = 0; i < step; i++) {
                r0 += dx; c0 += dy;
                if (r0 >= 0 && c0 >= 0 && r0 < R && c0 < C)
                    res[w++] = {r0, c0};
            }
            if (++cnt % 2 == 0)
                step++;
            swap(dx, dy);
            dy = -dy;
        }

        return res;
    }
};
```