Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).


The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.


#### Solutions

1. ##### 2d prefix sum


```c++
class NumMatrix {
public:
    vector<vector<int>> accum;
    NumMatrix(vector<vector<int>>& matrix) {
        if (!matrix.size()) return;
        int nrow = matrix.size(), ncol = matrix[0].size();
        accum = vector<vector<int>>(nrow + 1, vector<int>(ncol + 1));
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                accum[i + 1][j + 1] = matrix[i][j] + accum[i + 1][j] + accum[i][j + 1] - accum[i][j];
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        if (!accum.size())
            return 0;
        return accum[row2 + 1][col2 + 1] + accum[row1][col1] - accum[row1][col2 + 1] - accum[row2  + 1][col1];
    }
};
```