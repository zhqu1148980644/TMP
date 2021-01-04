---
title: Longest Uncommon Subsequence II
date: 2021-01-04
---
Given a list of strings, you need to find the longest uncommon subsequence among them. The longest uncommon subsequence is defined as the longest subsequence of one of these strings and this subsequence should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting some characters without changing the order of the remaining elements. Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.

The input will be a list of strings, and the output needs to be the length of the longest uncommon subsequence. If the longest uncommon subsequence doesn't exist, return -1.

Example 1:
Input: "aba", "cdc", "eae"
Output: 3
Note:

All the given strings' lengths will not exceed 10.
The length of the given list will be in the range of [2, 50].

#### Solutions

1. ##### loop through all pairs

- Key points, the longest uncommon subsequence must be one of the given strings.
    - Suppose `subs1` is the longest common subsequence, then `s1` must be a subsequence of other strings. If a string is a subsequence of other strings, then it's subsequence must also be a subsequence, which leads to the inconsistency with the supposition.
- Use sort to start scanning from the largest to the smallest string and preexit if we find a uncommon

```cpp
class Solution {
public:
    bool isubseq(string & s1, string & s2) {
        if (s1.size() > s2.size()) return false;
        int i = 0;
        for (int j = 0; j < s2.size(); j++) {
            if (s1[i] == s2[j])
                i++;
        }
        return i == s1.size();
    }
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](auto & s1, auto & s2) {
            return s1.size() > s2.size();
        });
        
        for (int i = 0; i < strs.size(); i++) {
            bool uncommon = true;
            for (int j = 0; j < strs.size(); j++) {
                if (i == j) continue;
                if (strs[j].size() < strs[i].size())
                    break;
                if (isubseq(strs[i], strs[j])) {
                    uncommon = false;
                    break;
                }
            }
            if (uncommon) return strs[i].size();
        }
        return -1;
    }
};
```