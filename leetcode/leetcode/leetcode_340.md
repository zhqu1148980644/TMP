---
title: Longest Substring with At Most K Distinct Characters
date: 2021-01-04
---
Given a string, find the length of the longest substring T that contains at most k distinct characters.

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: T is "ece" which its length is 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: T is "aa" which its length is 2.


#### Solutions

- Generalized version of problem `159 Longest Substring with At Most Two Distinct Characters`.

1. ##### sliding window O(n)

```cpp
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int i = 0, j = 0, distinct = 0, res = 0;
        vector<int> count(128);

        while (j < s.size()) {
            if (++count[s[j++]] == 1 && ++distinct > k) {
                while (--count[s[i++]] != 0);
                distinct--;
            }

            res = max(res, j - i);
        }

        return res;
    }
};
```