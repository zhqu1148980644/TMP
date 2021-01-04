---
title: Generate Parentheses
date: 2021-01-04
---
### Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

```
For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
```



### Soltuions

1. #### dynamic programming

Iteratively build lists of k-valid parentheses untill k reaches n.

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> res = {{""}, {"()"}};

        for (int i = 2; i <= n; i++) {
            vector<string> res1;
            for (int j = 0; j < i; j++) {
                for (auto & s1 : res[j])
                    for (auto & s2 : res[i - j - 1])
                        res1.push_back("(" + s1 + ")" + s2);
            }
            res.push_back(move(res1));
        }
        
        return res[n];
    }
};
```

2. #### recursion with backtracking

- Keeping track of left and right brackets.
- Add right brackt only when the number of left brackets is larger than the number of right brackets.

```cpp
class Solution {
public:
    vector<string> res;
    int n;

    void solve(string & s, int left, int right) {
        if (s.size() == 2 * n)
            res.push_back(s);
        else {
            if (left < n) {
                s.push_back('(');
                solve(s, left + 1, right);
                s.pop_back();
            }
            if (right < left) {
                s.push_back(')');
                solve(s, left, right + 1);
                s.pop_back();
            }
        }
    }

    vector<string> generateParenthesis(int n) {
        this->n = n;
        string base;
        solve(base, 0, 0);
        return res;
    }
};
```

```python
class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []
        def backtrack(s, left, right):
            if len(s) == 2 * n:
                res.append(s)
                return
            if (left < n):
                backtrack(s + "(", left + 1, right)
            if (right < left):
                backtrack(s + ')', left, right + 1)
        backtrack("", 0, 0)
        return res
```

3. #### Closure Number