---
title: Binary Number with Alternating Bits
date: 2021-01-04
---
Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

Example 1:
Input: 5
Output: True
Explanation:
The binary representation of 5 is: 101
Example 2:
Input: 7
Output: False
Explanation:
The binary representation of 7 is: 111.
Example 3:
Input: 11
Output: False
Explanation:
The binary representation of 11 is: 1011.
Example 4:
Input: 10
Output: True
Explanation:
The binary representation of 10 is: 1010.

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    bool hasAlternatingBits(int n) {
        while (n) {
            if ((n & 0b1) > 0 == (n & 0b10) > 0)
                return false;
            n >>= 1;
        }
        return true;
    }
};
```

or one line version using xor

```cpp
class Solution {
public:
    bool hasAlternatingBits(int n) {
        // 10101010 ^ 01010101 = 11111111
        n = n ^ (n >> 1);
        // 11111111 + 1 = 1000000000 & 11111111 = 00000000 
        // if n == INT_MAX, INT_MAX + 1 will cause runtime error
        return n == INT_MAX || !(n & (n + 1));
    }
};
```