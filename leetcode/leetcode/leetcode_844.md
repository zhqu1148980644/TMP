---
title: Backspace String Compare
date: 2021-01-04
---
Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Follow up:

Can you solve it in O(N) time and O(1) space?

#### Slutions

1. ##### stack O(n) S(n)

```cpp
class Solution {
public:
    vector<char> remove(const string & S) {
        vector<char> s;
        for (auto c : S)
            if (c != '#')
                s.push_back(c);
            else if (s.size())
                s.pop_back();
        return s;
    }
    bool backspaceCompare(string S, string T) {
        return remove(S) == remove(T);
    }
};
```

2. ##### use inplace stack O(n) S(1)

```cpp
class Solution {
public:
    int type(string & s) {
        int st = 0;
        for (auto c : s) {
            if (c != '#')
                s[st++] = c;
            else if (st > 0)
                st--;
        }
        return st;
    }
    bool backspaceCompare(string S, string T) {
        int len1 = type(S), len2 = type(T);
        return len1 == len2 && equal(
            S.begin(), S.begin() + len1,
            T.begin(), T.begin() + len2
        );
    }
};
```

3. ##### backward two pointers O(n) S(1)

```cpp
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int n1 = 0, n2 = 0;
        int i = S.size() - 1, j = T.size() - 1;
        while (i >= 0 || j >= 0) {
            bool miss = false;
            if (i >= 0 && S[i] == '#') {
                i--; n1++; miss = true;
            }
            if (j >= 0 && T[j] == '#') {
                j--; n2++; miss = true;
            }
            if (!miss) {
                if (n1 || n2) {
                    // skip char
                    if (n1) { i--; n1--; }
                    if (n2) { j--; n2--; }
                }
                else if (i < 0 || j < 0 || S[i--] != T[j--])
                    return false;
            }
        }
        return true;
    }
};
```