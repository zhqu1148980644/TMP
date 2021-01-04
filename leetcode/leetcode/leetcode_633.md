---
title: Sum of Square Numbers
date: 2021-01-04
---
Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.

Example 1:

Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5
 

Example 2:

Input: 3
Output: False

##### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    bool issquare(int n) {
        long r = n;
        while (r * r > n)
            r = (r + n / r) / 2;
        return r * r == n;
    }
    bool judgeSquareSum(int c) {
        if (c == 0) return true;
        for (long i = 1; i * i <= c; i++)
            if (issquare(c - i * i))
                return true;
        return false;
    }
};
```

- Or use sqrt in std

```cpp
class Solution {
public:
    bool judgeSquareSum(int c) {
        if (c == 0) return true;
        for (long i = 1; i * i <= c; i++) {
            auto sq = sqrt(c - i * i);
            if (sq == (int)sq)
                return true;
        }

        return false;
    }
};
```


2. ##### two pointers

- scan all pairs of `a, b` in `range[0, sqrt(c)]`.

```cpp
class Solution {
public:
    bool judgeSquareSum(int c) {
        long lo = 0, hi = sqrt(c);
        while (lo <= hi) {
            long sum = lo * lo + hi * hi;
            if (sum == c)
                return true;
            else if (sum > c)
                hi--;
            else
                lo++;
        };
        return false;
    }
};
```

3. ##### math