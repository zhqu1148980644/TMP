We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.

However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

Example:

n = 10, I pick 8.

First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.

Game over. 8 is the number I picked.

You end up paying $5 + $7 + $9 = $21.
Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.

#### Solutions

- Binary search saves times, while dynamic programming saves costs.
- `dp[k] = min(max(dp[lo, k - 1], dp[k + 1, hi]) + k  for k in [lo:hi])`

1. ##### dfs with memoization

```c++
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> memo(n + 1, vector<int>(n + 1, INT_MAX));
        function<int(int, int)> solve = [&](int lo, int hi) {
            if (hi <= lo) return 0;
            auto & minp = memo[lo][hi];
            if (minp != INT_MAX) return minp;
            for (int k = lo; k <= hi; k++)
                minp = min(minp, k + max(solve(lo, k - 1), solve(k + 1, hi)));
            return minp;
        };
        return solve(1, n);
    }
};
```


2. ##### dynamic programming

```c++
class Solution {
public:
    int getMoneyAmount(int n) {
        // must be n + 1
        vector<vector<int>> dp(n + 2, vector<int>(n + 2));

        for (int len = 2; len <= n; len++)
            for (int i = 1; i <= n - len + 1; i++) {
                int minp = INT_MAX;
                for (int k = i; k < i + len; k++)
                    // k + 1 may be greather than n
                    minp = min(minp, k + max(dp[i][k - 1], dp[k + 1][i + len - 1]));
                dp[i][i + len - 1] = minp;
            }
        return dp[1][n];
    }
};
```

or manually check border cases;
```c++
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));

        for (int len = 2; len <= n; len++)
            for (int i = 1; i <= n - len + 1; i++) {
                int j = i + len - 1;
                // border cases will cause outofbound error.
                int minp = min(i + dp[i + 1][j], j + dp[i][j - 1]);
                for (int k = i + 1; k < j; k++)
                    minp = min(minp, k + max(dp[i][k - 1], dp[k + 1][i + len - 1]));
                dp[i][i + len - 1] = minp;
            }
        return dp[1][n];
    }
};
```