---
title: Guess Number Higher or Lower
date: 2021-01-04
---
We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number is higher or lower.

You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):

- -1 : My number is lower
- 1 : My number is higher
- 0 : Congrats! You got it!

```
Example :

Input: n = 10, pick = 6
Output: 6
```


#### Solutions

1. ##### binary search

```cpp
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (guess(mid) == 1)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
};
```