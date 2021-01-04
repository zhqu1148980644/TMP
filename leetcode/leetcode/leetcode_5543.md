---
title: Largest Substring Between Two Equal Characters
date: 2021-01-04
---
Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.

A substring is a contiguous sequence of characters within a string.

 

Example 1:

Input: s = "aa"
Output: 0
Explanation: The optimal substring here is an empty substring between the two 'a's.
Example 2:

Input: s = "abca"
Output: 2
Explanation: The optimal substring here is "bc".
Example 3:

Input: s = "cbzxy"
Output: -1
Explanation: There are no characters that appear twice in s.
Example 4:

Input: s = "cabbac"
Output: 4
Explanation: The optimal substring here is "abba". Other non-optimal substrings include "bb" and "".
 

Constraints:

1 <= s.length <= 300
s contains only lowercase English letters.

#### Solutions

1. ##### hash map

```cpp
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        vector<int> pos(128, s.size());
        int res = -1;
        for (int i = 0; i < s.size(); i++) {
            res = max(res, i - pos[s[i]] - 1);
            if (pos[s[i]] == s.size())
                pos[s[i]] = i;
        };
        
        return res < s.size() ? res : -1;
    }
};
```