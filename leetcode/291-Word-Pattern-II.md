Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

 

Example 1:

Input: pattern = "abab", str = "redblueredblue"
Output: true
Example 2:

Input: pattern = "aaaa", str = "asdasdasdasd"
Output: true
Example 3:

Input: pattern = "aabb", str = "xyzabcxzyabc"
Output: false
 

Constraints:

You may assume both pattern and str contains only lowercase letters.


#### Solutions


1. ##### backtrack(dfs)


```c++
class Solution {
public:
    unordered_map<char, string_view> map;
    unordered_set<string_view> ms;
    string pattern;
    string_view str;

    bool dfs(int cur, int st) {
        if (cur == pattern.size()) 
            return !(st < str.size());
        char c = pattern[cur];
        // key point for pruning.
        int last = str.size() - (pattern.size() - cur);
        int i = cur == pattern.size() - 1 ? last : st;
        for (i = st; i <= last; i++) {
            auto w = str.substr(st, i - st + 1);
            if (map.count(c)) {
                if (map[c] != w) continue;
                if (dfs(cur + 1, i + 1))
                    return true;
            }
            else {
                if (ms.count(w)) continue;
                map[c] = w; ms.insert(w);
                if (dfs(cur + 1, i + 1))
                    return true;
                map.erase(c); ms.erase(w);
            }
        }
        return false;
    }
    bool wordPatternMatch(string pattern, string str) {
        this->pattern = move(pattern);
        this->str = string_view(str);
        return dfs(0, 0);
    }
};
```