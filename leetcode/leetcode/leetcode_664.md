---
title: Strange Printer
date: 2021-01-04
---
There is a strange printer with the following two special requirements:

-    The printer can only print a sequence of the same character each time.
-    At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.

Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

```
Example 1:

Input: "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".

Example 2:

Input: "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
```

Hint: Length of the given string will not exceed 100.


#### Solutions

- The main intuition is to firstly print border characters in order to print as much as possible in less operations, then print characters in the middle.

1. ##### dynamic programming with memoization

- reference: official answer.
- `dp[i][j]` represents the the minimum number of turns the printer needed to print `s[i:j]`

```cpp
class Solution {
public:
    vector<vector<int>> memo;
    int solve(string & s, int i, int j) {
        if (j < i) return 0;
        if (memo[i][j])
            return memo[i][j];
        // firstly print the first character, then print the remaining characters.
        int time = 1 + solve(s, i + 1, j);
        // Or choose a character same as the first character, the first character will be printed when printing the left substring as these two characters are border characters.
        /// a[*****a][****], the first a can be printed when printing the left half.
        for (int k = i + 1; k <= j; k++)
            if (s[i] == s[k])
                time = min(time, solve(s, i + 1, k) + solve(s, k + 1, j));
        return memo[i][j] = time;
    }

    int strangePrinter(string s) {
        int n = s.size();
        memo = vector<vector<int>>(n, vector<int>(n, 0));
        return solve(s, 0, n - 1);
    }
};
```

2. ##### dynamic programming with iteration

- A minor optimization: remove consecutive repeating characters since we will always print these duplicated characters in one turn.


```cpp
class Solution {
public:
    int strangePrinter(string s) {
        if (!s.size()) return 0;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, n));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
        // as we are extending i from j - 1 to 1, the current border characters is j
        // else if we are extending from 0 to j - 1, the current border characters is i
        for (int j = 0; j < n; j++)
            for (int i = j - 1; i >= 0; i--) {
                dp[i][j] = 1 + dp[i][j - 1];
                for (int k = j - 1; k >= i; k--)
                    // [****][a*****]a, the current a can be printed simultaneously in the second half.
                    if (s[k] == s[j])
                        // or (k > 0 ? dp[i][k - 1] : 0)
                        dp[i][j] = min(dp[i][j], (k > i ? dp[i][k - 1] : 0) + dp[k][j - 1]);
            }
        return dp[0][n - 1];
    }
};
```


- Another version.
- In this version, the border characters are included in the subproblem.
- For example, if the end character of s1 equals to the end character(border character) of of s2, these two characters can be printed in one turn, thus the answer is `turn(s1) + turn(s2) - 1`

```
              |-------------s2
    *********b---------------b
    |-------s1
```


```cpp
class Solution {
public:
    int strangePrinter(string s) {
        if (!s.size()) return 0;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, n));
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
        
        for (int j = 0; j < n; j++)
            // if we are extending i from 0 to j - 1, we need to check s[i] and s[k] 
            for (int i = j - 1; i >= 0; i--)
                for (int k = i; k < j; k++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] - (s[k] == s[j] ? 1 : 0));
        
        return dp[0][n - 1];
    }
};
```