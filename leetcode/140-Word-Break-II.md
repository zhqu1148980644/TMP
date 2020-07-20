#### SolutionsGiven a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

#### Note:

- The same word in the dictionary may be reused multiple times in the segmentation.
- You may assume the dictionary does not contain duplicate words.

```
Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]
Example 2:

Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]
```

#### Solutions


1. ##### dynamic programming

```c++
class Solution {
public:
    bool canbreak(string & s, unordered_set<string> & words) {
        vector<bool> breakable(s.size() + 1);
        breakable[0] = true;
        int minl = INT_MAX, maxl = INT_MIN;
        for (auto & word : words) {
            minl = min(minl, (int)word.size());
            maxl = max(maxl, (int)word.size());
        }
        for (int i = minl; i <= s.size(); i++)
            for (int j = max(i - maxl, 0); j <= i - minl; j++)
                if (breakable[j] && words.count(s.substr(j, i - j))) {
                    breakable[i] = true;
                    break; 
                }
        return breakable.back();
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        if (!canbreak(s, words)) return {};

        vector<vector<string>> dp{{""}};
        for (int i = 1; i <= s.size(); i++) {
            dp.push_back({});
            for (int j = 0; j < i; j++) {
                auto word = s.substr(j, i - j);
                if (words.count(word))
                    for (auto & sent : dp[j])
                        dp[i].push_back(sent.size() ? sent + " " + word : word);
            }
        }
        return dp[s.size()];
    }
};
```



2. ##### backtrack with recursion

```c++
class Solution {
public:
    bool canbreak(string & s, unordered_set<string> & words) {
        vector<bool> breakable(s.size() + 1);
        breakable[0] = true;
        int minl = INT_MAX, maxl = INT_MIN;
        for (auto & word : words) {
            minl = min(minl, (int)word.size());
            maxl = max(maxl, (int)word.size());
        }
        for (int i = minl; i <= s.size(); i++)
            for (int j = max(i - maxl, 0); j <= i - minl; j++)
                if (breakable[j] && words.count(s.substr(j, i - j))) {
                    breakable[i] = true;
                    break; 
                }
        return breakable.back();
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<int, vector<string>> mem {{s.size(), {""}}};
        unordered_set<string> m(wordDict.begin(), wordDict.end());

        function<vector<string>(int)> Break = [&](int st) {
            if (!mem.count(st)) {
                for (int i = st; i < s.size(); i++) {
                    auto w = s.substr(st, i - st + 1);
                    if (!m.count(w)) continue;
                    for (auto & sent : Break(i + 1))
                        mem[st].push_back(w + (sent.size() ? " " : "") + sent);
                }
            }
            return mem[st];
        };
        return Break(0);
    }
};
```

Python version

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        from functools import lru_cache

        @lru_cache(None)
        def Break(start):
            return [s[start: end + 1] + (" " + suffix if suffix else "")
                    for end in range(start, length)
                    if s[start: end + 1] in words
                    for suffix in Break(end + 1)] if start != length else [""]

        words, length = set(wordDict), len(s)
  
        return list(Break(0))
```