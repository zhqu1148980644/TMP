---
title: Fraction Addition and Subtraction
date: 2021-01-04
---
Given a string representing an expression of fraction addition and subtraction, you need to return the calculation result in string format. The final result should be irreducible fraction. If your final result is an integer, say 2, you need to change it to the format of fraction that has denominator 1. So in this case, 2 should be converted to 2/1.

Example 1:
Input:"-1/2+1/2"
Output: "0/1"
Example 2:
Input:"-1/2+1/2+1/3"
Output: "1/3"
Example 3:
Input:"1/3-1/2"
Output: "-1/6"
Example 4:
Input:"5/3+1/3"
Output: "2/1"
Note:
The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
Each fraction (input and output) has format ±numerator/denominator. If the first input fraction or the output is positive, then '+' will be omitted.
The input only contains valid irreducible fractions, where the numerator and denominator of each fraction will always be in the range [1,10]. If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
The number of given fractions will be in the range [1,10].
The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.

#### Solutions

1. ##### Least common multiple

- `lcm(a, b) = a * b / gcd(a, b)`
- `lcm(a, b, c, d, e ..) = lcm(lcm(lcm(a, b), c), d)...`

```cpp
class Solution {
public:
    vector<pair<int, int>> split(string & s) {
        if (!s.size()) return {};
        vector<pair<int, int>> res;
        s.push_back('+');
        int i = 0, a, b;
        for (int j = 1; j < s.size(); j++) {
            if (s[j] == '+' || s[j] == '-') {
                string tmp = s.substr(i, j - i);
                sscanf(tmp.c_str(), "%d/%d", &a, &b);
                bool neg = a * b < 0;
                res.emplace_back(neg ? -abs(a) : abs(a), abs(b));
                i = j;
            }
        }
        return res;
    }
    string fractionAddition(string expression) {
        auto fracs = split(expression);
        auto gcd = [](int a, int b) {
            while (b) {
                a %= b; swap(a, b);
            }
            return a;
        };
        int lcm = 1;
        for (auto & [nu, deno] : fracs)
            lcm = lcm * deno / gcd(lcm, deno);
        
        int num = 0;
        for (auto & [nu, deno] : fracs)
            num += nu * (lcm / deno);

        int g = gcd(abs(num), lcm);

        return to_string(num / g) + "/" + to_string(lcm / g);
    }
};
```

or split with regex

```cpp
class Solution {
public:
    string fractionAddition(string expression) {
        auto gcd = [](int a, int b) {
            while (b) {
                a %= b; swap(a, b);
            }
            return a;
        };
        int a, b;
        queue<pair<int, int>> q;
        string_view s(expression);
        std::regex frac_re(R"(([+-]*\d+/\d+))", std::regex::optimize);
        auto begin = cregex_token_iterator(s.begin(), s.end(), frac_re);
        auto end = cregex_token_iterator();
        string tmp(20, ' ');
        for (auto it = begin; it != end; it++) {
            tmp.assign(it->first, it->second);
            sscanf(tmp.c_str(), "%d/%d", &a, &b);
            q.emplace(a, b);
        }
        
        while (q.size() >= 2) {
            auto [n1, d1] = q.front(); q.pop();
            auto [n2, d2] = q.front(); q.pop();
            int p = n1 * d2 + n2 * d1;
            int d = d1 * d2;
            int g = gcd(abs(p), d);
            q.emplace(p / g, d / g);
        }
        
        auto [n, d] = q.front(); q.pop();
        int g = gcd(abs(n), d);
        return to_string(n / g) + "/" + to_string(d / g);
    }
};
```