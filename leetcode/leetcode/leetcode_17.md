---
title: Letter Combinations of a Phone Number
date: 2021-01-04
---
### Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.



### Example:

```
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
```

### Note:

Although the above answer is in lexicographical order, your answer could be in any order you want.

### Solutions

Since characters in each position are totally different. No need to care about duplicate.

1. #### Recursive 

```python
class Solution:
    phone = {'2': ['a', 'b', 'c'],
             '3': ['d', 'e', 'f'],
             '4': ['g', 'h', 'i'],
             '5': ['j', 'k', 'l'],
             '6': ['m', 'n', 'o'],
             '7': ['p', 'q', 'r', 's'],
             '8': ['t', 'u', 'v'],
             '9': ['w', 'x', 'y', 'z']}  
    
    def letterCombinations(self, digits: str) -> List[str]:
        if not digits:
            return []
        return [c + x 
                for x in self.letterCombinations(digits[1:]) or [""] 
                for c in self.phone[digits[0]]];
```

2. #### Backtracking

```cpp
class Solution {
public:
    string cur;
    vector<string> res;
    string chars[10] = {"", "", "abc", "def", "ghi", "jkl", 
                        "mno", "pqrs", "tuv", "wxyz"};
    void dfs(string & digits, int st) {
        if (st == digits.size())
            res.push_back(cur);
        else {
            for (auto c : chars[digits[st] - '0']) {
                cur += c;
                dfs(digits, st +1);
                cur.pop_back();
            }
        }
    }
    vector<string> letterCombinations(string digits) {
        if (digits.size()) dfs(digits, 0);
        return res;
    }
};
```
