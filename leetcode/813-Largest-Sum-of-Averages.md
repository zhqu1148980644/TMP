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


```c++
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<vector<double>> dp(n, vector<double>(K + 1));
        vector<double> prefixsum(n);
        for (int i = 0; i < n; i++)
            prefixsum[i] = A[i] + (i ? prefixsum[i - 1] : 0);
    
        for (int j = 0; j < n; j++) {
            dp[j][1] = prefixsum[j] / (j + 1);
            for (int k = 2; k <= K && k <= j + 1; k++) {
                for (int i = j - 1; i >= k - 2; i--) {
                    dp[j][k] = max(dp[j][k], dp[i][k - 1] + (prefixsum[j] - prefixsum[i]) / (j - i));
                }
            }
        }

        return *max_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};
```


- Or use a simple 1-d dp array and filling the dp table column by column.

```c++
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<double> dp(n);
        vector<double> prefixsum(n);
        for (int i = 0; i < n; i++) {
            prefixsum[i] = A[i] + (i ? prefixsum[i - 1] : 0);
            dp[i] = prefixsum[i] / (i + 1);
        }

        for (int k = 2; k <= K; k++) {
            for (int j = n - 1; j >= 0; j--)
                for (int i = j - 1; i >= k - 2; i--) {
                    dp[j] = max(dp[j], dp[i] + (prefixsum[j] - prefixsum[i]) / (j - i));
                }
        }

        // dp[i][k] must be greater than dp[i][k - 1]
        return dp[n - 1];
    }
};
```

2. ##### dfs with memoization

```c++
class Solution {
public:
    vector<double> sum;
    vector<vector<double>> memo;
    double solve(int end, int k) {
        if (k < 2 || memo[end][k])
            return memo[end][k];
        for (int mid = end - 1; mid >= k - 2; mid--)
            memo[end][k] = max(memo[end][k], solve(mid, k - 1) + (sum[end] - sum[mid]) / (end - mid));

        return memo[end][k];
    }
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        sum = vector<double>(n);
        memo = vector<vector<double>>(n, vector<double>(K + 1));

        for (int i = 0; i < n; i++) {
            sum[i] = A[i] + (i ? sum[i - 1] : 0);
            memo[i][1] = sum[i] / (i + 1);
        }

        return solve(n - 1, K);
    }
};
```