---
title: Projection Area of 3D Shapes
date: 2021-01-04
---
On a N * N grid, we place some 1 * 1 * 1 cubes that are axis-aligned with the x, y, and z axes.

Each value v = grid[i][j] represents a tower of v cubes placed on top of grid cell (i, j).

Now we view the projection of these cubes onto the xy, yz, and zx planes.

A projection is like a shadow, that maps our 3 dimensional figure to a 2 dimensional plane. 

Here, we are viewing the "shadow" when looking at the cubes from the top, the front, and the side.

Return the total area of all three projections.

 

Example 1:

Input: [[2]]
Output: 5
Example 2:

Input: [[1,2],[3,4]]
Output: 17
Explanation: 
Here are the three projections ("shadows") of the shape made with each axis-aligned plane.

Example 3:

Input: [[1,0],[0,2]]
Output: 8
Example 4:

Input: [[1,1,1],[1,0,1],[1,1,1]]
Output: 14
Example 5:

Input: [[2,2,2],[2,1,2],[2,2,2]]
Output: 21
 

Note:

1 <= grid.length = grid[0].length <= 50
0 <= grid[i][j] <= 50

#### Solutions

1. ##### straight forward O(mn) S(m + n)

```cpp
class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid.size(), top = 0;
        vector<int> front(n), side(m);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    top++;
                    front[j] = max(front[j], grid[i][j]);
                    side[i] = max(side[i], grid[i][j]);
                }
            }
        
        return top 
            + accumulate(front.begin(), front.end(), 0)
            + accumulate(side.begin(), side.end(), 0);
    }
};
```

or

```cpp
class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            int maxrow = 0, maxcol = 0;
            for (int j = 0; j < n; j++) {
                // since we are reusing i, j, can not wrap these three lines in a if statement.
                res += grid[i][j] > 0;
                maxrow = max(maxrow, grid[i][j]);
                maxcol = max(maxcol, grid[j][i]);
            }
            res += maxrow + maxcol;
        }

        return res;
    }
};
```