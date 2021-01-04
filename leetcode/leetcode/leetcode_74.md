---
title: Search a 2D Matrix
date: 2021-01-04
---
#### Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

```
Example 1:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
Output: true
Example 2:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
Output: false
```

#### Solutions

1. ##### binary search

- Ravel the 2d matrix into a 1d sorted array.

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // edge cases
        if (!matrix.size() || !matrix[0].size()) return false;
        int ncol = matrix[0].size();
        int lo = 0, hi = matrix.size() * ncol, mid;
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            if (target < matrix[mid / ncol][mid % ncol])
                hi = mid;
            else
                lo = mid + 1;
        }
        // the last element not larger than the target.
        lo--;
        // may be negative
        if (lo < 0 || matrix[lo / ncol][lo % ncol] != target)
            return false;
        else
            return true;
    }
};
```