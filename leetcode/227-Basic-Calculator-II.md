#### Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

```
Example 1:

Input: "3+2*2"
Output: 7

Example 2:

Input: " 3/2 "
Output: 1

Example 3:

Input: " 3+5 / 2 "
Output: 5
```

#### Note:

-    You may assume that the given expression is always valid.
-    Do not use the eval built-in library function.

#### Solutions

1. ##### one stack

- reference: https://leetcode-cn.com/problems/basic-calculator-ii/comments/32510
- Codes below are self-explanatory.

```c++
#define isnum(x) (x >= '0')
#define num(x) ((x - '0'))
class Solution {
public:
    int calculate(string s) {
        int cur = 0;
        char preopt = '+';
        stack<int> nums;
        s.push_back(' ');
        for (int i = 0; i < s.size(); i++) {
            if (isnum(s[i]))
                cur = cur * 10 + num(s[i]);
            else if (s[i] != ' ' || i == s.size() - 1) {
                if (preopt == '+')
                    nums.push(cur);
                else if (preopt == '-')
                    nums.push(-cur);
                else {
                    int prenum = nums.top(); nums.pop();
                    cur = preopt == '*' ? prenum * cur : prenum / cur;
                    nums.push(cur);
                }
                preopt = s[i];
                cur = 0;
            }
        }
        int res = 0;
        while (!nums.empty()) {
            res += nums.top();
            nums.pop();
        }

        return res;
    }
};
```

2. ##### no stack

```c++
#define isnum(x) (x >= '0')
class Solution {
public:
    int calculate(string s) {
        long cur = 0, prenum = 0, res = 0;
        char preopt = '+';
        for (int i = 0; i < s.size(); i++) {
            if (isnum(s[i]))
                cur = cur * 10 + (s[i] - '0');
            if ((!isnum(s[i]) && s[i] != ' ') || i == s.size() - 1) {
                if (preopt == '+') {
                    res += prenum;
                    prenum = cur;
                }
                else if (preopt == '-') {
                    res += prenum;
                    prenum = -cur;
                }
                else if (preopt == '*')
                    prenum *= cur;
                else if (preopt == '/')
                    prenum /= cur;

                preopt = s[i];
                cur = 0;
            }
        }

        return res + prenum;
    }
};
```