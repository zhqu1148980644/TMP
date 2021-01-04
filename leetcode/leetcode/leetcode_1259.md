---
title: Handshakes That Don't Cross
date: 2021-01-04
---
You are given an even number of people num_people that stand around a circle and each person shakes hands with someone else, so that there are num_people / 2 handshakes total.

Return the number of ways these handshakes could occur such that none of the handshakes cross.

Since this number could be very big, return the answer mod 10^9 + 7



```
Example 1:

Input: num_people = 2
Output: 1

Example 2:

Input: num_people = 4
Output: 2
Explanation: There are two ways to do it, the first way is [(1,2),(3,4)] and the second one is [(2,3),(4,1)].

Example 3:

Input: num_people = 6
Output: 5

Example 4:

Input: num_people = 8
Output: 14
```



#### Constraints:

-    2 <= num_people <= 1000
-    num_people % 2 == 0


#### Solutions

1. ##### dynamic programming

- `dp[i]` represents the total number of uncrossed handshakes.
- For example: if there are `5` pair of person.
    - randomly choose one pair to handshake, as handshakes can not be crossed, people are separated into two unconnected components which are two subproblem.
    - i.e.: `0-1-4  1-1-3 2-1-2 3-1-1 4-1-0`
    - `dp[i] = dp[0][n - 1] +  dp[1][n - 2] + dp[2][n - 3] ....`

```cpp
class Solution {
public:
    int numberOfWays(int num_people) {
        int numpair = num_people / 2;
        long mod = 1000000000 + 7;
        vector<long> dp(numpair + 1, 0);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= numpair; i++) {
            for (int j = 0; j <= (i - 1) / 2; j++) {
                if (j == i - j - 1)
                    dp[i] += dp[j] * dp[i - 1 - j];
                else
                    dp[i] += 2 * (dp[j] * dp[i - 1 - j]);
                dp[i] = dp[i] % mod;
            }
        }
        return dp[numpair];
    }
};
```

2. ##### Catalan

- The dp formula is exactly the definition of catalan numbers.
- `catlan(n) = C(2n, n) / (n + 1)`
    - `C(n, k) = n! / (k! * (n - k)!)`
    - `catlan(n) = (2n)! / (n! * (n + 1)!)`

```python
class Solution:
    def numberOfWays(self, num_people: int) -> int:
        from math import factorial
        n = num_people // 2
        return (factorial(2 * n) // (factorial(n) * factorial(n + 1))) % (1000000000 + 7)
```