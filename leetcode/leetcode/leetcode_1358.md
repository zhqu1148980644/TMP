---
title:  Number of Substrings Containing All Three Characters
date: 2021-01-04
---
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

```
Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

Example 3:

Input: s = "abc"
Output: 1
```

 

#### Constraints:

-    3 <= s.length <= 5 x 10^4
-    s only consists of a, b or c characters.

#### Solutions


1. ##### sliding window


```cpp
class Solution {
public:
    int numberOfSubstrings(string s) {
        int c[128] = {0};
        int i = 0, j = 0, cnt = 0, res = 0;
        while (j < s.size()) {
            if (++c[s[j]] == 1)
                cnt++;
            while (cnt == 3) {
                // s[j:] are all valid right boundaries
                res += s.size() - j;
                if (--c[s[i++]] == 0) --cnt;
            }
            j++;
        }

        return res;
    }
};
```