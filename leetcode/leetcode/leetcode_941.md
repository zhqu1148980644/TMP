---
title: Valid Mountain Array
date: 2021-01-04
---
Given an array A of integers, return true if and only if it is a valid mountain array.

Recall that A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[A.length - 1]


 

Example 1:

Input: [2,1]
Output: false
Example 2:

Input: [3,5,5]
Output: false
Example 3:

Input: [0,3,2,1]
Output: true
 

Note:

0 <= A.length <= 10000
0 <= A[i] <= 10000 
 

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        if (A.size() <= 2) return false;
        int state = -1;
        for (int i = 0; i < A.size() - 1; i++) {
            if (A[i] == A[i + 1])
                return false;
            else if (A[i] < A[i + 1]) {
                if (state == -1) state++;
                if (state > 0) return false;
            }
            else {
                if (state == 0) state++;
                if (state < 0) return false;
            }
        }
        return state == 1;
    }
};
```

or

```cpp
class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        if (A.size() <= 2) return false;
        int i = 0, j = A.size() - 1;
        while (i < j) {
            if (A[i] < A[i + 1])
                i++;
            else if (A[j] < A[j - 1])
                j--;
            else break;
        }

        return i == j && i != 0 && j != A.size() - 1;
    }
};
```