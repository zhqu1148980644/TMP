Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

```
Example 1:

Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:

Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
```

#### Note:
- 0 < s1.length, s2.length <= 1000.
- All elements of each string will have an ASCII value in [97, 122].


#### Solutions

1. ##### lcs based dynamic programming O(mn)

- This program equals to find the common subsequence with the largest sum.

```c++
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        if (s2.size() < s1.size())
            return minimumDeleteSum(s2, s1);
        int n1 = s1.size(), n2 = s2.size();
        vector<int> dp(n2 + 1);
        for (int i = 1; i <= n1; i++) {
            int diag = 0;
            for (int j = 1; j <= n2; j++) {
                int tmp = dp[j];
                if (s1[i - 1] == s2[j - 1])
                    dp[j] = diag + s1[i - 1];
                else
                    dp[j] = max(dp[j - 1], dp[j]);
                diag = tmp;
            }
        }

        int sum = accumulate(s1.begin(), s1.end(), 0)
                + accumulate(s2.begin(), s2.end(), 0);

        return sum - 2 * dp[n2];
    }
};
```


2. ##### dynamic programming O(mn)

-  `dp[i][j]` represents the the minimum sum of deleted characters to make `s1[:i]` and `s2[:j]` equal.

```c++
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        if (s2.size() < s1.size())
            return minimumDeleteSum(s2, s1);
        int n1 = s1.size(), n2 = s2.size();
        vector<int> dp(n2 + 1);
        for (int i = 0; i < n2; i++)
            dp[i + 1] += dp[i] + s2[i];
        
        for (int i = 1; i <= n1; i++) {
            int diag = dp[0];
            dp[0] += s1[i - 1];
            for (int j = 1; j <= n2; j++) {
                int tmp = dp[j];
                // no need to delete
                if (s1[i - 1] == s2[j - 1])
                    dp[j] = diag;
                else
                    dp[j] = min(dp[j - 1] + s2[j - 1], dp[j] + s1[i - 1]);
                diag = tmp;
            }
        }
        
        return dp[n2];
    }
};
```