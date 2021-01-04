---
title: One Edit Distance
date: 2021-01-04
---
#### Given two strings s and t, determine if they are both one edit distance apart.

#### Note: 

There are 3 possiblities to satisify one edit distance apart:

-    Insert a character into s to get t
-    Delete a character from s to get t
-    Replace a character of s to get t

```
Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.

Example 2:

Input: s = "cab", t = "ad"
Output: false
Explanation: We cannot get t from s by only one step.

Example 3:

Input: s = "1203", t = "1213"
Output: true
Explanation: We can replace '0' with '1' to get t.
```

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int lens = s.size(), lent = t.size();
        if (abs(lens - lent) > 1) return false;
        if (lens > lent) {
            swap(s, t);
            swap(lens, lent);
        }
        int i = 0;
        while (i < lens && s[i] == t[i])
            i++;
        // two idetical strings are not one edit apart
        if (lens == lent && i == lens)
            return false;
        int j = lens < lent ? i + 1 : ++i;
        while (j < lent)
            if (s[i++] != t[j++])
                return false;
        return true;
    }
};
```