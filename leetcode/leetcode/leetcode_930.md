---
title: Binary Subarrays With Su
date: 2021-01-04
---
In an array A of 0s and 1s, how many non-empty subarrays have sum S?

 

Example 1:

Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation: 
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
 

Note:

A.length <= 30000
0 <= S <= A.length
A[i] is either 0 or 1.

#### Solutions

1. ##### prefix sum O(n) S(n)

```cpp
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        if (S > A.size()) return 0;
        int n = A.size(), sum = 0, res = 0;
        vector<int> m(n + 1); m[0] = 1;
        for (auto n : A) {
            sum += n;
            if (sum >= S) res += m[sum - S];
            m[sum]++;
        }
        return res;
    }
};
```

2. ##### sliding window

- Note that the case `S == 0` shoulbe be separately handled.

```cpp
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        if (S > A.size()) return 0;
        int i = 0, j = 0;
        int n = A.size(), sum = 0, res = 0, zero = 0;
        A.push_back(1);
        while (j < A.size()) {
            if ((sum += A[j++]) > S) {
                int st = i;
                while ((sum -= A[i++]) > S);
                if (S != 0)
                    // left parts * right parts
                    res += (i - st) * (zero + 1);
                else 
                    // n * (n + 1) / 2
                    res += zero * (zero + 1) / 2;
            }
            zero = A[j - 1] == 1 ? 0 : ++zero;
        }

        return res;
    }
};
```