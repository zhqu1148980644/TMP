#### Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

-    Integers in each row are sorted in ascending from left to right.
-    Integers in each column are sorted in ascending from top to bottom.

```
Example:

Consider the following matrix:

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

Given target = 5, return true.

Given target = 20, return false.
```


#### Solutions

1. ##### deduce and conquer

- Shrink the seaching space at each iteration.
- Start searching at the leftbottom corner or rightmost corner of the matrix.
- As two pointers can move at most `m + n` steps, thus the complexity is `O(m + n)`.


```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (!matrix.size() || !matrix[0].size()) return false;
        int i = 0, j = matrix[0].size() - 1;
        while (i < matrix.size() && j >= 0) {
            if (matrix[i][j] == target)
                return true;
            // taget is smaller than the current number, move left.
            else if (target < matrix[i][j])
                j--;
            // otherwise we move to the next row.
            else
                i++;
        }
        return false;
    }
};
```

2. ##### binary search along each row and column

```c++


```