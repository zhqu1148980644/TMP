#### Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

```
Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
```


#### Solutions

1. ##### Straight forward

- In each while loop, traverse all items in a certain layer in spiral order starting at the top left item of this layer. More specifically:
    - push the top left top into store vector.
    - Traverse top row, right column, bottom row, left column in the same manner that the first item of the current row or column has been visited.
    - In order to prevent visiting each items twice, ignore the bottom row and the left column when there are only one row or one column in this layer.

```c++
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0) return {};
        vector<int> res;
        int i = 0, j = 0, len1, len2;
        int ncol = matrix[0].size(), nrow = matrix.size();

        while (true) {
            if (ncol <= 0 || nrow <= 0) break;
            len1 = ncol; len2 = nrow;
            // visit the first item of this layer.
            res.push_back(matrix[i][j]);
            // top_row[1:]
            while (--len1) res.push_back(matrix[i][++j]);
            // right_col[1:]
            while (--len2) res.push_back(matrix[++i][j]);
            if (ncol > 1 && nrow > 1) {
                len1 = ncol; len2 = nrow;
                // bottom_row[1:]
                while (--len1) res.push_back(matrix[i][--j]);
                // left_col[1:]
                while (--len2) res.push_back(matrix[--i][j]);
                // pop the first item of this layer which is visited again in the last time.
                res.pop_back();
            }
            i++; j++; ncol -= 2; nrow -= 2;
        }
        return res;
    }
};
```