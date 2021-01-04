---
title: Consecutive Numbers Su
date: 2021-01-04
---
Given a positive integer N, how many ways can we write it as a sum of consecutive positive integers?

```
Example 1:

Input: 5
Output: 2
Explanation: 5 = 5 = 2 + 3

Example 2:

Input: 9
Output: 3
Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4

Example 3:

Input: 15
Output: 4
Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5

Note: 1 <= N <= 10 ^ 9.
```

#### Solutions

1. ##### math  O(sqrt(n))

- reference: https://leetcode-cn.com/problems/consecutive-numbers-sum/solution/pythonchao-hao-li-jie-de-onsuan-fa-by-yybeta/
- Formulate every cases with increasing numbers:
    - N can be decomposed into `1` number: `N`.
    - N can be decomposed into `2` number: `x, x + 1` only if `(N - 1) / 2` is an integer.
    - N can be decomposed into `3` number: `x, x + 1, x + 2` only if `(N - 1 - 2) / 3` is an integer.
    - ....
- Time complexity: `1 + 2 + 3 + 4 ... + n = n(n + 1) / 2`, thus the number of while loops will run `sqrt(N)` times untill N is deduced to a number smaller than 0.

```cpp
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int cnt = 0, num = 1;
        while (N >= num) {
            // N / num  is an interger
            cnt += N % num == 0;
            N -= num;
            num++;
        }

        return cnt;
    }
};
```


2. ##### sum of arithmetic sequence  O(n)

-reference: https://leetcode-cn.com/problems/consecutive-numbers-sum/solution/qiao-yong-zhi-yin-shu-fen-jie-by-erik_chen/
- The sum of `x` consecutive numbers `a + (a + 1) + (a + 2) + ... + (a + x - 1)` is `x(a + (a + x - 1)) / 2`
- ie: `2n = x * c` only if `x` and `c` are intergers.
    - `2n % x = 0` and  x * x < 2n
    - `2n / x - x = 2a - 1  % 2 = 1`
```cpp
class Solution {
public:
    int consecutiveNumbersSum(int N) {
        int cnt = 0, x = 1, n = 2 * N;
        while (x * x < n) {
            if (n % x == 0 && (n / x - x) % 2 == 1)
                cnt++;
            x++;
        }
        return cnt;
    }
};
```
