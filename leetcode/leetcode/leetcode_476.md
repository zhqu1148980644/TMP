---
title: Number Complement
date: 2021-01-04
---
Given a positive integer num, output its complement number. The complement strategy is to flip the bits of its binary representation.

 

Example 1:

Input: num = 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
Example 2:

Input: num = 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
 

Constraints:

The given integer num is guaranteed to fit within the range of a 32-bit signed integer.
num >= 1
You could assume no leading zero bit in the integer’s binary representation.
This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/

#### Solutions

1. ##### straight forward

- `0101 ^ 0111`

```cpp
class Solution {
public:
    int findComplement(int num) {
        if (num == 0) return 1;
        int n = num, c = 0;
        while (n) {
            n >>= 1;
            c = (c << 1) | 1;
        }
        return c ^ num;
    }
};
```