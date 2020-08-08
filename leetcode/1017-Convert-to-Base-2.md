Given a number N, return a string consisting of "0"s and "1"s that represents its value in base -2 (negative two).

The returned string must have no leading zeroes, unless the string is "0".

 

Example 1:

Input: 2
Output: "110"
Explantion: (-2) ^ 2 + (-2) ^ 1 = 2
Example 2:

Input: 3
Output: "111"
Explantion: (-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3
Example 3:

Input: 4
Output: "100"
Explantion: (-2) ^ 2 = 4
 

Note:

0 <= N <= 10^9

#### Solutions

1. ##### straight forward

- reference: comments in https://leetcode.com/problems/convert-to-base-2/discuss/265507/JavaC%2B%2BPython-2-lines-Exactly-Same-as-Base-2
- reference: https://en.wikipedia.org/wiki/Negative_base#Calculation
    - this links says there is no negative remainders.
- reference: https://en.wikipedia.org/wiki/Positional_notation#Base_conversion

```c++
class Solution {
public:
    string baseconvert(int n, int k) {
        if (n == 0) return "0";
        string res;
        while (n != 0) {
            // remainder will be negative only when n < 0
            int remainder = n % k;
            n /= k;
            // here is the difference compared to positive base
            // get a positive remainder if needed
            if (remainder < 0) {
                remainder += -k;
                n += 1;
            }
            res.push_back(remainder + '0');
        }

        return {res.rbegin(), res.rend()};
    }
    string baseNeg2(int N) {
        return baseconvert(N, -2);
    }
};
```

or

```c++
class Solution {
public:
    string baseNeg2(int N) {
        if (N == 0 || N == 1) return to_string(N);
        // reference : https://leetcode.com/problems/convert-to-base-2/discuss/265507/JavaC++Python-2-lines-Exactly-Same-as-Base-2/256530
        // here is the trick
        // N >> 1 != N / 2 when N is negative number
        // for most compilers, (negative right shift) will set the most significant bit to 1, while it's not the case for positive number
        // so when N < 0, N >> 1 == N / 2 - 1, -(N >> 1) == abs(N) / 2 + 1
        // when N > 0, N >> 1 == N / 2
        else return baseNeg2(-(N >> 1)) + to_string(N & 1);
    }
};
```