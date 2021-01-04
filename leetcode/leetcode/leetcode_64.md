---
title: Minimum Path Su
date: 2021-01-04
---
### Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

### Note: 
You can only move either down or right at any point in time.

```
Example:

Input:
[
[1,3,1],
[1,5,1],
[4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.
```


### Solutions

1. #### Dynamic programming

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int minpath[n]; minpath[0] = grid[0][0];
        for (int i = 1; i < n; i++)
            minpath[i] = minpath[i - 1] + grid[0][i];
        for (int i = 1; i < m; i++) {
            minpath[0] = minpath[0] + grid[i][0];
            for (int j = 1; j < n; j++) {
                minpath[j] = min(minpath[j - 1], minpath[j]) + grid[i][j];
            }
        }
        return minpath[n - 1];
    }
};
```