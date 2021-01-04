---
title: Super Egg Drop
date: 2021-01-04
---
You are given K eggs, and you have access to a building with N floors from 1 to N. 

Each egg is identical in function, and if an egg breaks, you cannot drop it again.

You know that there exists a floor F with 0 <= F <= N such that any egg dropped at a floor higher than F will break, and any egg dropped at or below floor F will not break.

Each move, you may take an egg (if you have an unbroken one) and drop it from any floor X (with 1 <= X <= N). 

Your goal is to know with certainty what the value of F is.

What is the minimum number of moves that you need to know with certainty what F is, regardless of the initial value of F?

 

```
Example 1:

Input: K = 1, N = 2
Output: 2
Explanation: 
Drop the egg from floor 1.  If it breaks, we know with certainty that F = 0.
Otherwise, drop the egg from floor 2.  If it breaks, we know with certainty that F = 1.
If it didn't break, then we know with certainty F = 2.
Hence, we needed 2 moves in the worst case to know what F is with certainty.

Example 2:

Input: K = 2, N = 6
Output: 3

Example 3:

Input: K = 3, N = 14
Output: 4
```

 

#### Note:

-    1 <= K <= 100
-    1 <= N <= 10000


#### Solutions

1. ##### dynamic programming

- TLE O(kn2)
- `dp[k][n]` represents the minimum number of moves need to know `F` with `k` eggs and `n` floors.

```cpp
class Solution {
public:
// for 1 egg, we must test k floors to know the F within [0:k]
// for example k = 3
// drop at 1, break, F = 0, otherwist F must within[1:k]
// drop at 2, break, F = 1, otherwise F must within[2:k]
// drop at 3, break, F = 2, otherwise F = 3
    vector<vector<int>> memo;
    int solve(int k, int n) {
        if (k == 1) return n;
        if (n == 0) return 0;
        if (memo[k][n] != -1)
            return memo[k][n];
        int res = INT_MAX;
        // drop at each floor form 1...n
        for (int i = 1; i <= n; i++) {
            // choose the worst case between these two cases.
            // egg break when drop at floor i, both floors and eggs reduce by 1
            // egg don't break when drop at floor i, when egg break at i + 1 floor, we know the F is the current floor, thus the subproblem only contains (i:n].
            res = min(res, max(solve(k - 1, i - 1), solve(k, n - i)) + 1);
        }

        return memo[k][n] = res;
    }
    int superEggDrop(int K, int N) {
        memo =  vector<vector<int>>(K + 1, vector<int>(N + 1, -1));
        return solve(K, N);
    }
};
```


- binary search O(knlog(n))
- `dp(k, n)` increases when n increases, when `f1(i) cross f2(i)`, `dp[k][n] = f1(i) + f2(i)` reaches the minimum value. we use binary search to find the corresponding `i`.
- This can be seen as finding the valley for `f2(i) - f1(i)`.

```cpp
class Solution {
public:
    vector<vector<int>> memo;
    int solve(int k, int n) {
        if (k == 1) return n;
        if (n == 0) return 0;
        if (memo[k][n] != -1) return memo[k][n];
        int lo = 1, hi = n;

        int res = INT_MAX;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            int broken = solve(k - 1, mid - 1);
            int unbroken = solve(k, n - mid);
            if (broken < unbroken) {
                lo = mid + 1;
                res = min(res, 1 + unbroken);
            }
            else {
                hi = mid;
                res = min(res, 1 + broken);
            }
        }
        res = min(res, 1 + max(solve(k - 1, lo - 1), solve(k, n - lo)));
        return memo[k][n] = res;
    }
    int superEggDrop(int K, int N) {
        memo = vector<vector<int>>(K + 1, vector<int>(N + 1, -1));
        return solve(K, N);
    }
};
```


- Another version. O(nk)
- `dp[k][m]` represents the maximum of floors can be investigated with `k` eggs and `m` moves.

```cpp
class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> dp(K + 1, vector<int>(N + 1));
        int m = 0;
        while (dp[K][m] < N) {
            m++;
            for (int k = 1; k <= K; k++)
                dp[k][m] = dp[k - 1][m - 1] + dp[k][m - 1] + 1;
        }
        return m;
    }
};
```

- Or with single 1d array.

```cpp
class Solution {
public:
    int superEggDrop(int K, int N) {
        vector<int> dp(K + 1);
        int m = 0;
        while (dp[K] < N) {
            m++;
            for (int k = K; k > 0; k--)
                dp[k] += dp[k - 1] + 1;
        }
        return m;
    }
};
```