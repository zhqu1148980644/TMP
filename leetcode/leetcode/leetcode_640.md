---
title: Solve the Equation
date: 2021-01-04
---
Solve a given equation and return the value of x in the form of string "x=#value". The equation contains only '+', '-' operation, the variable x and its coefficient.

If there is no solution for the equation, return "No solution".

If there are infinite solutions for the equation, return "Infinite solutions".

If there is exactly one solution for the equation, we ensure that the value of x is an integer.

Example 1:
Input: "x+5-3+x=6+x-2"
Output: "x=2"
Example 2:
Input: "x=x"
Output: "Infinite solutions"
Example 3:
Input: "2x=x"
Output: "x=0"
Example 4:
Input: "2x+3x-6x=x+2"
Output: "x=-1"
Example 5:
Input: "x=x+2"
Output: "No solution"

#### Solutions

1. #####  straight forward

```cpp
class Solution {
public:
    pair<int, int> parse(string s) {
        int x = 0, n = 0, num = 0, sign = 1;
        s.push_back('+');
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '+' || s[j] == '-') {
                if (j - 1 >= 0 && s[j - 1] == 'x')
                    // for differing '2+x+1' and'2+0x+1'
                    x += sign * (num ? num : j - 2 < 0 || (s[j - 2] == '+' || s[j - 2] == '-') ? 1 : 0);
                else
                    n += sign * num;
                sign = s[j] == '+' ? 1 : -1;
                num = 0;
            }
            else if (s[j] >= '0' && s[j] <= '9')
                num = num * 10 + (s[j] - '0');
        }
        return {x, n};
    }
    string solveEquation(string equation) {
        auto find = equation.find('=');
        auto [xl, nl] = parse(equation.substr(0, find));
        auto [xr, nr] = parse(equation.substr(find + 1));

        int x = xl - xr, n = nr - nl;
        if (x == 0 && n == 0)
            return "Infinite solutions";
        else if (x == 0)
            return "No solution";
        else return "x=" + to_string(n / x);
    }
};
```

or

```cpp
class Solution {
public:
    pair<int, int> parse(string s) {
        int x = 0, n = 0, num = INT_MIN, sign = 1;
        s.push_back('+');
        for (int j = 0; j < s.size(); j++) {
            if (s[j] == '+' || s[j] == '-') {
                if (j - 1 >= 0 && s[j - 1] == 'x')
                    x += sign * (num == INT_MIN ? 1 : num);
                else if (num != INT_MIN)
                    n += sign * num;
                sign = s[j] == '+' ? 1 : -1;
                num = INT_MIN;
            }
            else if (s[j] >= '0' && s[j] <= '9') {
                if (num == INT_MIN) num = 0;
                num = num * 10 + (s[j] - '0');
            }
        }
        return {x, n};
    }
    string solveEquation(string equation) {
        auto find = equation.find('=');
        auto [xl, nl] = parse(equation.substr(0, find));
        auto [xr, nr] = parse(equation.substr(find + 1));

        int x = xl - xr, n = nr - nl;
        if (x == 0 && n == 0)
            return "Infinite solutions";
        else if (x == 0)
            return "No solution";
        else return "x=" + to_string(n / x);
    }
};
```

2. ##### regex matching

```cpp

```