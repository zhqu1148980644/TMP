---
title: Count Square Submatrices with All Ones
date: 2021-01-04
---
Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

 

Example 1:

Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation: 
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.
Example 2:

Input: matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation: 
There are 6 squares of side 1.  
There is 1 square of side 2. 
Total number of squares = 6 + 1 = 7.
 

Constraints:

1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1

#### Solutions

- Similar to problem `221 Maximal Square`

1. ###### dynamic programming O(n2)

```cpp
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();

        vector<int> dp(matrix[0]);
        int res = accumulate(matrix[0].begin(), matrix[0].end(), 0);
        for(int i = 1; i < m; i++) {
            int preup = dp[0];
            res += dp[0] = matrix[i][0] == 1;
            for (int j = 1; j < n; j++) {
                int up = dp[j];
                if (matrix[i][j] == 1)
                    dp[j] = min({preup, dp[j - 1], dp[j]}) + 1;
                else
                    dp[j] = 0;
                preup = up;
                res += dp[j];
            }
        }

        return res;
    }
};
```

- Or fill the dp table in-place.

```cpp
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size(); if (!m) return 0;
        int n = matrix[0].size();
        int res = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i && j && matrix[i][j])
                    matrix[i][j] = min({
                        matrix[i - 1][j - 1],
                        matrix[i][j - 1],
                        matrix[i - 1][j]
                    }) + 1;
                res += matrix[i][j];
            }
        }

        return res;
    }
};
```