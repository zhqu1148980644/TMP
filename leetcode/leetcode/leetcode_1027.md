---
title: Longest Arithmetic Sequence
date: 2021-01-04
---
Given an array A of integers, return the length of the longest arithmetic subsequence in A.

Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 0 <= i_1 < i_2 < ... < i_k <= A.length - 1, and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value (for 0 <= i < B.length - 1).

 

```
Example 1:

Input: [3,6,9,12]
Output: 4
Explanation: 
The whole array is an arithmetic sequence with steps of length = 3.

Example 2:

Input: [9,4,7,2,10]
Output: 3
Explanation: 
The longest arithmetic subsequence is [4,7,10].

Example 3:

Input: [20,1,15,3,10,5,8]
Output: 4
Explanation: 
The longest arithmetic subsequence is [20,15,10,5].
```

 

#### Note:

-    2 <= A.length <= 2000
-    0 <= A[i] <= 10000


#### Solutions

1. ##### dynamic programming O(n2) S(n2)

- Use hash map to store length of every possible arithmetic sequence.

```cpp
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int len = A.size(), res = 0;
        vector<vector<int>> dp(len, vector<int>(20000));

        for (int j = 0; j < len; j++)
            for (int i = 0; i < j; i++) {
                // prevent minus gap
                int gap = A[j] - A[i] + 10000;
                if (dp[i][gap])
                    dp[j][gap] = dp[i][gap] + 1;
                else
                    dp[j][gap] = 2;
                res = max(res, dp[j][gap]);
            }
        
        return res;
    }
};
```

Or

```cpp
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int len = A.size(), res = 0;
        vector<vector<int>> dp(len, vector<int>(20000, 1));

        for (int j = 0; j < len; j++)
            for (int i = 0; i < j; i++) {
                int gap = A[j] - A[i] + 10000;
                dp[j][gap] = dp[i][gap] + 1;
                res = max(res, dp[j][gap]);
            }
        
        return res;
    }
};
```


- Another better approach.
- The dp table is much more smaller.
- reference: https://leetcode-cn.com/problems/longest-arithmetic-sequence/solution/tong-guo-aihe-ajzhao-qian-mian-de-xiang-by-charon-/

```cpp
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int index[20000];
        memset(index, -1, 20000 * sizeof(int));
        int len = A.size(), res = 0;
        vector<vector<int>> dp(len, vector<int>(len));

        for (int i = 0; i < len; i++) {
            index[A[i]] = i;
            for (int j = i + 1; j < len; j++) {
                int prev = A[i] - (A[j] - A[i]);
                if (prev < 0 || index[prev] == -1)
                    dp[i][j] = 2;
                else
                    dp[i][j] = dp[index[prev]][i] + 1;
                res = max(res, dp[i][j]);
            }
        }

        return res;
    }
};
```