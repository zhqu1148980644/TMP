---
title: Max Consecutive Ones III
date: 2021-01-04
---
Given an array A of 0s and 1s, we may change up to K values from 0 to 1.

Return the length of the longest (contiguous) subarray that contains only 1s. 

 

Example 1:

Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
Output: 6
Explanation: 
[1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
Example 2:

Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
Output: 10
Explanation: 
[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
 

Note:

1 <= A.length <= 20000
0 <= K <= A.length
A[i] is 0 or 1 

#### Solutions

1. ##### sliding window

- The problem equals to find the length of the longest window with at most `k` zeros.

```cpp
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        int i = 0, j = 0, res = 0, cnt = 0;
        while (j < A.size()) {
            if (A[j++] == 0 && ++cnt > K) {
                while (A[i++] != 0);
                cnt--;
            }
            res = max(res, j - i);
        }

        return res;
    }
};
```