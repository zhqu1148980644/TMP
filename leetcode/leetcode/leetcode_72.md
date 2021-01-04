---
title: Edit Distance
date: 2021-01-04
---
#### Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.

You have the following 3 operations permitted on a word:

-    Insert a character
-    Delete a character
-    Replace a character

```
Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
```


#### Solutions

- Break the problem down into multiple subproblem. ie: The minimum editing distance of two strings can be calculated using the minimum editing distance between two prefixs.

1. ##### dynamic programming

- A bottom-up approach.
- Recursive formula: `min[i, j]` represent the minimum editing distance between `s1[:i]` and `s2[:j]`: then
    - if `s1[i] == s2[j]`, the minimum edit distance equals to `min[i - 1, j - 1]`
    - else there are three possibilities: 
        - from `min[i - 1, j]`, insert a character `s2[j]` at the back of `s1[:i - 1]`. ie. one insertion in `s1`.
        - from `min[i, j - 1]`, the same. ie. one insertion in `s2`.
        - from `min[i - 1, j - 1]`, just replace one of `s1[i]` and `s2[j]` to make them match. ie. one replacement in either `s1` or `s2`.
        - Thus we choose the `minimum` editing distance among these three situations, and `plus one`.

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<int> dp(word2.size() + 1, 0);
        for (int j = 1; j <= word2.size(); j++)
            dp[j] = dp[j - 1] + 1;
        
        int prel;
        for (int i = 0; i < word1.size(); i++) {
            prel = dp[0]++;
            for (int j = 0; j < word2.size(); j++) {
                int up = dp[j + 1];
                if (word1[i] == word2[j])
                    dp[j + 1] = prel;
                else
                    dp[j + 1] = min(prel, min(dp[j], up)) + 1;
                prel = up;
            }
        }

        return dp[word2.size()];
    }
};
```

2. ##### recursion with memoization

- A top down method, solving the problem from the results of subproblem by recursion.

```python
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        from functools import lru_cache
        @lru_cache(None)
        def mineds(end1, end2):
            if end1 < 0 and end2 < 0:
                return 0
            elif end1 < 0 or end2 < 0:
                return end1 + 1 if end2 < 0 else end2 + 1
            if word1[end1] == word2[end2]:
                return mineds(end1 - 1, end2 - 1)
            else:
                return 1 + min(
                    mineds(end1 - 1, end2),
                    mineds(end1, end2 - 1),
                    mineds(end1 - 1, end2 - 1)
                )

        return mineds(len(word1) - 1, len(word2) - 1)
```