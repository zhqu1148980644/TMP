---
title: Shortest Common Supersequence
date: 2021-01-04
---
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences.  If multiple answers exist, you may return any of them.

(A string S is a subsequence of string T if deleting some number of characters from T (possibly 0, and the characters are chosen anywhere from T) results in the string S.)

 

```
Example 1:

Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation: 
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.
```

 

#### Note:

-    1 <= str1.length, str2.length <= 1000
-    str1 and str2 consist of lowercase English letters.


#### Solutions

1. ##### longest common subsequence O(m + n) S(n * min(m, n))

- Find the longest common subsequence.
- Insert characters outside the lcs into lcs with the same order as that in original string.

```cpp
class Solution {
public:
    string lcs(string & s1, string & s2) {
        int m = s1.size(), n = s2.size();
        vector<string> dp(n + 1);

        for (int i = 1; i < m + 1; i++) {
            string diag = "";
            for (int j = 1; j < n + 1; j++) {
                string tmp = dp[j];
                if (s1[i - 1] == s2[j - 1])
                    dp[j] = diag + s1[i - 1];
                else if (dp[j - 1].size() > dp[j].size())
                    dp[j] = dp[j - 1];
                diag = tmp;
            }
        }
        return dp[n];
    }
    string shortestCommonSupersequence(string str1, string & str2) {
        if (str1.size() < str2.size())
            swap(str1, str2);
        
        int m = str1.size(), n = str2.size();
        int i = 0, j = 0;
        string res;

        for (auto c : lcs(str1, str2)) {
            while (i < m && str1[i] != c)
                res.push_back(str1[i++]);
            while (j < n && str2[j] != c)
                res.push_back(str2[j++]);
            res.push_back(c); i++; j++;
        }

        return res + str1.substr(i) + str2.substr(j);
    }
};
```


- In order to save the space for storing lcss in dp table, we can also choose to record lengths of lcss in dp table and finally recover the lcs by backtracking.


