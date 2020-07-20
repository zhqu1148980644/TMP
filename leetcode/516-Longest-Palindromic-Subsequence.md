#### Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

```
Example 1:
Input:

"bbbab"

Output:

4

One possible longest palindromic subsequence is "bbbb".

Example 2:
Input:

"cbbd"

Output:

2

One possible longest palindromic subsequence is "bb". 
```

#### Solutions

- Notes: Subsequence is not equal to substring.

1. ##### dynamic programming

- `dp[i][j]` represents the length of the longest palindromic subsequence within `s[i:j]`, then:
    - if `s[i] == s[j]`, `dp[i][j] = dp[i][j] + 2`
    - else `dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])`
- Codes below fill the table column by column from the left to the right, you may also choose to fill the table from the bottom row by row as long as all states required for updating a  position is available when needed.

```c++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int len = s.size();
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int j = 0; j < len; j++) {
            for (int i = j; i >= 0; i--) {
                if (i == j)
                    dp[i][j] = 1;
                else {
                    if (s[i] == s[j])
                        // dp[i + 1][j - 1] is zero(bypass the diagonal) when j < i, would not cause error
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    else
                        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][len - 1];
    }
};
```


- Or just use a 1d table.
- This time we fill the table row by row.

```c++
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int len = s.size();
        vector<int> dp(s.size());

        for (int i = len - 1; i >= 0; i--) {
            dp[i] = 1;
            // prel represents dp[i + 1][j - 1
            int prel = 0;
            for (int j = i + 1; j < len; j++) {
                // down reprewents d[i + 1][j]
                int down = dp[j];
                if  (s[i] == s[j])
                    dp[j] = prel + 2;
                else
                    dp[j] = max(dp[j - 1], down);
                prel = down;
            }
        }
        return dp[len - 1];
    }
};
```