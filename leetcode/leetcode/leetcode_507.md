---
title: Perfect Number
date: 2021-01-04
---
We define the Perfect Number is a positive integer that is equal to the sum of all its positive divisors except itself.

Now, given an integer n, write a function that returns true when it is a perfect number and false when it is not.
Example:
Input: 28
Output: True
Explanation: 28 = 1 + 2 + 4 + 7 + 14
Note: The input number n will not exceed 100,000,000. (1e8)

#### Solutions

1. ##### straight forward O(n^1/2)

```cpp
class Solution {
public:
    bool checkPerfectNumber(int num) {
        if (num <= 1) return false;
        int sum = 1, i = 2;
        for (; i * i <= num; i++) {
            if (num % i == 0)
                sum += i + num / i;
        }
        if (i * i == num) sum -= i;
        return sum == num;
    }
};
```

2. ##### math

- perfect numbers can be represented as `2^(p-1) * (2^p  -  1)` with p is prime number.