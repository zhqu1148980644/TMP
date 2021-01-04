---
title: Lucky Numbers in a Matrix
date: 2021-01-04
---
Given a m * n matrix of distinct numbers, return all lucky numbers in the matrix in any order.

A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.

 

```
Example 1:

Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
Output: [15]
Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column
Example 2:

Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
Output: [12]
Explanation: 12 is the only lucky number since it is the minimum in its row and the maximum in its column.
Example 3:

Input: matrix = [[7,8],[1,2]]
Output: [7]
```
 

#### Constraints:

m == mat.length
n == mat[i].length
1 <= n, m <= 50
1 <= matrix[i][j] <= 10^5.
All elements in the matrix are distinct.


#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> mins(m);
        for (int i = 0; i < m; i++) {
            int minj = min_element(matrix[i].begin(), matrix[i].end()) - matrix[i].begin();
            mins[i] = minj;
        }

        vector<int> res;
        for (int j = 0; j < n; j++) {
            int max = matrix[0][j], maxi = 0;
            for (int i = 0; i < m; i++)
                if (matrix[i][j] > max) {
                    max = matrix[i][j];
                    maxi = i;
                }
            if (mins[maxi] == j)
                res.push_back(matrix[maxi][j]);
        }
        
        return res;
    }
};
```

or

```cpp
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> row(m, INT_MAX), col(n, INT_MIN);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                row[i] = min(row[i], matrix[i][j]);
                col[j] = max(col[j], matrix[i][j]);
            }
        
        vector<int> res;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (matrix[i][j] == row[i] && matrix[i][j] == col[j])
                    res.push_back(matrix[i][j]);
        
        return res;
    }
};
```