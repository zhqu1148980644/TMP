---
title: Largest Perimeter Triangle
date: 2021-01-04
---
Given an array A of positive lengths, return the largest perimeter of a triangle with non-zero area, formed from 3 of these lengths.

If it is impossible to form any triangle of non-zero area, return 0.

 

Example 1:

Input: [2,1,2]
Output: 5
Example 2:

Input: [1,2,1]
Output: 0
Example 3:

Input: [3,2,3,4]
Output: 10
Example 4:

Input: [3,6,2,3]
Output: 8
 

Note:

3 <= A.length <= 10000
1 <= A[i] <= 10^6

#### Solutions

1. ##### math

- for `a <= b <= c`, a + b > c is the sufficient requirement for them to make up a valid triangle

```cpp
class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        if (A.size() <= 2) return 0;
        sort(A.begin(), A.end());

        for (int i = A.size() - 3; i >= 0; i--)
            if (A[i] + A[i + 1] > A[i + 2])
                return A[i] + A[i + 1] + A[i + 2];
        
        return 0;
    }
};
```