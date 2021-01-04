---
title: Two Sum Less Than K
date: 2021-01-04
---
Given an array A of integers and integer K, return the maximum S such that there exists i < j with A[i] + A[j] = S and S < K. If no i, j exist satisfying this equation, return -1.

 

Example 1:

Input: A = [34,23,1,24,75,33,54,8], K = 60
Output: 58
Explanation: 
We can use 34 and 24 to sum 58 which is less than 60.
Example 2:

Input: A = [10,20,30], K = 15
Output: -1
Explanation: 
In this case it's not possible to get a pair sum less that 15.
 

Note:

1 <= A.length <= 100
1 <= A[i] <= 1000
1 <= K <= 2000

#### Solutions

1. ##### straight forward O(n2)

```cpp
class Solution {
public:
    int twoSumLessThanK(vector<int>& A, int K) {
        int res = -1;
        for (int i = 0; i < A.size(); i++)
            for (int j = i + 1; j < A.size(); j++)
                if (A[i] + A[j] < K && A[i] + A[j] > res)
                    res = A[i] + A[j];
        return res;
    }
};
```

2. ##### sort with two pointers

```cpp
class Solution {
public:
    int twoSumLessThanK(vector<int>& A, int K) {
        sort(A.begin(),  A.end());
        int i = 0, j = A.size() - 1;
        int res = -1;
        while (i < j) {
            int sum = A[i] + A[j];
            if (sum >= K)
                j--;
            else {
                if (sum > res) res = sum;
                i++;
            }
        }

        return res;
    }
};
```