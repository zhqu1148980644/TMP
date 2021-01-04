---
title: Encode Number
date: 2021-01-04
---
Given a non-negative integer num, Return its encoding string.

The encoding is done by converting the integer to a string using a secret function that you should deduce from the following table:



 

Example 1:

Input: num = 23
Output: "1000"
Example 2:

Input: num = 107
Output: "101100"
 

Constraints:

0 <= num <= 10^9

#### Solutions

1. ##### bit operation

```cpp
class Solution {
public:
    string encode(int num) {
        string res; num++;
        while (num >> 1) {
            res += num & 1 ? '1' : '0';
            num >>= 1;
        }
        return {res.rbegin(), res.rend()};
    }
};
```