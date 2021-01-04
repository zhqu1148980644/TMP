---
title: Count Substrings That Differ by One Character
date: 2021-01-04
---
Given two strings s and t, find the number of ways you can choose a non-empty substring of s and replace a single character by a different character such that the resulting substring is a substring of t. In other words, find the number of substrings in s that differ from some substring in t by exactly one character.

For example, the underlined substrings in "computer" and "computation" only differ by the 'e'/'a', so this is a valid way.

Return the number of substrings that satisfy the condition above.

A substring is a contiguous sequence of characters within a string.

 

Example 1:

Input: s = "aba", t = "baba"
Output: 6
Explanation: The following are the pairs of substrings from s and t that differ by exactly 1 character:
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
("aba", "baba")
The underlined portions are the substrings that are chosen from s and t.
​​Example 2:
Input: s = "ab", t = "bb"
Output: 3
Explanation: The following are the pairs of substrings from s and t that differ by 1 character:
("ab", "bb")
("ab", "bb")
("ab", "bb")
​​​​The underlined portions are the substrings that are chosen from s and t.
Example 3:
Input: s = "a", t = "a"
Output: 0
Example 4:

Input: s = "abe", t = "bbc"
Output: 10
 

Constraints:

1 <= s.length, t.length <= 100
s and t consist of lowercase English letters only.


#### Solutions

1. ##### straight forward O(n4)

- Check all possible combinations of two substrings with the same length in two words.

```cpp
class Solution {
public:
    inline bool ok(const string & s1, const string & s2) {
        int diff = 0;
        for (int i = 0; i < s1.size(); i++) {
            if ((diff += (s1[i] != s2[i])) > 1)
                return false;
        }
        return diff == 1;
    }
    int countSubstrings(string s, string t) {
        int res = 0;
        // for each length
        for (int l = 1; l <= s.size(); l++) {
            // for each start position in s
            for (int i = 0; i <= s.size() - l; i++) {
                if (t.size() < l) continue;
                string s1 = s.substr(i, l);
                // for each start position in t
                for (int j = 0; j <= t.size() - l; j++) {
                    string s2 = t.substr(j, l);
                    res += ok(s1, s2);
                }
            }
        }
        
        return res;
    }
};
```

- optimized version O(n3)

```cpp
class Solution {
public:
    int countSubstrings(string s, string t) {
        int n1 = s.size(), n2 = t.size(), res = 0;
        // for each start position in s
        for (int i = 0; i < n1; i++)
            // for each end position in t
            for (int j = 0; j < n2; j++) {
                int diff = 0;
                // for different length of substring
                for (int k = 0; i + k < n1 && j + k < n2; k++) {
                    if ((diff += s[i + k] != t[j + k]) > 1)
                        break;
                    else
                        res += diff == 1;
                }
            }
        
        return res;
    }
};
```

2. ##### O(n2) solution

- reference: https://leetcode-cn.com/problems/count-substrings-that-differ-by-one-character/solution/tong-ji-zhi-chai-yi-ge-zi-fu-de-zi-chuan-shu-mu-by/
