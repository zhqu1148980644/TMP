A string of '0's and '1's is monotone increasing if it consists of some number of '0's (possibly 0), followed by some number of '1's (also possibly 0.)

We are given a string S of '0's and '1's, and we may flip any '0' to a '1' or a '1' to a '0'.

Return the minimum number of flips to make S monotone increasing.

 

Example 1:

Input: "00110"
Output: 1
Explanation: We flip the last digit to get 00111.
Example 2:

Input: "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.
Example 3:

Input: "00011000"
Output: 2
Explanation: We flip to get 00000000.
 

Note:

1 <= S.length <= 20000
S only consists of '0' and '1' characters.

#### Solutions

1. ##### dynamic programming

- `dp1` represents the minimum number of swaps to make the prefix be monotone increasing with the last character(may be swapped) as `1`.

```c++
class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int dp0 = 0, dp1 = 0;
        for (auto c : S)
            if (c == '0')
                dp1 = min(dp0, dp1) + 1;
            else {
                dp1 = min(dp0, dp1);
                dp0 = dp0 + 1;
            }

        return min(dp0, dp1);
    }
};
```

2. ##### prefix sum

- Iterating all possible i, swap the left side into 0s, nad wap the other side into 1s, these two sides can be 0 sized.

```c++
class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int n = S.size(), sum = 0;
        vector<int> sums(n + 1);
        for (int i = 0; i < n; i++)
            sums[i + 1] = sum += (S[i] == '1');

        int res = n;
        for (int i = 0; i <= n; i++) {
            int nr0 = (n - i) - (sum - sums[i]);
            res = min(res, sums[i] + nr0);
        }
        return res;
    }
};
```