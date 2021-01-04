---
title: Happy Number
date: 2021-01-04
---
#### Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

```
Example: 

Input: 19
Output: true
Explanation: 
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

#### Solutions

1. ##### Straight forward

```cpp
class Solution {
public:
    bool isHappy(int n) {
    unordered_set<int> s;
    while (!s.count(n)) {
        s.insert(n);
        int res = 0;
        while (n) {
            res += (n % 10) * (n % 10);
            n = n / 10;
        }
        if (res == 1) return true;
        else n = res;
    }
    return false;
    }
};
```

2. ##### two pointer in cycle

- The sequence of happy numbers or unhappy numbers is a endless cycle.

```cpp
int next(int n ) {
    int res = 0;
    while (n) {
        res += (n % 10) * (n % 10);
        n /= 10;
    }
    return res;
}

class Solution {
public:
    bool isHappy(int n) {
        int slow = n, fast = n;
        do {
            slow = next(slow);
            fast = next(next(fast));
        } while (slow != fast);
        return slow == 1;
    }
};
```

3. ##### Use rules

- Every unhappy number will meet number 4.


```cpp
class Solution {
public:
    int next(int n) {
        int res = 0;
        while (n) {
            res += (n % 10) * (n % 10);
            n /= 10;
        }
        return res;
    }
    bool isHappy(int n) {
        while (n != 1 && n > 4)
            n = next(n);
        return n == 1;
    }
};
```