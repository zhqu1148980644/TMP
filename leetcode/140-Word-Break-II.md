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

- Memory limit exceed
- A huge amount of undesirable subsolutions(prefix) are stored in the dp table.

```c++
class Solution {
public:
    bool canBreak(string & s, unordered_set<string> & m) {
        if (!m.size()) return false;
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++)
            for (int j = 0; j < i; j++) {
                if (dp[j] && m.count(s.substr(j, i - j)))
                    return true;
            }
        return false;
    }

    typedef string Sentence;
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> m(wordDict.begin(), wordDict.end());
        if (!canBreak(s, m)) return {};

        vector<vector<Sentence>> dp{{""}};

        for (int i = 1; i <= s.size(); i++) {
            dp.push_back(vector<Sentence>());
            for (int j = 0; j < i; j++) {
                auto word = s.substr(j, i - j);
                if (dp[j].size() && m.count(word))
                    for (auto & sent : dp[j])
                        dp[i].push_back(sent.size() ? sent + " " + word : word);
            }
        }
        return dp[s.size()];
    }
};
```


- To solve this problem, we can build the results backwards with minimal number of suffixs.

2. ##### backtrack with recursion

- Since backtracking builds results in a bottom-up way, only necessary suffix will be stored and thus reducing the memory usage.

```c++
typedef vector<string> Sents;
class Solution {
public:
    Sents Break(unordered_map<int, Sents> & memo,
                unordered_set<string> & words,
                string & s, int start) {
        if (start == s.size())
            return {""};
        if (memo.count(start))
            return memo[start];

        Sents sents;
        for (int i = start; i < s.size(); i++) {
            string word = s.substr(start, i - start + 1);
            if (words.count(word))
                for (auto & sent : Break(memo, words, s, i + 1))
                    sents.push_back(word + (sent.size() ? " " : "") + sent);
        }

        return memo[start] = move(sents);
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (!wordDict.size()) return {};
        unordered_map<int, Sents> memo;
        unordered_set<string> words(wordDict.begin(), wordDict.end());

        return Break(memo, words, s, 0);
    }
};
```

Or a fancy one borrowed from stephan.

```c++
class Solution {
public:
    bool canbreak(string & s, unordered_set<string> & words) {
        vector<bool> breakable(s.size() + 1, false);
        breakable[0] = true;
        int minlen = INT_MAX, maxlen = INT_MIN;
        for (auto & word : words) {
            minlen = min(minlen, (int)(word.size()));
            maxlen = max(maxlen, (int)(word.size()));
        }

        for(int i = minlen; i <= s.size(); i++)
            for (int j = max(i - maxlen, 0); j <= i - minlen; j++)
                if (breakable[j] && words.count(s.substr(j, i - j))) {
                    breakable[i] = true;
                    break;
                }
        return breakable[s.size()];
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        // prexit if the whole string is not breakable.
        if (!canbreak(s, words)) return {};

        unordered_map<int, vector<string>> memo = {{s.size(), {""}}};
        // use a lambda function
        function<vector<string>(int)> Break = [&](int start) {
            if (!memo.count(start)) {
                for (int i = start; i < s.size(); i++) {
                    string word = s.substr(start, i - start + 1);
                    if (!words.count(word)) continue;
                    for (auto & sent : Break(i + 1))
                        memo[start].push_back(word + (sent.size() ? " " : "") + sent);
                }
            }
            return memo[start];
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