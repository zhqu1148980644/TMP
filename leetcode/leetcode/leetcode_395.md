---
title: Longest Substring with At Least K Repeating Characters
date: 2021-01-04
---
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.

#### Solutions

1. ##### divide and conquer with recursion


```cpp
class Solution {
public:
    int longestSubstring(string s, int k) {
        if (k <= 1) return s.size();
        if (s.size() < k) return 0;
        vector<int> m(128);
        for (auto c : s) m[c]++;
        // insert a border
        s.push_back(0);int res = 0;
        for (int i = 0, j = 0; j < s.size(); j++)
            if (m[s[j]] < k) {
                if (j - i == s.size() - 1)
                    return j - i;
                if (j - i > 0)
                    res = max(res, longestSubstring(s.substr(i, j - i), k));
                i = j + 1;
            }

        return res;
    }
};
```