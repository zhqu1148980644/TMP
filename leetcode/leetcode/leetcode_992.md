---
title: Subarrays with K Different Integers
date: 2021-01-04
---
Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of A good if the number of different integers in that subarray is exactly K.

(For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)

Return the number of good subarrays of A.

 

Example 1:

Input: A = [1,2,1,2,3], K = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
Example 2:

Input: A = [1,2,1,3,4], K = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 

Note:

1 <= A.length <= 20000
1 <= A[i] <= A.length
1 <= K <= A.length

#### Solutions

1. ##### sliding window

- reference: https://leetcode-cn.com/problems/subarrays-with-k-different-integers/solution/shuang-zhi-zhen-qing-xi-ontong-su-jie-shi-by-pbslz/
- `numequal(k) == numless(k) - numless(k - 1)` .less means less than or equal to.

```cpp
class Solution {
public:
    int lessthen(vector<int> & A, int k) {
        vector<int> count(A.size() + 1);
        int i = 0, j = 0, cnt = 0, res = 0;
        while (j < A.size()) {
            if (++count[A[j++]] == 1 && ++cnt > k) {
                while (--count[A[i++]] != 0);
                cnt--;
            }
            // number of subarrays end with `j - 1` that satisfies the requirement.
            res += j - i;
        }
        return res;
    }
    int subarraysWithKDistinct(vector<int>& A, int K) {
        return lessthen(A, K) - lessthen(A, K - 1);
    }
};
```