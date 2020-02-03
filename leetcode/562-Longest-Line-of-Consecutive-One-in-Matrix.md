Given a 01 matrix M, find the longest line of consecutive one in the matrix. The line could be horizontal, vertical, diagonal or anti-diagonal.

```
Example:

Input:
[[0,1,1,0],
 [0,1,1,0],
 [0,0,0,1]]
Output: 3
```

#### Hint: The number of elements in the given matrix will not exceed 10,000. 


#### Solutions


1. ##### dynamic programming

- Count the number of contiguous 1 in each row, column, diagonal and anti-diagonal

```c++
class Solution {
public:
    int longestLine(vector<vector<int>>& M) {
        int nrow = M.size(); if (!nrow) return 0;
        int ncol = M[0].size();
        vector<vector<int>> dp(ncol, vector<int>(4));
        int maxn = 0, row, col, diag, adiag, prevdiag;
        for (int i = 0; i < nrow; i++) {
            prevdiag = 0;
            for (int j = 0; j < ncol; j++) {
                if (M[i][j] == 1) {
                    int tmp = dp[j][2];
                    row = dp[j][0] = j > 0 ? dp[j - 1][0] + 1 : 1;
                    col = dp[j][1] = dp[j][1] + 1;
                    diag = dp[j][2] = prevdiag + 1; prevdiag = tmp;
                    adiag = dp[j][3] = j + 1 < ncol ? dp[j + 1][3] + 1 : 1;

                    maxn = max(maxn, max(max(row, col), max(diag, adiag)));
                }
                else {
                    prevdiag = dp[j][2];
                    dp[j][0] = dp[j][1] = dp[j][2] = dp[j][3] = 0;
                }
            }
        }
        
        return maxn;
    }
};
```