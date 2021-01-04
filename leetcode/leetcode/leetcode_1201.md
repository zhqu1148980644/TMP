---
title: Ugly Number III
date: 2021-01-04
---
Write a program to find the n-th ugly number.

Ugly numbers are positive integers which are divisible by a or b or c.

 

Example 1:

Input: n = 3, a = 2, b = 3, c = 5
Output: 4
Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
Example 2:

Input: n = 4, a = 2, b = 3, c = 4
Output: 6
Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4th is 6.
Example 3:

Input: n = 5, a = 2, b = 11, c = 13
Output: 10
Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5th is 10.
Example 4:

Input: n = 1000000000, a = 2, b = 217983653, c = 336916467
Output: 1999999984
 

Constraints:

1 <= n, a, b, c <= 10^9
1 <= a * b * c <= 10^18
It's guaranteed that the result will be in range [1, 2 * 10^9]

#### Solutions

- The same as problem 878
- Note that this problem differs with `problem ugly number II` in the definition of ugly number. ie: from factorization to division.

1. ##### merge sorted list O(n)

- TLE

```cpp
class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        int A = a, B = b, C = c;
        n--;

        while (n--) {
            int minv = min(A, min(B, C));
            if (minv == A)
                A = A + a;
            if (minv == B)
                B = B + b;
            if (minv == C)
                C = C + c;
        }

        return min(A, min(B, C));
    }
};
```

2. ##### binary search

```cpp
class Solution {
public:
    inline size_t gcd(size_t a, size_t b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    int nthUglyNumber(int n, int a, int b, int c) {
        size_t lcmab = (size_t)a * b / gcd(a, b);
        size_t lcmac = (size_t)a * c / gcd(a, c);
        size_t lcmbc = (size_t)b * c / gcd(b, c);
        size_t lcmabc = (size_t)lcmab * c / gcd(lcmab, c);

        size_t lo = min(a, min(b, c)), hi = lo * n;
        while (lo < hi) {
            size_t mid = lo + ((hi - lo) >> 1);
            size_t cnt = mid / a + mid / b + mid / c;
            size_t dup = mid / lcmab + mid / lcmbc + mid / lcmac - mid / lcmabc;
            if (cnt - dup < n)
                lo = mid + 1;
            else
                hi = mid;
        }

        return lo;
    }
};
```