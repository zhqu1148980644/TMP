---
title: Nth Magical Number
date: 2021-01-04
---
A positive integer is magical if it is divisible by either A or B.

Return the N-th magical number.  Since the answer may be very large, return it modulo 10^9 + 7.

 

Example 1:

Input: N = 1, A = 2, B = 3
Output: 2
Example 2:

Input: N = 4, A = 2, B = 3
Output: 6
Example 3:

Input: N = 5, A = 2, B = 4
Output: 10
Example 4:

Input: N = 3, A = 6, B = 4
Output: 8
 

Note:

1 <= N <= 10^9
2 <= A <= 40000
2 <= B <= 40000

#### Solutions

1. ##### simulation/merge sorted list O(n)

- TLE

```cpp
class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {
        const int MOD = 1e9 + 7;
        if (A == B) return ((long long)A * N) % MOD; 
        int a = A, b = B;
        N--;

        while (N--) {
            int minv = min(a, b);
            if (minv == a)
                a = (a + A) % MOD;
            if (minv == b)
                b = (b + B) % MOD;
        }
        
        return min(a, b);
    }
};
```

2. ##### binary search O(nlog(n)) with n = N*min(A, B)

- least common multiple equals to `(a * b) / gcd(a, b)`.

```cpp
class Solution {
public:
    int gcd(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }
    int nthMagicalNumber(int N, int A, int B) {
        long long lo = min(A, B), hi = (long long)N * min(A, B);
        int lm = A * B / gcd(A, B);
        while (lo < hi) {
            long long mid = lo + ((hi - lo) >> 1);
            long long n1 = mid / A, n2 = mid / B, ndup = mid / lm;
            if (n1 + n2 - ndup < N)
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo % 1000000007;
    }
};
```

3. ##### math O(1)

- Check the official answer.

```cpp

```