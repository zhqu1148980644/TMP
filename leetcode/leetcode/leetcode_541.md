---
title: Reverse String II
date: 2021-01-04
---
#### Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting from the start of the string. If there are less than k characters left, reverse all of them. If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.

```
Example:

Input: s = "abcdefg", k = 2
Output: "bacdfeg"
```

#### Restrictions:

-    The string consists of lower English letters only.
-    Length of the given string and k will in the range [1, 10000]

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    string reverseStr(string s, int k) {
        if (k == 1 || !s.size()) return s;
        int maxend = s.size() - 1, st = 0, end, tmp;
        while (st < s.size()) {
            tmp = st;
            end = min(st + k - 1, maxend);
            while(st < end)
                swap(s[st++], s[end--]);
            st = tmp + 2 * k;
        }

        return s;
    }
};
```

```python
class Solution:
    def reverseStr(self, s: str, k: int) -> str:
        s = list(s)
        for i in range(0, len(s), 2 * k):
            s[i: i + k] = s[i: i + k][::-1]
        return "".join(s)
```