---
title: Prime Palindrome
date: 2021-01-04
---
Find the smallest prime palindrome greater than or equal to N.

Recall that a number is prime if it's only divisors are 1 and itself, and it is greater than 1. 

For example, 2,3,5,7,11 and 13 are primes.

Recall that a number is a palindrome if it reads the same from left to right as it does from right to left. 

For example, 12321 is a palindrome.

 

Example 1:

Input: 6
Output: 7
Example 2:

Input: 8
Output: 11
Example 3:

Input: 13
Output: 101
 

Note:

1 <= N <= 10^8
The answer is guaranteed to exist and be less than 2 * 10^8.

#### Solutions

1. ##### math O(N / 2)

- Borrowed from others
- All palindrome numbers(except for 11) with even number of digits is not a prime number(n % 11 == 0). ie: pass all numbers with(len(n) % 2 == 0).


```cpp
class Solution {
public:
    inline bool isprime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0)
                return false;
        return true;
    }
    inline bool ispalin(int N) {
        int rn = 0, n = N;
        while (N) {
            rn = rn * 10 + (N % 10);
            N /= 10;
        }
        return rn == n;
    }
    int primePalindrome(int N) {
        while (true) {
            if (N == 10 || N == 11) return 11;
            int len = 0, n = N;
            while (n && ++len && (n /= 10));
            if (len % 2 == 0)
                N = pow(10, len) - 1;
            else if (ispalin(N) && isprime(N))
                return N;
            N++;
        }
        return 1;
    }
};
```