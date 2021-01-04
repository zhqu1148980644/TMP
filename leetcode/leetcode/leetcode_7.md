---
title: Reverse Integer
date: 2021-01-04
---
### Given a 32-bit signed integer, reverse digits of an integer.

#### Example 1:

```
Input: 123
Output: 321
```

### Example 2:

```
Input: -123
Output: -321
```

### Example 3:

```
Input: 120
Output: 21
```

### Note:

Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

### Solutions

1. #### Straight forward.

- Watch for edges cases.
- No need to check the case when `base * 10 + remainder > INT_MAX`.
    - When x contains 9 digits and `base` reaches to number smaller than `INT_MAX / 10` before the first digit is considered.
    - Since the first digit will not be larger than `2`, `base * 10 + remainder` will be `INT_MAX / 10 + 2` in the worst case, which is a valid number, thus we only need to ensure `base < INT_MAX / 10`.


```cpp
class Solution {
public:
    int reverse(int x) {
        int remain = 0, res = 0;
        int max = INT_MAX / 10;
        int min = INT_MIN / 10;
        while (x != 0) {
            remain = x % 10;
            x /= 10;
            if ((res > max) || (res < min))
                return 0;
            res = res * 10 + remain;
        }
        return res;
    }
};
```

Or

```cpp
class Solution {
public:
    int reverse(int x) {
        if (!x) return 0;
        int base = 0;
        while (x) {
            if (base > INT_MAX / 10 || base < INT_MIN / 10)
                return 0;
            base = base * 10 + x % 10;
            x /= 10;
        }
        return base;
    }
};
```