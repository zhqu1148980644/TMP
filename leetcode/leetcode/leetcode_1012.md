---
title: Numbers With Repeated Digits
date: 2021-01-04
---
Given a positive integer N, return the number of positive integers less than or equal to N that have at least 1 repeated digit.

 

Example 1:

Input: 20
Output: 1
Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
Example 2:

Input: 100
Output: 10
Explanation: The positive numbers (<= 100) with atleast 1 repeated digit are 11, 22, 33, 44, 55, 66, 77, 88, 99, and 100.
Example 3:

Input: 1000
Output: 262
 

Note:

1 <= N <= 10^9

#### Solutions

1. ##### dynamic programming

- reference :https://leetcode.com/problems/numbers-with-repeated-digits/discuss/256725/JavaPython-Count-the-Number-Without-Repeated-Digit
- It's hard to directly count the number of integers with duplicate digits, however, counting the number of integers without duplicate digit is much easier.
- Thus the answer equals to `N - num_with_no_duplicate`
- `dp[i]` represents the current checking numbers's prefix is `str(N)[:i)`.
    - Basically, we are checking and counting all numbers in the order of prefix.

```cpp
class Solution {
public:
    // A(m, n) means the number of permutaion when select n from m number
    int A(int m, int n) {
        if (n > m) return 0;
        int res = 1;
        for (int i = 0; i < n; i++)
            res *= m--;
        return res;
    }
    int numDupDigitsAtMostN(int N) {
        // here is the trick, may be N itself without  duplicate digit
        string s = to_string(N + 1);

        int res = 0, len = s.size();
        // count num of intergers without duplicate digits with les number of digits than N
        for (int n = 1; n < len; n++) {
            // the first digit can be len(1...9) = 9;
            // later digits can be (len(0...9) = 10) - 1(except the first digit)
            res += 9 * A(10 - 1, n - 1);
        }
        
        // count num of integers without duplicate digit with the same number of digits than N
        vector<bool> seen(10);
        for (int i = 0; i < len; i++) {
            int maxd = s[i] - '0';
            for (int d = 0; d < maxd; d++) {
                if (i == 0 && d == 0) continue;
                if (!seen[d])
                    // except former digit and the current digit
                    res += A(10 - i - 1, len - i - 1);
            }
            if (seen[maxd]) break;
            seen[maxd] = true;
        }

        return N - res;
    }
};
```