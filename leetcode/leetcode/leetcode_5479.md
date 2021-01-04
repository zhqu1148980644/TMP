---
title: Thousand Separator
date: 2021-01-04
---
Given an integer n, add a dot (".") as the thousands separator and return it in string format.

 

Example 1:

Input: n = 987
Output: "987"
Example 2:

Input: n = 1234
Output: "1.234"
Example 3:

Input: n = 123456789
Output: "123.456.789"
Example 4:

Input: n = 0
Output: "0"
 

Constraints:

0 <= n < 2^31

#### Solutions

````cpp
class Solution {
public:
    string thousandSeparator(int n) {
        if (!n) return "0";
        string res;
        int len = 0;
        while (n) {
            res += ((n % 10) + '0');
            if (++len == 3) {
                len = 0;
                res += '.';
            }
            n /= 10;
        }
        if (res.size() && res.back() == '.')
            res.pop_back();
        return {res.rbegin(), res.rend()};
    }
};
```