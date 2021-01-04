---
title: Arranging Coins
date: 2021-01-04
---
#### You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.

Given n, find the total number of full staircase rows that can be formed.

n is a non-negative integer and fits within the range of a 32-bit signed integer.

```
Example 1:

n = 5

The coins can form the following rows:
¤
¤ ¤
¤ ¤

Because the 3rd row is incomplete, we return 2.

Example 2:

n = 8

The coins can form the following rows:
¤
¤ ¤
¤ ¤ ¤
¤ ¤

Because the 4th row is incomplete, we return 3.
```

#### Solutions

- Toal number of coins in k rows:  n = (k * (k + 1)) / 2

1. ##### binary search

```cpp
class Solution {
public:
    int arrangeCoins(int n) {
        int lo = 1, hi = n;
        while (lo < hi) {
            long mid = lo + ((hi - lo) >> 1);
            if (mid * (mid + 1) >> 1 < n)
                lo = mid + 1;
            else
                hi = mid;
        }
        return (long)lo * (lo + 1) >> 1 == n ? lo : lo - 1;
    }
};
```


2. ##### cummulation

```cpp
class Solution {
public:
    int arrangeCoins(int n) {
        int nrow = 1;
        while (n >= nrow) {
            n -= nrow;
            nrow++;
        }
        return nrow - 1;
    }
};
```

3. ##### math

- `x = (-b + sqrt(b^2 - 4ac)) / 2a`

```cpp
class Solution {
public:
    int arrangeCoins(int n) {
        return (int)(sqrt(2 * (long)n + 0.25) - 0.5);
    }
};
```