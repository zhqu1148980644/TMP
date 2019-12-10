### Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

```
Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
```

### Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.

### Solutions

1. #### bit operation O(log(n)2)

- Borrowed from other.
- Iteratively find the lagest divisor.
- The problem said the machine can only handle 32-bit integers. Need to find a way without long.

```c
int divide(int dividend, int divisor){
    if (dividend == INT_MIN  && divisor == -1)
        return INT_MAX;
    int neg =  (dividend < 0 ^ divisor < 0) ? 1 : 0;
    long dd = dividend; long ds = divisor;
    ds = (ds < 0) ? -ds : ds;
    dd = (dd < 0) ? -dd : dd;
    if (ds == 1) return neg ? -dd : dd;

    int res = 0;
    while (dd >= ds) {
        long m = ds; long n = 1;
        while ((m << 1) <= dd) {
            m <<= 1; // m = m * 2
            n <<= 1; // n = n * 2
        }
        dd -= m;
        res += n;
    }
    if (neg && res < INT_MIN) res = INT_MIN;
    if (!neg && res > INT_MAX) res = INT_MAX;
    return neg ? -res : res;
}
```
