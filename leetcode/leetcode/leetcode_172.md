---
title: Factorial Trailing Zeroes
date: 2021-01-04
---
#### Given an integer n, return the number of trailing zeroes in n!.

```
Example 1:

Input: 3
Output: 0
Explanation: 3! = 6, no trailing zero.
Example 2:

Input: 5
Output: 1
Explanation: 5! = 120, one trailing zero.
```

#### Note: Your solution should be in logarithmic time complexity.

#### Solutions

- since 0 comes from  `2 x 5` and `factoral(5)` must contain `2`, the number of zeros equals to number of `5` in `1 x 2 x 3 ... x n`

1. ##### 

- When counting how many 5 appeared in the multiplication, we can simply use `n / 5`.
- however `5 ** i` also contains 5. ie: `25 125 ...`
    - (1 * 5 * 5) .. (2 * 5 * 5) .. (3 * 5 * 5)
    - (2 * 5 * 5 * 5) .. (2 * 5 * 5 * 5)
    - ....
- Thus the number of traling zeros is the sum count of `n/5`   `n/25`  `n/125` .....

```cpp
class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0;
        while (n) {
            n /= 5;
            count += n;
        }
        return count;
    }
};

```