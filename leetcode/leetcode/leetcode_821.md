---
title: Shortest Distance to a Character
date: 2021-01-04
---
Given a string S and a character C, return an array of integers representing the shortest distance from the character C in the string.

Example 1:

Input: S = "loveleetcode", C = 'e'
Output: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
 

Note:

S string length is in [1, 10000].
C is a single character, and guaranteed to be in string S.
All letters in S and C are lowercase.

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    vector<int> shortestToChar(string S, char C) {
        vector<int> res(S.size(), 0x3f3f3f3f);
        int previ = -0x3f3f3f3f;
        for (int i = 0; i < S.size(); i++) {
            if (S[i] == C) previ = i;
            res[i] = i - previ;
        }
        previ = 2 * 0x3f3f3f3f;
        for (int i = S.size() - 1; i >= 0; i--) {
            if (S[i] == C) previ = i;
            res[i] = min(res[i], previ - i);
        }

        return res;
    }
};
```