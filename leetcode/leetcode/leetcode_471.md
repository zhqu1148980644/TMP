---
title: Encode String with Shortest Length
date: 2021-01-04
---
#### Given a non-empty string, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

#### Note:

-    k will be a positive integer and encoded string will not be empty or have extra space.
-    You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
-    If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.

 

```
Example 1:

Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.

 

Example 2:

Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.

 

Example 3:

Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".

 

Example 4:

Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".

 

Example 5:

Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
```


#### Solutions

- Use method in `problem 459` for checking if there are repeated pattern in a certain string.

1. ##### dynamic programming with recursion

- top down recursive method.
- Denote `dp[i][j]` as the encoded shortest string of substring `s[i:j]`
- `dp[i][j]` can be calculated by:
    - If `s[i:j]` is made of repeated pattern `p` with `k` occurrences, `dp[i][j]` can be represented by `k[p]`.
    - Else, divide `s[i:j]` into two parts, `dp[i][j]` can be represented by `dp[i][k] + dp[k + 1][j] i <= k < j`, and choose the shortest one among all possibilities.

```cpp
class Solution {
public:
    const string & solve(string & s, vector<vector<string>> & dp, int i, int j) {
        if (i > j) return "";
        if (dp[i][j].size())
            return dp[i][j];
        string & res = dp[i][j];
        res = s.substr(i, j - i + 1);
        // if the length of substring is smaller than 5, it can't be shorter.
        // ie: `4[c]` has length 4
        if (res.size() < 5)
            return res;
        // find the repeated pattern.
        int find = res.size();
        if ((find = (res + res).find(res, 1)) < res.size())
            res = to_string(res.size() / find) + "[" + solve(s, dp, i, i + find - 1) + "]";
        // iterate all possibilities.
        else {
            for (int k = i; k < j; k++) {
                const string & left = solve(s, dp, i, k);
                const string & right = solve(s, dp, k + 1, j);
                if (left.size() + right.size() < res.size())
                    res = left + right;
            }
        }
        return res;
    }
    string encode(string s) {
        vector<vector<string>> dp(s.size(), vector<string>(s.size(), ""));
        return solve(s, dp, 0, s.size() - 1);

    }
};
```

2. ##### dynamic programming with iteration

- bottom up iterative method.
- fill the table column by column from left to right and bottom to top.

```cpp
class Solution {
public:
    string encode(string s) {
        int len = s.size();
        if (len <= 4) return s;
        vector<vector<string>> dp(len, vector<string>(len, ""));

        for (int j = 0; j < len; j++)
            for (int i = j; i >= 0; i--) {
                string & res = dp[i][j];
                res = s.substr(i, j - i + 1);
                if (j - i + 1 < 5)
                    continue;
                int find = res.size();
                if ((find = (res + res).find(res, 1)) < res.size())
                    res = to_string(res.size() / find) + "[" + dp[i][i + find - 1] + "]";
                else {
                    for (int k = i; k < j; k++) {
                        string & left = dp[i][k];
                        string & right = dp[k + 1][j];
                        if (left.size() + right.size() < res.size())
                            res = left + right;
                }
            }

        return dp[0][s.size() - 1];
    }

};
```