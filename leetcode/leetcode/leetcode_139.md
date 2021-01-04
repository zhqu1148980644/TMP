---
title: Word Break
date: 2021-01-04
---
#### Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

### Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

```
Example 1:

Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".
Example 2:

Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.
Example 3:

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false
```

#### Solutions

1. ##### backtrack with memoization  O(n2)

- `breakable[i]` means if suffix `s[i:]` is breakable.

```cpp
class Solution {
private:
    unordered_set<string> m;
    unordered_map<int, bool> breakable;

public:
    bool canBreak(string s, int start) {
        if (start == s.size())
            return true;
        if (breakable.count(start))
            return breakable[start];
        for (int i = start; i < s.size(); i++) {
            auto word = s.substr(start, i - start + 1);
            if (m.count(word) && canBreak(s, i + 1))
                return breakable[start] = true;

        }
        return breakable[start] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        for (auto & word : wordDict) m.insert(word);
        return canBreak(s, 0);
    }
};
```

- Since the program will exit whenever we meets a breakable suffix, we can use a boolean array to record the unbreakable suffix. ie: breakable suffix will never be visited twice.

```cpp
class Solution {
public:
    unordered_set<string> m;
    vector<bool> breakable;
    bool canbreak(string & s, int st) {
        if (st == s.size())
            return true;
        if (!breakable[st])
            return false;
        for (int i = st; i < s.size(); i++) {
            auto word = s.substr(st, i - st + 1);
            if (m.count(word) && canbreak(s, i + 1))
                return true;
        }
        return breakable[st] = false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        for (auto & s : wordDict)
            m.insert(s);
        breakable = vector<bool>(s.size(), true);
        return canbreak(s, 0);    
    }
};
```

Python version

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        from functools import lru_cache
        @lru_cache(None)
        def canbreak(start):
            if start == length:
                return True
            for i in range(start, length + 1):
                if s[start: i + 1] in words and canbreak(i + 1):
                    return True
            return False

        length = len(s)
        words = set(wordDict)
        return canbreak(0);
```


2. ##### dynamic programming  O(n2)



```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> canbreak(s.size() + 1, false);
        canbreak[0] = true;
        unordered_set<string> m(wordDict.begin(), wordDict.end());
        // canbreal[j] means if prefix s[:j) is breakable.
        for (int i = 1; i <= s.size(); i++)
            for (int j = 0; j < i; j++) {
                if (canbreak[j] && m.count(s.substr(j, i - j))) {
                    canbreak[i] = true;
                    break;
                }
            }
        return canbreak[s.size()];
    }
};
```

Or skip impossible prefix and suffix.

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (!wordDict.size()) return false;
        vector<bool> canbreak(s.size() + 1, false);
        canbreak[0] = true;
        unordered_set<string> m(wordDict.begin(), wordDict.end());
        int minlen = INT_MAX, maxlen = INT_MIN;
        for (auto & word : wordDict) {
            minlen = min(minlen, (int)word.size());
            maxlen = max(maxlen, (int)word.size());
        }
        // canbreal[j] means if prefix s[:j) is breakable.
        for (int i = minlen; i <= s.size(); i++)
            for (int j = max(i - maxlen, 0); j <= i - minlen; j++) {
                if (canbreak[j] && m.count(s.substr(j, i - j))) {
                    canbreak[i] = true;
                    break;
                }
            }
        return canbreak[s.size()];
    }
};
```

