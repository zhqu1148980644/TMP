---
title: Range Sum Query 2D Mutable
date: 2021-01-04
---
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
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
You may assume that row1 ≤ row2 and col1 ≤ col2.


#### Solutions

1. ##### binary index tree(fenwick tree)

```cpp
struct FenwickTree {
    int m, n;
    vector<vector<int>> sums;
    FenwickTree(int r, int c) 
    : m(r + 1), n(c + 1), sums(r + 1, vector<int>(c + 1)) {}

    static inline int lowbit(int x) {
        return x & (-x);
    }
    // do not directly use r, c
    void update(int r, int c, int delta) {
        for (int i = r; i < m; i += lowbit(i))
            for(int j = c; j < n; j += lowbit(j))
                sums[i][j] += delta;
    }
    int query(int r, int c) {
        int sum = 0;
        for (int i = r; i > 0; i -= lowbit(i))
            for(int j = c; j > 0; j -= lowbit(j))
                sum += sums[i][j];
        return sum;
    }
};

class NumMatrix {
public:
    FenwickTree ft;
    vector<vector<int>> clone;
    NumMatrix(vector<vector<int>>& matrix) 
    : ft(matrix.size(), matrix.size() ? matrix[0].size() : 0), clone(matrix) {
        for (int i = 0; i < matrix.size(); i++)
            for (int j = 0; j < matrix[0].size(); j++)
                ft.update(i + 1, j + 1, matrix[i][j]);
    }
    
    void update(int row, int col, int val) {
        ft.update(row + 1, col + 1, val - clone[row][col]);
        clone[row][col] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return ft.query(row2 + 1, col2 + 1) + ft.query(row1, col1) 
        - ft.query(row1, col2 + 1) 
        - ft.query(row2 + 1, col1);
    }
};
```



2. ##### 2d segment tree