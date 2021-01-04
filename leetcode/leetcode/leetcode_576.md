---
title: Out of Boundary Paths
date: 2021-01-04
---
There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball, you can move the ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right). However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary. The answer may be very large, return it after mod 109 + 7.

 

```
Example 1:

Input: m = 2, n = 2, N = 2, i = 0, j = 0
Output: 6
Explanation:

Example 2:

Input: m = 1, n = 3, N = 3, i = 0, j = 1
Output: 12
Explanation:
```

 

#### Note:

-    Once you move the ball out of boundary, you cannot move it back.
-    The length and height of the grid is in range [1,50].
-    N is in range [0,50].

#### Solutions

1. ##### dynamic programming O(kmn) S(mn)

- `dp[i][j][k]` represents the number of unique paths reached `grid[i][j]` after `k` moves starting from the given position of ball.
- The answer equals to the `sum` of paths reached borders in `1, 2, 3, ... k` moves.

```cpp
class Solution {
public:
    int findPaths(int m, int n, int N, int i, int j) {
        vector<vector<int>> dp(m, vector<int>(n));
        int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        dp[i][j] = 1;
        long res = 0;
        for (int k = 1; k <= N; k++) {
            vector<vector<int>> dp1(m, vector<int>(n));
            for (int i = 0 ; i < m; i++)
                for (int j = 0; j < n; j++) {
                    if (!dp[i][j])
                        continue;
                    int numpath = dp[i][j];
                    for (auto & d : dir) {
                        int nx = i + d[0], ny = j + d[1];
                        if (nx < 0 || ny < 0 || nx == m || ny == n)
                            res += numpath;
                        else
                            dp1[nx][ny] = (dp1[nx][ny] + numpath) % 1000000007;
                    }
                }
            dp = move(dp1);
        }

        return res % 1000000007;
    }
};
```

2. ##### dfs with memoization

```cpp
class Solution {
public:
    vector<vector<vector<int>>> memo;
    int solve(int & m, int & n, int k, int i, int j) {
        if (k < 0) return 0;
        if (i < 0 || j < 0 || i == m || j == n)
            return 1;
        if (memo[i][j][k] != INT_MIN)
            return memo[i][j][k];
    
        long cnt = 0;
        cnt += solve(m, n, k - 1, i + 1, j);
        cnt += solve(m, n, k - 1, i, j + 1);
        cnt += solve(m, n, k - 1, i - 1, j);
        cnt += solve(m, n, k - 1, i, j - 1);

        return memo[i][j][k] = cnt % 1000000007;
    }

    int findPaths(int m, int n, int N, int i, int j) {
        memo = vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(N + 1, INT_MIN)));
        return solve(m , n, N, i, j);
    }
};
```