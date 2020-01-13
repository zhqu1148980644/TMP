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

```c++
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (abs((int)s.size() - (int)t.size()) > 1)
            return false;
        if (s.size() > t.size())
            swap(s, t);

        bool unequal = false;
        int i = 0;
        while (i < s.size()) {
            if (s[i] != t[i]) {
                unequal = true;
                break;
            }
            i++;
        }
        if (!unequal) {
            return s.size() < t.size();
        } else {
            int j = s.size() < t.size() ? i + 1 : ++i;
            while (j < t.size())
                if (s[i++] != t[j++])
                    return false;
            return true;
        }
    }
};
```