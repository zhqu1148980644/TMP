---
title: Distinct Subsequences
date: 2021-01-04
---
Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

It's guaranteed the answer fits on a 32-bit signed integer.

Example 1:

Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^
Example 2:

Input: S = "babgbag", T = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^


#### Solutions

1. ##### backtrack

- TLE

```cpp
class Solution {
public:
    string s, t;
    int res = 0;

    void dfs(int si, int ti) {
        if (s.size() - si < t.size() - ti)
            return;
        if (ti == t.size()) {
            res++;
        }
        else {
            for (int i = si; i < s.size(); i++) {
                if (s[i] == t[ti]) {
                    dfs(i + 1, ti + 1);
                }
            }
        }
    }
    int numDistinct(string s, string t) {
        this->s = s; this->t = t;
        dfs(0, 0);
        return res;
    }
};
```

2. ##### backtrack with memoization

- `dp[si][ti]` represents the number of unique subsequences within `s[si:]` equals to `t[ti:]`

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int sn = s.size(), tn = t.size();
        if (sn < tn) return 0;
        vector<vector<int>> dp(sn + 1, vector<int>(tn + 1, -1));
        function<int(int, int)> solve = [&](int si, int ti) {
            if (sn - si < tn - ti) return 0;
            if (ti == tn) return 1;
            if (dp[si][ti] != -1) return dp[si][ti];
            int res = 0;
            for (int i = si; i < sn; i++) {
                if (s[i] == t[ti])
                    res += solve(i + 1, ti + 1);
            }
            return dp[si][ti] = res;
        };

        return solve(0, 0);
    }
};
```


2. ##### dynamic programming

- `dp[i][j]` represents the number of unique subsequences within `s[:i]` equals to `t[:j]`

- Note that we should set all `dp[i][-1]` to `1` to represent that the beginning of the subsequence equals to `t` can start at any place within `s`.

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        int sn = s.size(), tn = t.size();
        if (sn < tn) return 0;
        // must set dp[former positions of each t[0] in s][0] to 1
        vector<size_t> dp(sn + 1, 1);
        for (int i = 0; i < tn; i++) {
            vector<size_t> dp1(sn + 1);
            for (int j = 1; j <= sn; j++) {
                dp1[j] = dp[j - 1];
                // t[i] matches with s[j - 1], plus dp[i - 1][j - 1]
                if (t[i] == s[j - 1])
                    dp1[j] += dp[j - 1];
            }
            dp = move(dp1);
        }
        return dp[sn];
    }
};
```