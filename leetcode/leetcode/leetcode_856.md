---
title: Score of Parentheses
date: 2021-01-04
---
Given a balanced parentheses string S, compute the score of the string based on the following rule:

() has score 1
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.
 

Example 1:

Input: "()"
Output: 1
Example 2:

Input: "(())"
Output: 2
Example 3:

Input: "()()"
Output: 2
Example 4:

Input: "(()(()))"
Output: 6
 

Note:

S is a balanced parentheses string, containing only ( and ).
2 <= S.length <= 50

#### Solutions

1. ##### dfs with recursion O(n) S(n)

```cpp
class Solution {
public:
    int score(const string & s, int & st) {
        int sc = 0;
        while (st < s.size() && s[st] != ')') {
            int prev = st++;
            int innersc = score(s, st);
            sc += st - prev == 2 ? innersc : 2 * innersc;
        }
        st++;
        return sc == 0 ? 1 : sc;
    }
    int scoreOfParentheses(string S) {
        int st = 0;
        return score(S, st);
    }
};
```

2. ##### stack

- From the official answer

```cpp
class Solution {
public:
    int scoreOfParentheses(string S) {
        stack<int> s; s.push(0);
        for (auto c : S) {
            if (c == '(')
                s.push(0);
            else {
                int child = s.top(); s.pop();
                int prev = s.top(); s.pop();
                s.push(prev + max(2 * child, 1));
            }
        }

        return s.top();
    }
};
```

3. ##### iteration

- From the official answer.
- Count the score at the first time when meets a "()"

```cpp
class Solution {
public:
    int scoreOfParentheses(string S) {
        int level = 0, res = 0;
        for (int i = 0; i < S.size(); i++) {
            if (S[i] == '(')
                level++;
            else {
                level--;
                // only count one for each hierarchical parenthese
                if (S[i - 1] == '(')
                    res += 1 << level;
            }
        }
        return res;
    }
};
```