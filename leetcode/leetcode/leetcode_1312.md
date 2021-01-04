---
title: Minimum Insertion Steps to Make a String Palindrome
date: 2021-01-04
---
#### Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.

 

```
Example 1:

Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we don't need any insertions.

Example 2:

Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:

Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".

Example 4:

Input: s = "g"
Output: 0

Example 5:

Input: s = "no"
Output: 1
```

 

#### Constraints:

-    1 <= s.length <= 500
-    All characters of s are lower case English letters.


#### Solutions

1. ##### dynamic programming

- similar to `problem 516`
- `dp[i][j]` represents the minimum number of steps to make `s[i:j]` a palindrome, then:
    - if `s[i] == s[j]`, `dp[i][j] = dp[i + 1][j - 1]`. It's definitely a palindrome.
    - else `dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1`. Insert `s[i]` at `s[j + 1]` or insert `s[j]` at the front of `s[i:j]` makes `s[i: j - 1]/s[i + 1: j]` a palindrome.

```cpp
class Solution {
public:
    int minInsertions(string s) {
        int len = s.size();
        vector<vector<int>> dp(len, vector<int>(len, 0));

        for (int i = len - 1; i >= 0; i--)
            for (int j = i; j < len; j++) {
                if (i == j)
                    dp[i][j] = 0;
                else {
                    if (s[i] == s[j])
                        dp[i][j] = dp[i + 1][j - 1];
                    else
                        dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
                }
            }

        return dp[0][len - 1];
    }
};
```

- The same as in `problem 516`, we can simply use a `1d` table.

```cpp
class Solution {
public:
    int minInsertions(string s) {
        int len = s.size();
        vector<int> dp(len, 0);

        for (int i = len - 1; i >= 0; i--) {
            int prel = dp[i] = 0;
            for (int j = i + 1; j < len; j++) {
                int down = dp[j];
                if (s[i] == s[j])
                    dp[j] = prel;
                else
                    dp[j] = min(down, dp[j - 1]) + 1;
                prel = down;
            }
        }

        return dp[len - 1];
    }
};
```