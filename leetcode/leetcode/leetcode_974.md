---
title: Subarray Sums Divisible by K
date: 2021-01-04
---
Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.

 

Example 1:

Input: A = [4,5,0,-2,-3,1], K = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by K = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 

Note:

1 <= A.length <= 30000
-10000 <= A[i] <= 10000
2 <= K <= 10000

#### Solutions

1. ##### prefix sum

- Be careful to handle negative modulus.

```cpp
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        unordered_map<int, int> sums;
        sums[0]++;
        int sum = 0, res = 0;
        for (auto n : A) {
            sum += n;
            // incase mod < 0.
            // or  int mod = (sum % K + K) % K;
            int mod = sum % K >= 0 ? sum % K : K + (sum % K);
            res += sums[mod];
            sums[mod]++;
        }
        return res;
    }
};
```