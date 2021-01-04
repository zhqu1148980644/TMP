---
title:  Integer Break
date: 2021-01-04
---
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

```
Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.

Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
```

#### Note: You may assume that n is not less than 2 and not larger than 58.


#### Solutions

1. ##### dynamic programing O(n2)

```cpp
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j < i; j++) {
                dp[i] = max(dp[i], dp[i - j] * j);
                dp[i] = max(dp[i], j * (i - j));
            }

        return dp[n];
    }
};
```


2. ##### math O(1)

- reference: https://leetcode-cn.com/problems/integer-break/solution/zheng-shu-chai-fen-shu-xue-fang-fa-han-wan-zheng-t/
- The idea is to split the interger into multiple `3` and one `(2/3/4)`.
    - maximize `x^(n / x)`
    - `x^(n / x) == (x ^ (1/x)) ^ n`
    - equals to maximize `f(x) = x ^ (1 / x)`
    - log transform to `h(x) = ln(fx) =  (1/x) * ln(x)`
    - derivative of `h(x)` is `ln(x)/(x ^ 2) - 1/(x ^ 2)`
    - `when h(x) = 0` we have `x0 = e`
    - choose `x0 = 3` since `h(3) > h(2)`

```cpp
class Solution {
public:
    int integerBreak(int n) {
        if (n <= 3) return n - 1;
        if (n % 3 == 2)
            // 3 * 3 * 3... * 2
            return 2 * pow(3, (n - 2) / 3);
        else if (n % 3 == 1)
            // 3 * 3 * 3 .. * 2 * 2
            return 4 * pow(3, (n - 4) / 3);
        else
            // 3 * 3 * 3 * 3
            return pow(3, n / 3);
    }
};
```