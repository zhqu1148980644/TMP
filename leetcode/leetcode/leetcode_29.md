---
title: Divide Two Integers
date: 2021-01-04
---
### Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

```
Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
```

### Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.

### Solutions

1. #### bit operation O(log(n)2)

- Borrowed from other.
- Iteratively find the lagest divisor.
- Convert inputs to negative numbers to get rid of overflow problems.


```cpp
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        bool neg = dividend < 0 ^ divisor < 0;
        if (dividend > 0)
            dividend = -dividend;
        if (divisor > 0)
            divisor = -divisor;
        unsigned int res = 0, fold = 1;
        int _divisor = divisor;
        while (dividend <= _divisor) {
            if (dividend <= divisor) {
                res += fold;
                dividend -= divisor;
                fold += fold;
                if (divisor < (INT_MIN >> 1))
                    break;
                divisor += divisor;
            }
            else {
                divisor >>= 1;
                fold >>= 1;
            }
        }

        return neg ? -res : res;
    }
};
```

Or we can just starting from 2^31 * divisor to 2^0 * divisor
