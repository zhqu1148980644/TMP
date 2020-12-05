https://ac.nowcoder.com/acm/contest/9716/B

#### Solutions

1. ##### dynamic programming O(nm)

- `dp[n][m]` represents the number of solutions to handle `n` notes and `m` accents with the `last` accent placed on the last position.
- Since solutions for `dp[n][m]` for different m are non-redundant(unique) based the last accent, we have:
- `dp[n][m] = sum(dp[pn][m - 1] for all pn < n - k)`


```c++
class Solution {
public:
    /**
     * 
     * @param n int整型 乐谱总音符数
     * @param m int整型 重音符数
     * @param k int整型 重音符之间至少的间隔
     * @return long长整型
     */
    long long solve_bangbang(int n, int m, int k) {
        if (m == 0) return 1;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        int mod = 1000000007;
        // edge cases
        for (int nn = 1; nn <= n; nn++)
            dp[nn][1] = 1;

        for (int mm = 2; mm <= m; mm++) {
            long long psum = 0;
            for (int nn = 1; nn <= n; nn++) {
                if (nn - k - 1 >= 1)
                    dp[nn][mm] = psum = (psum + dp[nn - k - 1][mm - 1]) % mod;
            }
        }
        // all solutions with m accents are unique, sum them up
        long long res = 0;
        for (int nn = 1; nn <= n; nn++)
            res = (res + dp[nn][m]) % mod;
        return res;
    }
};
```