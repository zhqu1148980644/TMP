---
title: Longest Substring with At Most Two Distinct Characters
date: 2021-01-04
---
Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.

Example 1:

Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.
Example 2:

Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.


#### Solutions

1. ##### sliding window O(n)

- Maintaining a valid window during the scanning.

```cpp
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        vector<int> count(128);
        int i = 0, j = 0, cnt = 0, res = 0;

        while (j < s.size()) {
            if (++count[s[j++]] == 1 && ++cnt > 2) {
                while (--count[s[i++]] != 0);
                cnt--;
            }
            res = max(res, j - i);
        }

        return res;
    }
};
```