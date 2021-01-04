---
title: Number of Submatrices That Sum to Target
date: 2021-01-04
---
Given a matrix, and a target, return the number of non-empty submatrices that sum to target.

A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.

Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate that is different: for example, if x1 != x1'.

 

```
Example 1:

Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
Output: 4
Explanation: The four 1x1 submatrices that only contain 0.

Example 2:

Input: matrix = [[1,-1],[-1,1]], target = 0
Output: 5
Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2 submatrix.
```


#### Note:

-    1 <= matrix.length <= 300
-    1 <= matrix[0].length <= 300
-    -1000 <= matrix[i] <= 1000
-    -10^8 <= target <= 10^8


#### Solutions

1. ##### prefix sum and hash map O(n3)

- Prepare the prefix sum of each row.
- Iterate for every possible pair of columns that define the left and right border of each matrix in `O(n2)`.
- For each pair of columns, iterate over all rows in `O(n)`.
- In the inner loop, we can calculate the sum of submatrix in `O(1)` time with prefix sum and hash map.


```cpp
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 1; j < n; j++)
                matrix[i][j] += matrix[i][j - 1];
                
        int res = 0;
        // Iterate over all column pairs.
        for (int c1 = 0; c1 < n; c1++)
            for (int c2 = c1; c2 < n; c2++) {
                int sum = 0;
                unordered_map<int, int> cache = {{0, 1}};
                // iterate over all possible bottom edges.
                for (int r = 0; r < m; r++) {
                    sum += matrix[r][c2] - (c1 ? matrix[r][c1 - 1] : 0);
                    if (cache.count(sum - target))
                        res += cache[sum - target];
                    cache[sum]++;
                }
            }
        
        return res;
    }
};
```