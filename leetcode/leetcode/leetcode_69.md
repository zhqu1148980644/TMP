---
title: Sqrt(x)
date: 2021-01-04
---
#### Implement int sqrt(int x).

Compute and return the square root of x, where x is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

```
Example 1:

Input: 4
Output: 2
Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
```

#### Solutions

1. ##### brute force  O(log(n))

The problem does not require the decimal part.

```cpp
class Solution {
public:
    int mySqrt(int x) {
        long n = 0;
        while (n * n <= x) n++;
        return n - 1;
    }
};
```

2. ##### newton's method

- Find the sqrt of n is equal to solve the equation:
`x ** 2 = n` or `x ** 2 - n = 0`
- Use the Taylor expansion to approximate the function, we  keep the first order terms:
`f(x) = f(x0) + f'(x0) * (x - x0)`

- We are now at `x0`, apply our equation to this formula:
`0 = f(x0) + f'(x0) * (x - x0)`

- Solve this equation we can get the new `x`:
`x = x0 - f(x0) / f'(x0)`, then:
`x = (x0 + n / x0) / 2`

- In another perspective, we can see this iteration process as to find the next x by extending the current point's tangent till it intersect with `y = 0`.

```cpp
class Solution {
public:
    int mySqrt(int x) {
        long r = x;
        while (r * r > x) {
            r = (r + x / r) / 2;
        }
        return r;
    }
};
```

3. ##### bit operation O(log(log(n))) or O(1)

- This one is borrowed from others.
- The idea is to iteratilvely find the highest(most significant) bit to fill every bit of root.

```cpp
class Solution {
public:
    int mySqrt(int x) {
        long root = 0;
        // start checking at the 16'th bit or a higher one, make sure the square of root will not overflow.
        long bit = 1l << 16;
        while (bit) {
            // try to set this bit to True.
            root |= bit;
            if (root * root > x)
                // unset this bit in root as when this bit is set to true, the root * root will be greater than x.
                root ^= bit;
            // check the next less significant bit.
            bit >>= 1;
        }
        return root;
    }
};
```


