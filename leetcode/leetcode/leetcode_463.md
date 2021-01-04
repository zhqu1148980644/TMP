---
title: Island Perimeter
date: 2021-01-04
---
#### You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water.

Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes" (water inside that isn't connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

 

```
Example:

Input:
[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Output: 16

Explanation: The perimeter is the 16 yellow stripes in the image below:
```

#### Solutions

1. ##### count number of islands

- count the number of islands `nisland`.
- count the number of pairs of islands are adjacent to each other(Only count once) `nadj`.
- The perimeter of the island is `nisland * 4 - 2 * nadj`

```cpp
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int nisland = 0, adj = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++) {
                if (!grid[i][j]) continue;
                nisland++;
                if (i + 1 < grid.size() && grid[i + 1][j])
                    adj++;
                if (j + 1 < grid[0].size() && grid[i][j + 1])
                    adj++;
            }
        return 4 * nisland - 2 * adj;
    }
};
```


2. ##### count number of edges exposed to water

- The projection of left/top edges and right/bottom edges are the same, thus we only need to count edges in one of two opposit sides.

```cpp
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int edges = 0, nrow = grid.size(), ncol = grid[0].size();
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (!grid[i][j]) continue;
                if (i == nrow - 1 || !grid[i + 1][j])
                    edges++;
                if (j == ncol - 1 || !grid[i][j + 1])
                    edges++;
            }
        // we countted edges based on projection.
        return 2 * edges;
    }
};
```