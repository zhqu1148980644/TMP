---
title: Remove Duplicate Letters
date: 2021-01-04
---
Given a string which contains only lowercase letters, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: "bcabc"
Output: "abc"
Example 2:

Input: "cbacdcbc"
Output: "acdb"
Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/

#### Soltuions

1. ##### stack

```cpp
class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_set<char> seen;
        vector<int> m(126);
        for (int i = 0; i < s.size(); i++)
            m[s[i]] = i;

        string st;
        for (int i = 0; i < s.size(); i++) {
            auto c = s[i];
            // caution,
            if (seen.count(c)) continue;
            while (!st.empty() && c < st.back() && i < m[st.back()]) {
                seen.erase(st.back()); st.pop_back();
            }
            st.push_back(c); seen.insert(c);
        }

        return st;
    }
};
```