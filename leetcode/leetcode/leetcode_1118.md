---
title: Number of Days in a Month
date: 2021-01-04
---
Given a year Y and a month M, return how many days there are in that month.

 

Example 1:

Input: Y = 1992, M = 7
Output: 31
Example 2:

Input: Y = 2000, M = 2
Output: 29
Example 3:

Input: Y = 1900, M = 2
Output: 28
 

Note:

1583 <= Y <= 2100
1 <= M <= 12

#### Solutions

1. ##### math

- Y is a leap year only if `(Y % 4 == 0 && Y % 100 %= 0) || (Y % 400 == 0)`

```cpp
class Solution {
public:
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int numberOfDays(int Y, int M) {
        int day = days[M - 1];
        if (M == 2 && (Y % 4 == 0 && Y % 100 != 0) || Y % 400 == 0)
            day++;
        return day;
    }
};
```