---
title: Minimum Add to Make Parentheses Vali
date: 2021-01-04
---
Given a string S of '(' and ')' parentheses, we add the minimum number of parentheses ( '(' or ')', and in any positions ) so that the resulting parentheses string is valid.

Formally, a parentheses string is valid if and only if:

It is the empty string, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
Given a parentheses string, return the minimum number of parentheses we must add to make the resulting string valid.

 

Example 1:

Input: "())"
Output: 1
Example 2:

Input: "((("
Output: 3
Example 3:

Input: "()"
Output: 0
Example 4:

Input: "()))(("
Output: 4
 

Note:

S.length <= 1000
S only consists of '(' and ')' characters.

#### Solutions

1. ##### greedy

```cpp
class Solution {
public:
    int minAddToMakeValid(string S) {
        int l = 0;
        for (int i = 0; i < S.size(); i++)
            if (S[i] == '(')
                l++;
            else if (S[i] == ')' && l)
                l--;

        int r = 0;
        for (int i = S.size() - 1; i >= 0; i--)
            if (S[i] == ')')
                r++;
            else if (S[i] == '(' && r)
                r--;


        return l + r;
    }
};
```

- one pass

```cpp
class Solution {
public:
    int minAddToMakeValid(string S) {
        int needl = 0, needr = 0;
        for (auto c : S) {
            if (c == '(')
                needr++;
            else {
                if (needr > 0)
                    needr--;
                else
                    needl++;
            }
        }

        return needl + needr;
    }
};
```

2. ##### stack

```cpp
class Solution {
public:
    int minAddToMakeValid(string S) {
        stack<char> s;
        for (auto c : S)
            if (c == ')' && s.size() && s.top() == '(')
                s.pop();
            else
                s.push(c);

        return s.size();
    }
};
```