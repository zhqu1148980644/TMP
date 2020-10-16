Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

Example:

Input: 

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

Output: 4


#### Solutions

1. ##### dynamic programming

- `dp[i][j]` represent the maximum length of the square with `matrix[i][j]` as the right-bottom corner.
- `dp[i][j] = min(dp[i - 1, j], dp[i - 1][j - 1], dp[i][j - 1]) + 1 if matrix[i][j] == '1' else 0`
- Check the official answer for detailed proof.

```c++
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (!matrix.size()) return 0;
        int res = 0;
        vector<int> dp(matrix[0].size());

        for (int i = 0; i < matrix.size(); i++) {
            int prel = i == 0 ? 0 : dp[0];
            dp[0] = matrix[i][0] == '1';
            res = max(dp[0], res);
            for (int j = 1; j < matrix[0].size(); j++) {
                int tmp = dp[j];
                if (matrix[i][j] == '1')
                    dp[j] = min(prel, min(dp[j - 1], dp[j])) + 1;
                else
                    dp[j] = 0;
                prel = tmp;
                res = max(res, dp[j]);
            }
        }
        return res * res;
    }
};
```