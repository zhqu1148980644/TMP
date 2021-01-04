---
title: Broken Calculator
date: 2021-01-04
---
On a broken calculator that has a number showing on its display, we can perform two operations:

Double: Multiply the number on the display by 2, or;
Decrement: Subtract 1 from the number on the display.
Initially, the calculator is displaying the number X.

Return the minimum number of operations needed to display the number Y.

 

Example 1:

Input: X = 2, Y = 3
Output: 2
Explanation: Use double operation and then decrement operation {2 -> 4 -> 3}.
Example 2:

Input: X = 5, Y = 8
Output: 2
Explanation: Use decrement and then double {5 -> 4 -> 8}.
Example 3:

Input: X = 3, Y = 10
Output: 3
Explanation:  Use double, decrement and double {3 -> 6 -> 5 -> 10}.
Example 4:

Input: X = 1024, Y = 1
Output: 1023
Explanation: Use decrement operations 1023 times.
 

Note:

1 <= X <= 10^9
1 <= Y <= 10^9

#### Solutions

1. ##### greedy

- reference: https://leetcode-cn.com/problems/broken-calculator/solution/tan-xin-suan-fa-ji-qi-zheng-ming-by-lenn123/
- The idea is to reach back to X from Y.
    - if `Y < X`, move `Y` forward `X - Y` steps.
    - else if `Y % 2 == 0`, divide by 2, else move 1 step forward.

```cpp
class Solution {
public:
    int brokenCalc(int X, int Y) {
        int res = 0;
        while (Y > X) {
            res++;
            if (Y % 2 == 1)
                Y++;
            else
                Y /= 2;
        }

        return res + X - Y;
    }
};
```

2. ##### math + greedy


- Suppose x has been increased by `n1` multiplication and `n2` decutions. we have:
    - Without dedution, after n1 multiplution: `pos = x * 2^n1`.
    - Suppose deductions are conducted `a` times before the first multiplication, then `pos = (x - a) * 2^n1  == x * 2^n1 - a * 2^n1`
    - Suppose deductions are conducted `b` times right after the first multiplication, then `pos = (x * 2 - 1) * 2^(n1 - 1) == x * 2^n1 - b * 2^(n - 1)`
    - For deductions happened in any place, we have: `Y = X * 2^n1 - a * 2^n1 - b * 2^(n1 - 1) - c * 2^(n1 -2) ... x * 1  s.t a,b,c .. >= 0`
- Thus the problem equals to find the minimum sum of `n1 + a + b + c...`. To minimize this summation, we eagerly choose the maximum `n1`, then `a`.....
- Since x can only choose to multiply 2 or deduce by 1, `x` needs to be increased to at least `Y` with `n1` multiplication.


```cpp
class Solution {
public:
    int brokenCalc(int X, int Y) {
        int n1 = 0, n2 = 0;
        // move to at least Y
        while (X < Y) {
            X *= 2; n1++;
        }
        if (X == Y) return n1;
        // check the number of steps to subtract by 1 eagerly.
        int dis = X - Y;
        for (int i = n1; i >= 0 && dis > 0; i--) {
            int base = pow(2, i);
            int maxd = dis / base;
            dis -= maxd * base; 
            n2 += maxd;
        }

        return n1 + n2;   
    }
};
```