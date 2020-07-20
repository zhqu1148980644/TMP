##### Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

```
Example:

Input: "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
```


##### Solutions

1. ##### dynamic programming O(n2) S(n2)

- `mincut[j]` represents the minimum number of cuts to cut the `string[:j]` into palindromes, then:
- `mincut[j] = mincut[i - 1] + 1 if s[i:j] is palindrome for i <= j`
- base cases:
    - when `i == 0`, the whole string is a palindrome, no need to cut any more.
    - the maximum cut is `j`. ie: every character is a single palindrome.
- Use method in `problem 5` to memoize whether a certain substring is a palindrome.

```c++
class Solution {
public:
    int minCut(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size()));
        int mincut[s.size()];

        for (int j = 0; j < s.size(); j++) {
            int minc = j;
            for (int i = 0; i <= j; i++) {
                if (s[j] == s[i] && (j - i < 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    minc = min(i >= 1 ? mincut[i - 1] + 1 : 0, minc);
                }
            }
            mincut[j] = minc;
        }
        return mincut[s.size() - 1];
    }
};
```

2. ##### optimized with one pass O(n2) S(n)

- Since only the palindrome subarray would help us to update the `mincut` dp table, we can uitilize a center expansion method we used in `problem 5` to avoid checking every possible substring which is time consuming.

```c++
class Solution {
public:
    int minCut(string s) {
        int len = s.size(), i, j;
        int mincut[len];

        // initialize with the maximum number of cuts
        iota(mincut.begin(), mincut.end(), 0);

        for (int k = 0; k < len; k++) {
            // ...baab...
            i = k; j = k + 1;
            for (;i > 0 && j < len && s[i] == s[j]; i--, j++)
                mincut[j] = min(mincut[i - 1] + 1, mincut[j]);
            if (i == 0 && s[0] == s[j]) mincut[j] = 0;

            // ...cbabc...
            i = j = k;
            for (;i > 0 && j < len && s[i] == s[j]; i--, j++)
                mincut[j] = min(mincut[i - 1] + 1, mincut[j]);
            if (i == 0 && s[0] == s[j]) mincut[j] = 0;
        }

        return mincut[len - 1];
    }
};
```


3. ##### shortest path in graph O(n2) S(n2)

- reference: https://leetcode.com/problems/palindrome-partitioning-ii/discuss/42257/Solved-by-shortest-path-algorithm-clear-and-straightforward-O(n2)