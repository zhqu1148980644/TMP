---
title: Number of Segments in a String
date: 2021-01-04
---
#### Count the number of segments in a string, where a segment is defined to be a contiguous sequence of non-space characters.

Please note that the string does not contain any non-printable characters.

```
Example:

Input: "Hello, my name is John"
Output: 5
```

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    int countSegments(string s) {
        int count = 0;
        for (int i = 0; i < s.size(); i++)
            if (s[i] != ' ' && (i == s.size() - 1 || s[i + 1] == ' '))
                count++;
        return count;
    }
};
```
