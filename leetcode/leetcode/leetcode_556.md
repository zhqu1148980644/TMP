---
title: Next Greater Element III
date: 2021-01-04
---
Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.

Example 1:

Input: 12
Output: 21
 

Example 2:

Input: 21
Output: -1

#### Solutions

1. ##### next greater permutation

- check `problem` 31 for details

```cpp
class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        int r = s.size(); if (!r) return -1;
        while (--r) if (s[r] > s[r - 1]) break;
        if (r == 0) return -1;
        int rnext = r;
        while (rnext + 1 < s.size() && s[rnext + 1] > s[r - 1])
            rnext++;
        swap(s[r - 1], s[rnext]);
        rnext = s.size() - 1;
        while (r < rnext)
            swap(s[r++], s[rnext--]);
        long res = stol(s);
        return res <= INT_MAX ? res : -1;
    }
};
```