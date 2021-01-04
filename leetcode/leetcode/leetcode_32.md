---
title: Longest Valid Parentheses
date: 2021-01-04
---
### Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

```
Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"
```


### Solutions

1. #### Brute force O(n3) S(n)

Check all possible substrings.


2. #### Dynamic programming O(n)

Build a dp table to record each position's longest valid parentheses ending in this position.

- When `s[i] == "("`, then `dp[i] = 0`
- When `s[i] == ")"` and `s[i - 1] == "("`, then `dp[i] = dp[i - 2] + 2`
- When `s[i] == ")"` and `s[i - 1] == ")"`
    - if `dp[i - dp[i - 1] - 1] == "("`, then `dp[i] = dp[i - 2] + dp[i - dp[i - 1] - 2] + 2`
    - else `dp[i] = 0`;

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.size(); if (!len) return 0;
        int * dp = new int[len], max_len;
        dp[0] = max_len = 0;
        for (int i = 1; i < len; i++) {
            dp[i] = 0;
            if (s[i] == '(') continue;
            else if (s[i - 1] == '(')
                dp[i] = 2 + ((i - 2 >= 0) ? dp[i - 2] : 0); 
            else if ((i - dp[i - 1] - 1 >= 0) && (s[i - dp[i -1] - 1] == '(')) {
                dp[i] = 2 + dp[i - 1];
                if (i - dp[i - 1] - 2 >= 0)
                    dp[i] += dp[i - dp[i - 1] - 2];
            }
            max_len = max(max_len, dp[i]);
        }
        return max_len;
    }
};
```

Or unify the last two cases since `dp[i - 1] == 0` when `s[i - 1] == '('`.

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.size(); if (!len) return 0;
        int * dp = new int[len], max_len;
        dp[0] = max_len = 0;
        for (int i = 1; i < len; i++) {
            dp[i] = 0;
            if (s[i] == '(') continue;
            else if ((i - dp[i - 1] - 1 >= 0) && (s[i - dp[i -1] - 1] == '(')) {
                dp[i] = 2 + dp[i - 1];
                if (i - dp[i - 1] - 2 >= 0)
                    dp[i] += dp[i - dp[i - 1] - 2];
            }
            max_len = max(max_len, dp[i]);
        }
        return max_len;
    }
};
```

3. #### Two pass


- Record the current number of left and right brackets.
- when the number of left bracket equals to the number of right bracket. It must be a valid substring.
- A valid string must start from a left bracket. This is the reason why we set left and right to zero when there are more right brackets than left brackets.
- Can not use a single value to record the difference between number of two kinds of brackets.
eg: 1 2 3 2 1 0 1 2 1 0 -1 So the largest valid string is from 1 to 0:  10 but not 6.
- Why need to scan twice: https://leetcode-cn.com/problems/longest-valid-parentheses/solution/zui-chang-you-xiao-gua-hao-by-leetcode/218953


```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.size(); if (!len) return 0;
        int max_len = 0;
        int i = -1, left = 0, right = 0;
        while (++i < len) {
            if (s[i] == '(') left++;
            else right++;
            if (left == right)
                max_len = max(max_len, 2 * right);
            else if (right > left)
                left = right = 0;
        }

        left = right = 0;
        while (--i) {
            if (s[i] == ')') left++;
            else right++;
            if (left == right)
                max_len = max(max_len, 2 * right);
            else if (right > left)
                left = right = 0;
        }
        return max_len;
    }
};
```

4. #### Stack with one pass

- The top of the stack represents the former index of the valid substring.

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int max_len = 0;
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ')') {
                st.pop();
                if (st.empty()) st.push(i);
                else max_len = max(i - st.top(), max_len);
            } else {
                st.push(i);
            }
        }
        return max_len;
    }
};
```
