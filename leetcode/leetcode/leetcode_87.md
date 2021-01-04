---
title: Scramble String
date: 2021-01-04
---
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false


#### Solutions

1. ##### backtrack

- reference: https://leetcode-cn.com/problems/scramble-string/comments/65098
- For each possible split point, two subnodes may(not) have been swapped, thus need to search for both cases.

```cpp
class Solution {
public:
    bool solve(string_view s1, string_view s2) {
        if (s1 == s2) return true;
        int n = s1.size();
        int count[26] = {0};
        for (auto c : s1) count[c - 'a']++;
        for (auto c : s2) count[c - 'a']--;
        for (int i = 0; i < 26; i++)
            if (count[i]) return false;
        
        for (int i = 1; i < n; i++) {
            string_view 
                l1 = s1.substr(0, i),
                l2 = s2.substr(0, i),
                r1 = s1.substr(i),
                r2 = s2.substr(i);
            // not swapped
            if (solve(l1, l2) && solve(r1, r2))
                return true;
            // swapped
            l2 = s2.substr(0, n - i);
            r2  = s2.substr(n - i);
            if (solve(l1, r2) && solve(r1, l2))
                return true;
        }

        return false;
    }
    bool isScramble(string s1, string s2) {
        return solve(s1, s2);
    }
};
```

2. ##### dynamic programming

- reference: https://leetcode-cn.com/problems/scramble-string/solution/miao-dong-de-qu-jian-xing-dpsi-lu-by-sha-yu-la-jia/