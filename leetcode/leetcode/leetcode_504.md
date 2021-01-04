---
title: Base 7
date: 2021-01-04
---
Given an integer, return its base 7 string representation.

Example 1:
Input: 100
Output: "202"
Example 2:
Input: -7
Output: "-10"
Note: The input will be in range of [-1e7, 1e7].

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    string convertToBase7(int num) {
        if (!num) return "0";
        bool pos = num >= 0; num = abs(num);
        string res;
        while (num) {
            res.push_back(num % 7 + '0');
            num /= 7;
        }
        if (!pos) res.push_back('-');
        return {res.rbegin(), res.rend()};
    }
};
```