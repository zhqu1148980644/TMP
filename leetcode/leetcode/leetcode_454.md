---
title: 4Sum II
date: 2021-01-04
---
Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in the range of -228 to 228 - 1 and the result is guaranteed to be at most 231 - 1.

Example:

Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0

#### Solutions

1. ##### hashmap O(n2)

```cpp
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> sum;
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < B.size(); j++) {
                sum[A[i] + B[j]]++;
            }
        
        int res = 0;
        for (int i = 0; i < C.size(); i++)
            for (int j = 0; j < D.size(); j++) {
                int s = C[i] + D[j];
                if (sum.count(-s))
                    res += sum[-s];
            }
        
        return res;
    }
};
```