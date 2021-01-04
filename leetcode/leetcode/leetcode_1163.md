---
title: Last Substring in Lexicographical Order
date: 2021-01-04
---
Given a string s, return the last substring of s in lexicographical order.

 

Example 1:

Input: "abab"
Output: "bab"
Explanation: The substrings are ["a", "ab", "aba", "abab", "b", "ba", "bab"]. The lexicographically maximum substring is "bab".
Example 2:

Input: "leetcode"
Output: "tcode"
 

Note:

1 <= s.length <= 4 * 10^5
s contains only lowercase English letters.

#### Solutions

- The problem equals to find the maximum suffix.

1. ##### straight forward O(n2)

- Check all suffix and find the maximum one.
- TLE.


2. ##### two pointers O(n)

- reference: https://leetcode-cn.com/problems/last-substring-in-lexicographical-order/solution/python-shuang-zhi-zhen-362ms-by-mian-mian-sir/
- check reference for details.

```cpp
class Solution {
public:
    string lastSubstring(string s) {
        if (s.size() <= 1) return s;

        int l = 0, r = 1, k = 0;
        while (r + k < s.size()) {
            if (s[l + k] > s[r + k]) {
                r += k + 1; k = 0;
            }
            else if (s[r + k] > s[l + k]) {
                l = r++; k = 0;
            }
            else
                k++;
        }

        return s.substr(l);
    }
};
```