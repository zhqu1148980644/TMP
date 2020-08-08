Given a string S, count the number of distinct, non-empty subsequences of S .

Since the result may be large, return the answer modulo 10^9 + 7.

 

Example 1:

Input: "abc"
Output: 7
Explanation: The 7 distinct subsequences are "a", "b", "c", "ab", "ac", "bc", and "abc".
Example 2:

Input: "aba"
Output: 6
Explanation: The 6 distinct subsequences are "a", "b", "ab", "ba", "aa" and "aba".
Example 3:

Input: "aaa"
Output: 3
Explanation: The 3 distinct subsequences are "a", "aa" and "aaa".
 

 

Note:

S contains only lowercase letters.
1 <= S.length <= 2000

#### Solutions

1. ##### dynamic programming

- from the official answer
- `dp[i]` represents the number of uniq subsequences in `S[:i)`
- There are two cases when adding a new character at the end.
    - The current character is a new character. Then `dp[i] = dp[i - 1] * 2` denotes for all uniq subsequences in `S[:i - 1)`, adding the current character at the back could build a new uniq subsequence.
    - The current character has been added before(duplicate), `dp[i] = dp[i - 1] * 2 - dp[last[S[i]]]`, `dp[last[S[i]]]` represents the previous `dp` when adding the same character at the last time.

```c++
class Solution {
public:
    int distinctSubseqII(string S) {
        const long MOD = 1e9 + 7;
        vector<long> dp(S.size() + 1), last(26, -1);
        dp[0] = 1;

        for (int i = 0; i < S.size(); i++) {
            auto c = S[i] - 'a';
            long back = dp[i];
            dp[i + 1] = (dp[i] * 2) % MOD;
            if (last[c] != -1)
                dp[i + 1] = (dp[i + 1] - dp[last[c]]) % MOD;
            last[c] = i;
        }

        return (dp[S.size()] + MOD) % MOD - 1;
    }
};
```