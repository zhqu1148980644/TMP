---
title: Partition Array for Maximum Su
date: 2021-01-04
---
Given an integer array A, you partition the array into (contiguous) subarrays of length at most K.  After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.

 

Example 1:

Input: A = [1,15,7,9,2,5,10], K = 3
Output: 84
Explanation: A becomes [15,15,15,9,10,10,10]
 

Note:

1 <= K <= A.length <= 500
0 <= A[i] <= 10^6

#### Solutions

1. ##### dynamic programming O(nk)

- `dp[i]` represents the maximum results for `nums[:i]`.

```cpp
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& A, int K) {
        int n = A.size();
        vector<int> dp(A);

        for (int j = 0; j < n; j++) {
            int maxv = A[j];
            dp[j] += j ? dp[j - 1] : 0;
            for (int i = j - 1; i > j - K && i >= 0; i--) {
                int prev = i - 1 >= 0 ? dp[i - 1] : 0;
                maxv = max(maxv, A[i]);
                dp[j] = max(dp[j], prev + maxv * (j - i + 1));
            }
        }

        return dp[n - 1];
    }
};
```