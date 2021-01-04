---
title: Maximum Width Ramp
date: 2021-01-04
---
Given an array A of integers, a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].  The width of such a ramp is j - i.

Find the maximum width of a ramp in A.  If one doesn't exist, return 0.

 

Example 1:

Input: [6,0,8,2,1,5]
Output: 4
Explanation: 
The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.
Example 2:

Input: [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation: 
The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.
 

Note:

2 <= A.length <= 50000
0 <= A[i] <= 50000

#### Solutions

1. ##### mono stack O(n)

- Mataining a monotonically decreasing stack stating with the first element of the array, then the target `i` must be within the stack. After the stack has been built, scanning the array `backwards(j)` and pop back the top element when the current `j` is larger/eq than the `top`(All availanle `j` to the left of the current `j` must has less `j - i`).

```cpp
class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        stack<int> s;
        for (int i = 0; i < A.size(); i++)
            if (!s.size() || A[s.top()] > A[i])
                s.push(i);

        int res = 0;
        for (int j = A.size() - 1; j >= 0; j--)
            while (s.size() && A[j] >= A[s.top()]) {
                res = max(res, j - s.top()); s.pop();
            }

        return res;
    }
};
```