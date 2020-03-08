### Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

```
Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true
```

### Solutions

1. #### stack

This application is widely taught in textbooks related to data structure and algorithms.

```c++
class Solution {
public:
    bool isValid(string s) {
        int len;
        if ((len = s.length()) % 2) return false;
        stack<char> S;
        for (int i = 0; i < len; i++) {
            if (!S.empty()) {
                int a = abs(S.top() - s[i]);
                if (a && (a < 3)) {
                    S.pop(); continue;
                }
            }
            S.push(s[i]);
        }
        return S.empty();
    }
};
```