---
title: Minimum Falling Path Su
date: 2021-01-04
---
Given a square array of integers A, we want the minimum sum of a falling path through A.

A falling path starts at any element in the first row, and chooses one element from each row.  The next row's choice must be in a column that is different from the previous row's column by at most one.

 

Example 1:

Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: 12
Explanation: 
The possible falling paths are:
[1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
[2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
[3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]
The falling path with the smallest sum is [1,4,7], so the answer is 12.

 

Constraints:

1 <= A.length == A[0].length <= 100
-100 <= A[i][j] <= 100

#### Solutions

1. ##### dynamic programming

```cpp
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int m = A.size(), n = A[0].size();
        vector<int> dp(A[0]);
        for (int r = 1; r < m; r++) {
            vector<int> dp1(A[r]);
            for (int c = 0; c < n; c++) {
                int minl = c - 1 >= 0 ? dp[c - 1] : INT_MAX;
                int minr = c + 1 < n ? dp[c + 1] : INT_MAX;
                dp1[c] += min(dp[c], min(minl, minr));
            }
            swap(dp, dp1);
        }

        return *min_element(dp.begin(), dp.end());
    }
};
```