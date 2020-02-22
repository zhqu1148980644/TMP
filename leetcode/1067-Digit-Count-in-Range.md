Given an integer d between 0 and 9, and two positive integers low and high as lower and upper bounds, respectively. Return the number of times that d occurs as a digit in all integers between low and high, including the bounds low and high.

 

```
Example 1:

Input: d = 1, low = 1, high = 13
Output: 6
Explanation: 
The digit d=1 occurs 6 times in 1,10,11,12,13. Note that the digit d=1 occurs twice in the number 11.

Example 2:

Input: d = 3, low = 100, high = 250
Output: 35
Explanation: 
The digit d=3 occurs 35 times in 103,113,123,130,131,...,238,239,243.
```
 

#### Note:

-    0 <= d <= 9
-    1 <= low <= high <= 2×10^8


#### Solutions

1. ##### math

- This problem is a generalization of `problem 233`.
- The method is the same as in `problem 233` except for the case when `d` equals to `0`. Since the highest number can not be `0`, we need to remove these impossible cases.
- For example:
    - When counting the number of `0` in the second lowest digit, `n = 123`.
    - Following the rule in `problem 233`, the number of 0 in this position is composed of two parts: 
        - The main part: `(223 / 100) * 10 = 20` ie: `01, 02, 03, ... 09   101, 102, 103 ... 109`. It's clear that the first `10` numbers are invalid.
        - The remainder part: `min(223 % 100 - 10 * 0 + 1, 10) = 10`, ie: `201 202 203 204 205 ... 209`. 
        - Thus the deduced count offsets the count of invalid numbers in the main part.

```c++
class Solution {
public:
    long digitsCount(int d, int n) {
        long res = 0;
        for (long num = 1; num <= n; num *= 10) {
            long base = num * 10;
            res += (n / base) * num + min(num, max(0l, (n % base) - (num * d) + 1));
            if (d == 0)
                // remove cases when: 0xxxx in the first part((n / base) * num)
                res -= num;
        }
        return res;
    }

    int digitsCount(int d, int low, int high) {
        return digitsCount(d, high) - digitsCount(d, low - 1);    
    }
};
```