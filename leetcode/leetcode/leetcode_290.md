---
title: Word Pattern
date: 2021-01-04
---
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Example 1:

Input: pattern = "abba", str = "dog cat cat dog"
Output: true
Example 2:

Input:pattern = "abba", str = "dog cat cat fish"
Output: false
Example 3:

Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
Example 4:

Input: pattern = "abba", str = "dog dog dog dog"
Output: false
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters that may be separated by a single space.

#### Solutions

1. ##### hashmap O(n)

- Check `problem 205` for details.
- Record each string's previous appearance index, if two strings are isomorphic, the index pair of each position should be the same.

```cpp
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<int> ls(26);
        unordered_map<string, int> rs;
        int i = 0;
        istringstream ss(str); string s;
        for (i = 0; i < pattern.size() && (ss >> s); i++) {
            if (ls[pattern[i] - 'a'] != rs[s])
                return false;
            ls[pattern[i] - 'a'] = rs[s] = i + 1;
            if (rs.size() > 26) return false;
        }
        return pattern.size() == i && ss.eof();
    }
};
```

2. ##### hashmap O(n2)

- `in` is used for detecting cases like: `ab, "c c"`  `aba, "a a a a a"`

```python
class Solution:
    def wordPattern(self, pattern: str, str: str) -> bool:
        s = str.split(' ')
        if len(s) != len(pattern):
            return False
        m = {}
        for i, c in enumerate(pattern):
            if c in m:
                if m[c] != s[i]:
                    return False
            else:
                if s[i] in m.values():
                    return False
                m[c] = s[i]
        return True
```


Or reduce the complexity to O(n) by two passes

```python
class Solution:
    def wordPattern(self, pattern: str, str: str) -> bool:
        def unique(pattern, str):
            s = str.split(' ')
            if len(s) != len(pattern) or len(set(s)) != len(set(pattern)):
                return False
            m = {}
            for i, c in enumerate(pattern):
                if c in m:
                    if m[c] != s[i]:
                        return False
                else:
                    m[c] = s[i]
            return True
        return unique(pattern, str) and unique(pattern[::-1], str[::-1])
```