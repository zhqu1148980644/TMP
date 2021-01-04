---
title: Concatenation of Consecutive Binary Numbers
date: 2021-01-04
---
Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.

 

Example 1:

Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1. 
Example 2:

Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.
Example 3:

Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 109 + 7, the result is 505379714.
 

Constraints:

1 <= n <= 105

#### Solutions

1. ##### math

- Similar to numbers in base 10. i.e. `res = (res * 10 + digit % mod`

```cpp
class Solution {
public:
    int concatenatedBinary(int n) {
        long mod = 1e9 + 7, res = 0;
        for (int x = 1; x <= n; x++) {
            int flag = 1 << (32  - __builtin_clz(x) - 1);
            while (flag > 0) {
                res = ((res * 2) + bool((x & flag))) % mod;
                flag >>= 1;
            }
        }
        
        return res;
    }
};
```

or

```cpp
class Solution {
public:
    int concatenatedBinary(int n) {
        long long mod = 1e9 + 7, res = 0;
        for (int x = 1; x <= n; x++) {
            int lenone = 32 - __builtin_clz(x);
            res = (res * (1ll << lenone) + x) % mod;;
        }
        
        return res;
    }
};
```