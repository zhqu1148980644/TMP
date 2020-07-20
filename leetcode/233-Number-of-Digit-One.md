Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

```
Example:

Input: 13
Output: 6 
Explanation: Digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
```

#### Solutions

1. ##### math

- reference: official answer
- Count the number of `1` in each digit.(10, 100, 1000...) and plus the number of `1` in the `remainder`. ie: `1234 % 1000, 1234 % 100, 1234 % 10`
- For example:
    - In each `10` base, there exists `1  1` in the lowest digit, ie: `1` or `11` or `21` ...
    - In each `100` base, there exists `10  1` in the second lowest digit, ie: `x10, x11, x12, x13 ... x19`
    - In each `1000` base, there exists `100  1` in the third lowest digit, ie: `x100, x101, ... x199`
    - `(n / base) * (base / 10)`
    - For remainder:
        - `1650 % 100 = 50`, as `50` is larger than `19`, this remainder contains exactly the same number of `1` as the base `100`. ie: `10`.
        - `1609 % 100 = 9`, as `9` is smaller than `10`, the remaining number of `1` in base 100 is `0`.
    - `0 <= (n % base) - (base / 10) + 1 <= base / 10`

```c++
class Solution {
public:
    int countDigitOne(int n) {
        long res = 0;
        for (long num = 1; num <= n; num *= 10) {
            // d is base
            long base = num * 10;
            // full part plus remaining part
            res += (n / base) * num + min(max((n % base) - num + 1, 0l), num);
        }
        return res;
    }
};
```


2. ##### digit dp
