---
title: Valid Parenthesis String
date: 2021-01-04
---
Given a string containing only three types of characters: '(', ')' and '*', write a function to check whether this string is valid. We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.
Example 1:
Input: "()"
Output: True
Example 2:
Input: "(*)"
Output: True
Example 3:
Input: "(*))"
Output: True
Note:
The string size will be in the range [1, 100].


#### Solutions

1. ##### dfs O(3^n)

- Almost get TLE.

```cpp
class Solution {
public:
    bool dfs(string & s, int cur, int l) {
        if (l < 0) return false;
        if (cur == s.size())
            return l == 0;
        if (s[cur] != '*') {
            l += (s[cur] == '(') ? 1 : -1;
            return dfs(s, cur + 1, l);
        }
        else
            return dfs(s, cur + 1, l)
                || dfs(s, cur + 1, l + 1)
                || dfs(s, cur + 1, l - 1);
    }
    bool checkValidString(string s) {
        return dfs(s, 0, 0);
    }
};
```


2. ##### greedy approach O(n)

- Borrowed from the official answer
- Maintaining the range(defined by lo and hi) of possible number of balanced left brackets while scanning the string.
    - Note that the lower_bound `lo` can not be smaller than zero as negative is meaningless.

```cpp
class Solution {
public:
    bool checkValidString(string s) {
        int lo = 0, hi = 0;
        for (auto c : s) {
            if (c == '(') {
                lo++; hi++;
            }
            else if (c == ')') {
                hi--; lo = max(0, lo - 1);
            }
            else {
                hi++; lo = max(0, lo - 1);
            }
            if (hi < 0) return false;
        }
        return lo <= 0 && hi >= 0;
    }
};
```

3. ##### two scanning

- reference: https://leetcode-cn.com/problems/valid-parenthesis-string/solution/fen-zhi-tan-xin-shuang-xiang-bian-li-shuang-zhan-j/
- Considering all '*' as '(' and ')' respectively and directly return false if the other bracket exceeds the maximum size.
- How to prove the correctness？

```cpp
class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();

        int l = 0;
        for (auto c : s) {
            if (c != ')')
                l++;
            else if (--l < 0)
                return false;
        }

        int r = 0;
        for (int i = n - 1; i >= 0; i--) {
            auto c = s[i];
            if (c != '(')
                r++;
            else if (--r < 0)
                return false;
        }

        return true;
    }
};
```