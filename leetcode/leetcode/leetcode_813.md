---
title: Largest Sum of Averages
date: 2021-01-04
---
We partition a row of numbers A into at most K adjacent (non-empty) groups, then our score is the sum of the average of each group. What is the largest score we can achieve?

Note that our partition must use every number in A, and that scores are not necessarily integers.

```
Example:
Input: 
A = [9,1,2,3,9]
K = 3
Output: 20
Explanation: 
The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned A into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
```

 

#### Note:

-    1 <= A.length <= 100.
-    1 <= A[i] <= 10000.
-    1 <= K <= A.length.
-    Answers within 10^-6 of the correct answer will be accepted as correct.


#### Solutions

1. ##### dynamic programming O(n2 * k)  S(nk)

- `dp[j][k]` represents the the maximum sum of averages when `nums[:j]` is spliited into `k` continuous groups.
- `dp[j][k] = max(dp[i][k - 1] + avg(nums[i + 1: j])) for i in (0, j)`
- Note that `dp[i][1]` should be specifically handled while updating the dp table.
- Notion: `K <= A.length()` means dp[n - 1][K] must be the answer, if `K > A.length()`, the answer is `dp[n - 1][A.length()()]`


```cpp
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<vector<double>> dp(n, vector<double>(K + 1));
        vector<double> sum(n);
        dp[0][0] = 0;
        for (int j = 0; j < n; j++) {
            sum[j] += A[j] + (j ? sum[j - 1] : 0);
            dp[j][1] = sum[j] / (j + 1);
            // can not start with 1, other wise dp[j][1] will be prefix[j]
            for (int k = 2; k <= K && k <= j + 1; k++)
                for (int i = j - 1; i >= k - 2; i--)
                    dp[j][k] = max(dp[j][k], dp[i][k - 1] + (sum[j] - sum[i]) / (j - i));
        }

        return dp[n - 1][K];
    }
};
```


- Or use a simple 1-d dp array and filling the dp table column by column.

```cpp
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<double> dp(n); dp[0] = A[0];
        vector<int> sum(n); sum[0] = A[0];
        for (int i = 1; i < n; i++) {
            sum[i] += sum[i - 1] + A[i];
            dp[i] = (double)sum[i] / (i + 1);
        }
        
        for (int k = 2; k <= K; k++)
            for (int j = n - 1; j >= 0; j--)
                for (int i = j - 1; i >= k - 2; i--)
                    dp[j] = max(dp[j], dp[i] + double(sum[j] - sum[i]) / (j - i));
        // dp[i][k] must be greater than dp[:i)[k]
        return dp[n - 1];
    }
};
```

2. ##### dfs with memoization

```cpp
class Solution {
public:
    vector<double> sum;
    vector<vector<double>> memo;
    double solve(int end, int k) {
        if (k < 2 || memo[end][k]) return memo[end][k];
        for (int mid = end - 1; mid >= k - 2; mid--)
            memo[end][k] = max(memo[end][k], 
                solve(mid, k - 1) + (sum[end] - sum[mid]) / (end - mid));

        return memo[end][k];
    }
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        memo = vector<vector<double>>(n, vector<double>(K + 1));
        sum = vector<double>(n);

        for (int i = 0; i < n; i++) {
            sum[i] += A[i] + (i ? sum[i - 1] : 0);
            memo[i][1] = sum[i] / (i + 1);
        }

        return solve(n - 1, K);
    }
};

```