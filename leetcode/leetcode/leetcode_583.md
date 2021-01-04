---
title: Delete Operation for Two Strings
date: 2021-01-04
---
Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, where in each step you can delete one character in either string.

```
Example 1:

Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
```

#### Note:

-    The length of given words won't exceed 500.
-    Characters in given words can only be lower-case letters.


#### Solutions

1. ##### dynamic programming

- `dp[i][j]` represents the minimum number of delete operators to make `s1[:i]` and `s2[:j]` the same.
    - if `s[i] == s[j]`, `dp[i][j] = dp[i - 1][j - 1]`
    - else `dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1`

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (word1.size() < word2.size())
            swap(word1, word2);
        int nrow = word1.size();
        int ncol = word2.size();
        vector<int> dp(ncol + 1);
        for (int i = 0; i < ncol + 1; i++)
            dp[i] = i;

        for (int i = 1; i < nrow + 1; i++) {
            int diag = dp[0]++; 
            for (int j = 1; j < ncol + 1; j++) {
                int tmp = dp[j];
                if (word1[i - 1] == word2[j - 1])
                    dp[j] = diag;
                else
                    // diag + 2 can not be smaller than other two situations
                    dp[j] = min(dp[j - 1], dp[j]) + 1;
                diag = tmp;
            }
        }
        return dp[ncol];
    }
};
```

2. ##### longest common subsequence

- The minimum number of delete operations equals to the total length of two strings minus 2 times the length of the longest common subsequence(lcs).
- `dp[i][j]` represents the length of the longest common subsequence of `s[:i]` and `s[:j]`
    - if `s[i] == s[j]`, then `dp[i][j] = dp[i - 1][j - 1] + 1`
    - else `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`
        - `dp[i - 1][j - 1]` can not be greater than the other two cases.

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        if (!word1.size() || !word2.size())
            return word1.size() || word2.size();
        if (word1.size() < word2.size())
            swap(word1, word2);
        vector<int> dp(word2.size());

        for (int i = 0; i < word1.size(); i++) {
            int diag = dp[0];
            dp[0] = dp[0] || word1[i] == word2[0];
            for (int j = 1; j < word2.size(); j++) {
                int tmp = dp[j];
                if (word1[i] == word2[j])
                    dp[j] = diag + 1;
                else
                    dp[j] = max(dp[j - 1], dp[j]);
                diag = tmp;
            }
        }
        // mindelete = len(s1) + len(s2) - 2 * len(lcs(s1, s2))
        return word1.size() + word2.size() - 2 * dp[word2.size() - 1];
    }
};
```