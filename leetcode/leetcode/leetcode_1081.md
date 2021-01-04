---
title: Smallest Subsequence of Distinct Characters
date: 2021-01-04
---
Return the lexicographically smallest subsequence of text that contains all the distinct characters of text exactly once.

Example 1:

Input: "cdadabcc"
Output: "adbc"
Example 2:

Input: "abcd"
Output: "abcd"
Example 3:

Input: "ecbacba"
Output: "eacb"
Example 4:

Input: "leetcode"
Output: "letcod"
 

Constraints:

1 <= text.length <= 1000
text consists of lowercase English letters.
Note: This question is the same as 316: https://leetcode.com/problems/remove-duplicate-letters/

#### Solutions

1. ##### mono stack

```cpp
class Solution {
public:
    string smallestSubsequence(string text) {
        vector<int> m(126);
        for (int i = 0; i < text.size(); i++)
            m[text[i]] = i;
        
        string st;
        unordered_set<char> seen;
        for (int i = 0; i < text.size(); i++) {
            auto c = text[i];
            if (seen.count(c)) continue;
            while (st.size() && c < st.back() && i < m[st.back()]) {
                seen.erase(st.back());  st.pop_back();
            }
            st.push_back(c); seen.insert(c);
        }

        return st;
    }
};
```