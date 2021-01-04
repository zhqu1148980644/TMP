---
title: Rotated Digits
date: 2021-01-04
---
X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X.  Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other (on this case they are rotated in a different direction, in other words 2 or 5 gets mirrored); 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation: 
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Note:

N  will be in range [1, 10000].

#### Solutions

1. ##### straight forward O(32n)

```cpp
class Solution {
public:
    vector<int> valid = {1, 1, 2, 0, 0, 1, 1, 0, 1, 1};
    vector<int> unsame = {0, 0, 1, 1, 1, 1, 1, 1, 0, 1};
    inline bool isgood(int n) {
        int uneq = 0;
        while (n) {
            int mod = n % 10;
            if (!valid[mod]) return false;
            uneq += unsame[mod];
            n /= 10;
        }
        return uneq;
    }
    int rotatedDigits(int N) {
        int res = 0;
        for (int i = 1; i <= N; i++)
            res += isgood(i);
        
        return res;
    }
};
```

2. ##### dynamic programming O(n) S(n)

```cpp
class Solution {
public:
    int rotatedDigits(int N) {
        // 0 represent the number contains only 0/1/8
        // -1 represent the numer is not a good number
        // 1 good number
        vector<int> dp = {0, 0, 1, -1, -1, 1, 1, -1, 0, 1};
        dp.resize(N + 1);
        int res = 0;
        for (int n = 1; n <= N; n++) {
            int mod = n % 10, prev = n / 10;
            if (dp[mod] == -1 || dp[prev] == -1)
                dp[n] = -1;
            else if (!dp[mod] && !dp[prev])
                dp[n] = 0;
            else {
                res += dp[n] = 1;
            }
        }
        return res;
    }
};
```

3. ##### dynamic programming O(1)/O(log(n))

- reference: https://leetcode.com/problems/rotated-digits/discuss/116530/O(logN)-Time-O(1)-Space
- `dp[i]` represents the number of good numbers start with `prefix to_string(N)[:i)`.
- Then the total number equals to `dp[0] + dp[1] + .... dp[len(str(N)) + 1]`
- We denote `{0, 1, 8}` as group 1 and `{0, 1, 2, 5, 6, 8, 9}` as group 2.
- For example:
    - `dp[0]` means no digits has been settled, for `N = 4712` as example
    - `dp[0]` represents numbers `****`, they can be further grouped into 3 groups.
        - number start with `0`, then the left 3 numbers can be randomly choosed from group2, and the total number of pertutations are `7 ** 3`, while within those pertuations, there are `3 ** 3` numbers are all composed of `0, 1, 8`, which should be excluded. `dp[0][0] = 7 ** 3 - 3 ** 3`
        - number start with `1`, `dp[0][1] = 7 ** 3`(No need to deduce 3^3 as the current number is 1)
        - number start with `2`, `dp[0][2] = 7 ** 3`
        - number start with `3`, `3` is not a valid number, `dp[0][3] = 0`
    - `dp[1]` represents numbers `4***`, can be grouped into `40**`, `41**`, .... `46**`.
    - `dp[2]` represents numbers `47**`, as the current number already contains invalid number `7`, all numbers with this prefix will be invalid.
    - `dp[2] = dp[3] = dp[4] = 0`

```cpp
class Solution {
public:
    int rotatedDigits(int N) {
        string ns = to_string(N);
        int n = ns.size(), res = 0;
        vector<int> set1 = {1, 1, 0, 0, 0, 0, 0, 0, 1, 0};
        vector<int> set2 = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1};
        bool issubset1 = true, issubset2 = true; 
        for (int i = 0; i < n; i++) {
            int curd = ns[i] - '0';
            for (int d = 0; d < curd; d++) {
                if (issubset2 && set2[d])
                    res += pow(7, n - i - 1);
                // runs only when prefix[:i) are all 0/1/8
                if (issubset1 && set1[d])
                    res -= pow(3, n - i - 1);
            }
            // the current digit is invalid, all numbers followed with this prefix will also be invalid
            if (!set2[curd]) return res;
            if (issubset1) {
                if (set2[curd] && !set1[curd])
                    issubset1 = false;
            }
        }
        //  Check for self
        return res + (issubset2 && !issubset1);
    }
};
```