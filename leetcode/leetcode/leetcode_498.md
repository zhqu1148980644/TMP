---
title: Diagonal Traverse
date: 2021-01-04
---
Given a matrix of M x N elements (M rows, N columns), return all elements of the matrix in diagonal order as shown in the below image.

![](https://assets.leetcode.com/uploads/2018/10/12/diagonal_traverse.png)


```
Example:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]

Output:  [1,2,4,7,5,3,6,8,9]

Explanation:
```

 

#### Note:

The total number of elements of the given matrix will not exceed 10,000.


#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if (!matrix.size() || !matrix[0].size())
            return {};
        int nrow = matrix.size();
        int ncol = matrix[0].size();
        vector<int> res(nrow * ncol);
        int r = 0, c = 0, i = 0;
        int up = true;
        while (r + c < nrow + ncol) {
            if (up) {
                while (r >= 0 && c < ncol) {
                    res[i++] = matrix[r][c];
                    r--; c++;
                }
                r++;
                if (c == ncol) {
                    r++; c--;
                }
            }
            else {
                while (r < nrow && c >= 0) {
                    res[i++] = matrix[r][c];
                    r++; c--;
                }
                c++;
                if (r == nrow) {
                    c++; r--;
                }
            }
            up = !up;
        }
        return res;
    }
};
```