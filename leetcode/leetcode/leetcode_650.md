---
title: 2 Keys Keyboar
date: 2021-01-04
---
Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
 

Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.

Example 1:

Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
 

Note:

The n will be in the range [1, 1000].

#### Solutions

1. ##### Prime decomposition

- If the current number is a number denoted a `n` with valid divisors(prime), the smallest divisor is `d`, then `n` must be constructed from `1` copy and `d` times paste of `n/d`.

```cpp
class Solution {
public:
    int minSteps(int n) {
        if (n == 0) return 0;
        int res = 0;
        while (n != 1) {
            int i, find = 0;
            for (i = 2; i * i <= n; i++)
                if (n % i == 0) {
                    find = true;
                    break;
                }
            if (find) {
                res += i; n /= i;
            }
            else {
                res += n; n = 1;
            }
        }
        return res;
    }
};
```