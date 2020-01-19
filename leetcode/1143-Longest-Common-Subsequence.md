#### Given two strings text1 and text2, return the length of their longest common subsequence.

A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted without changing the relative order of the remaining characters. (eg, "ace" is a subsequence of "abcde" while "aec" is not). A common subsequence of two strings is a subsequence that is common to both strings.

 

If there is no common subsequence, return 0.

 

```
Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
```

 

#### Constraints:

-    1 <= text1.length <= 1000
-    1 <= text2.length <= 1000
-    The input strings consist of lowercase English characters only.

#### Solutions

1. ##### dynamic programming

- Bottom up method.
- `dp[i][j]` represent the lenght of the longest common subsequence between `s1[:i]` and `s2[:j]`
    - When `s1[i] == s[j]`, `dp[i][j]` equals to `dp[i - 1][j - 1] + 1`. We can not use `d[i]` or `dp[j]` as these two characters has been used at those points.
    - Otherwise, `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`.


```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1 = text1.size();
        int len2 = text2.size();
        if (!len1 || !len2) return 0;
        vector<int> dp(len2, 0);

        for (int i = 0; i < len1; i++) {
            int leftup = dp[0];
            dp[0] |= text1[i] == text2[0];
            for (int j = 1; j < len2; j++) {
                int up = dp[j], left = dp[j - 1];
                if (text1[i] == text2[j])
                    dp[j] = leftup + 1;
                else
                    // leftup cannot be larger thant left or up, thus the comparison is redundant
                    // dp[j] = max(leftup, max(left, up));
                    dp[j] = max(left, up);
                leftup = up;
            }
        }
        return dp[len2 - 1];
    }
};
```