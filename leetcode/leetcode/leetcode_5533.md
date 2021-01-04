---
title: Minimum One Bit Operations to Make Integers Zero
date: 2021-01-04
---
Given an integer n, you must transform it into 0 using the following operations any number of times:

Change the rightmost (0th) bit in the binary representation of n.
Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the (i-2)th through 0th bits are set to 0.
Return the minimum number of operations to transform n into 0.

 

Example 1:

Input: n = 0
Output: 0
Example 2:

Input: n = 3
Output: 2
Explanation: The binary representation of 3 is "11".
"11" -> "01" with the 2nd operation since the 0th bit is 1.
"01" -> "00" with the 1st operation.
Example 3:

Input: n = 6
Output: 4
Explanation: The binary representation of 6 is "110".
"110" -> "010" with the 2nd operation since the 1st bit is 1 and 0th through 0th bits are 0.
"010" -> "011" with the 1st operation.
"011" -> "001" with the 2nd operation since the 0th bit is 1.
"001" -> "000" with the 1st operation.
Example 4:

Input: n = 9
Output: 14
Example 5:

Input: n = 333
Output: 393
 

Constraints:

0 <= n <= 109


#### Solutions

1. ##### math

- reference: https://leetcode-cn.com/problems/minimum-one-bit-operations-to-make-integers-zero/solution/zhao-gui-lu-by-baymaxhwy-2/
- Copied explanation:

```
for numbers with only one bit: for example 100
the number of steps is 2^(n + 1) - 1 n is the index of the bit 1
2^(2 + 1) - 1 == 7
100 -> 101 -> 111 -> 110 -> 010 -> 011 -> 001 -> 000

for 101, we can see that 101 is part of 100's traversal states, thus
f(101->000) = f(100->000) - f(100->101)
...
...
```


```cpp
class Solution {
public:
    int minimumOneBitOperations(int n) {
        if (n == 0) return 0;
        int pos = 32 - __builtin_clz(n) - 1;
        return (1 << (pos + 1)) - 1 - minimumOneBitOperations(n ^ (1 << pos));
    }
};
```

2. ##### gray code

```cpp


```