---
title: Maximum Sum Circular Subarray
date: 2021-01-04
---
Given a circular array C of integers represented by A, find the maximum possible sum of a non-empty subarray of C.

Here, a circular array means the end of the array connects to the beginning of the array.  (Formally, C[i] = A[i] when 0 <= i < A.length, and C[i+A.length] = C[i] when i >= 0.)

Also, a subarray may only include each element of the fixed buffer A at most once.  (Formally, for a subarray C[i], C[i+1], ..., C[j], there does not exist i <= k1, k2 <= j with k1 % A.length = k2 % A.length.)

 

Example 1:

Input: [1,-2,3,-2]
Output: 3
Explanation: Subarray [3] has maximum sum 3
Example 2:

Input: [5,-3,5]
Output: 10
Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10
Example 3:

Input: [3,-1,2,-1]
Output: 4
Explanation: Subarray [2,-1,3] has maximum sum 2 + (-1) + 3 = 4
Example 4:

Input: [3,-2,2,-3]
Output: 3
Explanation: Subarray [3] and [3,-2,2] both have maximum sum 3
Example 5:

Input: [-2,-3,-1]
Output: -1
Explanation: Subarray [-1] has maximum sum -1
 

Note:

-30000 <= A[i] <= 30000
1 <= A.length <= 30000

#### Solutions

- Note that the problem requires the length of the subarray is at most `len(A)`. The ordinary way of finding the maximum sum by using prefixsum would not work.

1. ##### mono stack with prefix sum O(2n) S(n)

- Maintaining a `monotonically increasing` stack(deque) with elements represents the minimum prefix sum in the valid range, remove the front element of the deque if the front element is the out of the valid range.

```cpp
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int j = 0, n = A.size(), hi = 2 * n - 1;
        int sum = 0, res = INT_MIN;
        // {index, prefixsum}
        deque<pair<int, int>> dq;
        dq.emplace_back(-1, 0);

        while (j < hi) {
            sum += A[j++ % n];
            // remove out of range prefix sum
            if (j > n && dq.front().first <= j % n)
                    dq.pop_front();
            // maxisum rangsum = prefixsum - min(prefixsum in the valid range)
            int minsum = dq.front().second;
            res = max(res, sum - minsum);
            // maintains monotonically increasing order
            while (dq.size() && dq.back().second > sum)
                dq.pop_back();
            dq.emplace_back(j, sum);
        }

        return res;
    }
};
```

2. ##### dynamic programming

- For finding maximum sum of subarray within noncircular array: `dp[i] = max(dp[i - 1], 0)`. `dp[i]` represents the maxisum sum of subarrays end at `nums[i]`.
- For subarrays spanning over two arrays(circular), finding the maxisum sum range equals to `total_sum - minimum_sumrange`.
- In ohter words, the maximum range sum has two cases in total:
    - Sum of middle range.
    - Sum of prefix plus sum of suffix.

```
aaaaaaaccccccccbbbbb aaaaaaaacccccccbbbbb
               |   maximum  |
to make bbbbb+aaaaa has the largest sum, sum of cccccc has to be minimum
```

```cpp
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int sum = 0, curmax = 0, curmin = 0;
        int maxsum = INT_MIN, minsum = INT_MAX;

        for (auto n : A) {
            sum += n;
            maxsum = max(maxsum, curmax = n + max(curmax, 0));
            minsum = min(minsum, curmin = n + min(curmin, 0));
        }
        // sum == minsum only when minres contains all numbers(or numers outside minres are all zeros) and sum <= 0
        // if this is true, then maxsum must be the answer
        return max(maxsum, sum != minsum ? sum - minsum : INT_MIN);
    }
};
```