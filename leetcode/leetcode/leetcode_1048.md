---
title: Longest String Chain
date: 2021-01-04
---
Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.  For example, "abc" is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

Return the longest possible length of a word chain with words chosen from the given list of words.

 

Example 1:

Input: ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: one of the longest word chain is "a","ba","bda","bdca".
 

Note:

1 <= words.length <= 1000
1 <= words[i].length <= 16
words[i] only consists of English lowercase letters.

##### Solutions

1. ##### dynamic programming

- `dp[w]` represents the length of the longest chain ends with `w`.
    - `dp[w] = 1 + max(dp[wx])` wx are any words with length `w.size() - 1`

```cpp
class Solution {
public:
    bool ispre(string_view s1, string_view s2) {
        if (s1.size() + 1 != s2.size()) return false;
        int i = 0, j = 0;
        while (j < s2.size()) {
            if (s1[i] == s2[j]) i++;
            j++;
        }
        return i == s1.size();
    }
    int longestStrChain(vector<string>& words) {
        map<int, vector<string_view>> m;
        for (auto & w : words)
            m[w.size()].push_back(w);

        int res = 1, prevlen = INT_MIN;
        unordered_map<string_view, int> dp;
        for (auto & [len, vs] : m) {
            for (auto & w : vs) {
                dp[w] = 1;
                if (prevlen != len - 1)
                    continue;
                for (auto & prev : m[len - 1])
                    if (ispre(prev, w))
                        dp[w] = max(dp[w], dp[prev] + 1);
                res = max(res, dp[w]);
            }
            prevlen = len;
        }
        return res;
    }
};
```