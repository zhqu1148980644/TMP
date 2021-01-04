---
title: Bitwise AND of Numbers Range
date: 2021-01-04
---
#### Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

```
Example 1:

Input: [5,7]
Output: 4

Example 2:

Input: [0,1]
Output: 0
```

#### Solutions

- The idea is to find the longest unchangable high bits within the given range.
- For example: `n = 101001` and `m = 101100`
- Only the lowest `3` bit differs, as the bit AND operation will get `0` whenever a `0` is encountered, when bit AND with increasing numbers, the lowest `3` bits will finally be 0.

1. ##### iteratively remove a tail bit

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int removed = 0;
        while (n != m) {
            n >>= 1;
            m >>= 1;
            removed++;
        }
        return n << removed;
    }
};
```


2. ##### iteratively remove the rightmost `1` bit


```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (n > m) {
            n = n & (n - 1);
        }
        return n;
    }
};
```

3. ##### Another solution

- reference: https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--41/

