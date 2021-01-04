---
title: Buddy Strings
date: 2021-01-04
---
Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B.

 

Example 1:

Input: A = "ab", B = "ba"
Output: true
Example 2:

Input: A = "ab", B = "ab"
Output: false
Example 3:

Input: A = "aa", B = "aa"
Output: true
Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:

Input: A = "", B = "aa"
Output: false
 

Constraints:

0 <= A.length <= 20000
0 <= B.length <= 20000
A and B consist only of lowercase letters.

#### Solutions

1. ##### straight forward

- Note that the problem requires the string A `must` operate 1 swap.

```cpp
class Solution {
public:
    bool buddyStrings(string A, string B) {
        if (A.size() != B.size()) return false;
        vector<int> c1(126), c2(126);
        int diff = 0;
        for (int i = 0; i < A.size(); i++) {
            if (A[i] != B[i] && ++diff > 2)
                return false;
            c1[A[i]]++;
            c2[B[i]]++;
        }

        bool hasdup = false;
        for (int i = 97; i < 126; i++) {
            if (c1[i] != c2[i])
                return false;
            if (c1[i] > 1)
                hasdup = true;
        }

        return diff == 2 || hasdup;
    }
};
```