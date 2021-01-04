---
title: Integer Replacement
date: 2021-01-04
---
Given a positive integer n and you can do operations as follow:

If n is even, replace n with n/2.
If n is odd, you can replace n with either n + 1 or n - 1.
What is the minimum number of replacements needed for n to become 1?

Example 1:

Input:
8

Output:
3

Explanation:
8 -> 4 -> 2 -> 1
Example 2:

Input:
7

Output:
4

Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1

#### Solutions

1. ##### dfs

```cpp
class Solution {
public:
    int integerReplacement(int n) {
        if (n == INT_MAX) return 32;
        if (n == 1) return 0;
        if (n % 2)
            return 1 + min(integerReplacement(n + 1), integerReplacement(n - 1));
        else
            return 1 + integerReplacement(n >> 1);
    }
};
```


2. ##### bit operations

- when the current number's bits are `bin(n) = xx11`:
    - if choose `n - 1`, xx11 -> xx10 -> xx1 -> xx0
    - if choose `n + 1`, xx11 -> xx00 -> xx0 ->  xx
    - Except for number `3`, other numbers with the lowest two bits set prefer `n + 1`.
- When the number is `bin(n) = xx10`, for the same reason, more right shift operations can be achieved by chooseing `n + 1`.

```cpp
class Solution {
public:
    int integerReplacement(int n) {
        if (n == INT_MAX) return 32;
        int res = 0;
        while (n != 1) {
            if (n % 2 == 0)
                n >>= 1;
            else if (n != 3 && (n >> 1 & 1))
                n++;
            else
                n--;
            res++;
        }
        return res;
    }
};
```

or

```cpp
class Solution {
public:
    int integerReplacement(int n) {
        if (n == INT_MAX) return 32;
        int res = 0;
        while (n != 1) {
            if (n % 2 == 0)
                n >>= 1;
            else if (n != 3 && (n >> 1 & 1)) {
                n++; n >>= 2; res += 2;
            }
            else
                n--;
            res++;
        }
        return res;
    }
};
```