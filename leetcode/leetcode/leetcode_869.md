---
title: Reordered Power of 2
date: 2021-01-04
---
Starting with a positive integer N, we reorder the digits in any order (including the original order) such that the leading digit is not zero.

Return true if and only if we can do this in a way such that the resulting number is a power of 2.

 

Example 1:

Input: 1
Output: true
Example 2:

Input: 10
Output: false
Example 3:

Input: 16
Output: true
Example 4:

Input: 24
Output: false
Example 5:

Input: 46
Output: true
 

Note:

1 <= N <= 10^9

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    array<int, 10> count(int n) {
        array<int, 10> count; count.fill(0);
        while (n) {
            count[n % 10]++;
            n /= 10;
        }
        return count;
    }
    bool reorderedPowerOf2(int N) {
        auto c = count(N);
        for (int i = 0; i < 30; i++)
            if (count(1 << i) == c)
                return true;
        return false;
    }
};
```