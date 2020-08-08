### Implement pow(x, n), which calculates x raised to the power n (xn).

```
Example 1:

Input: 2.00000, 10
Output: 1024.00000
Example 2:

Input: 2.10000, 3
Output: 9.26100
Example 3:

Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
```

### Note:

-100.0 < x < 100.0
n is a 32-bit signed integer, within the range [−231, 231 − 1]


### Solutions

1. #### recursion O(log(n))

- Observation: 
    - x * 2n = (x * n) * (x * n) = (x * n) ** 2
    - x * (2n + 1) = (x * n) ** 2 * x
- When the n increases with n, the bit numbers of exponent increases with log2(n).
- Time complexity can be reduced to log2(n)

```c++
class Solution {
public:
    double pow(double x, long n) {
        if (n == 1) return x;
        double half = pow(x, n >> 1);
        return n & 1 ? x * half * half : half * half;
    }
    double myPow(double x, int n) {
        if (x == 1 || x == 0) return x;
        if (n == 0) return 1;
        if (n < 0) x = 1 / x;
        // incase of n == INT_MIN, abs(INT_MIN) would cuase overflow
        long N = abs(long(n));
        return pow(x, N);
    }
};
```

2. ##### bit representation

- `x^4 = x^0b100 = x^(2^2 * 1 + 2^1 * 0 + 2^0 * 0) = x^(2^2) * X^0 * X^0`

```c++
class Solution {
public:
    double myPow(double x, int n) {
        long N = n;
        if (N < 0) {
            x = 1.0 / x;
            N = -N;
        }

        double res = 1;
        while (N) {
            // the current bit is 1
            if (N & 1)
                res *= x;
            // x^(2^n)
            x *= x;
            N >>= 1;
        }

        return res;
    }
};
```

