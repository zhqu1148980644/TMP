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

1. #### bit operation  O(log(n))

- Observation: 
    - x * 2n = (x * n) * (x * n) = (x * n) ** 2
    - x * 2n = (x * n) ** 2 * x
- When the n increases with n, the bit numbers of exponent increases with log2(n).
- Time complexity can be reduced to log2(n)

```c++
#define sqr(x) ((x) * (x))
double pow1(double x, long n) {
    if (n == 0) return 1.0;
    return (n & 1) ? sqr(pow1(x, n >> 1)) * x : sqr(pow1(x, n >> 1));
}

double myPow(double x, int n){
    if (!x) {
        return 0;
    }
    else if (x == 1.0) {
        return 1.0;
    } else if (x == -1) {
        return ((n % 2) == 0) ? 1.0 : -1.0;
    } else {
        long N = n;
        if (n > 0) {
            return pow1(x, N);
        } else {
            return 1.0 / pow1(x, -N);
        }
    }
}
```



