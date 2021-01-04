---
title: Surface Area of 3D Shapes
date: 2021-01-04
---
On a N * N grid, we place some 1 * 1 * 1 cubes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).

Return the total surface area of the resulting shapes.


```
Example 1:

Input: [[2]]
Output: 10

Example 2:

Input: [[1,2],[3,4]]
Output: 34

Example 3:

Input: [[1,0],[0,2]]
Output: 16

Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 32

Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 46
```


#### Note:

-    1 <= N <= 50
-    0 <= grid[i][j] <= 50


#### Solutions

1. ##### straight forward

- Count the maximum area can be made by all columns: ie `sum(1 + 1 + 4 * height for all bar) - 2 * (number of overlapping sefaces)`

```cpp
class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size(), res = 0, overlap = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (!grid[i][j]) continue;
                res += 2 + grid[i][j] * 4;
                if (i + 1 < n && grid[i + 1][j])
                    overlap += min(grid[i][j], grid[i + 1][j]);
                if (j + 1 < n && grid[i][j + 1])
                    overlap += min(grid[i][j], grid[i][j + 1]);
            }

        return res -= 2 * overlap;
    }
};
```