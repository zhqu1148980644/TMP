A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

Example:

Input:  n = 2
Output: ["11","69","88","96"]

#### Solutions

1. ##### dynamic programming

```c++
class Solution {
public:
    vector<vector<string>> res = {
        {"1", "8", "0"},
        {"11", "88", "69", "96"}
    };

    vector<string> findStrobogrammatic(int n) {
        if (n <= 2) return n == 2 ? res[1] : res[0];
        vector<string> pprev, prev(res[1]);
        
        for (int i = 3; i <= n; i++) {
            vector<string> cur;
            int odd = i % 2;
            for (auto & s2 : (odd ? prev : pprev)) {
                int half = s2.size() / 2;
                auto sl = s2.substr(0, half), sr = s2.substr(half);
                for (auto & s1 : res[odd ? 0 : 1])
                    cur.push_back(sl + s1 + sr);
                if (!odd)
                    cur.push_back(sl + "00" + sr);
            }
            pprev = move(prev);
            prev = move(cur);
        }
    
        return prev;
    }
};
```

2. ##### dfs

```c++
class Solution {
public:
    vector<pair<char, char>> cp = {{'6', '9'}, {'9', '6'}, {'0', '0'}, {'8', '8'}, {'1', '1'}};
    vector<string> res;

    void dfs(string & s, int l, int r) {
        if (l > r)
            res.emplace_back(s);
        else if (l == r)
            for (auto c : {'1', '8', '0'}) {
                s[l] = c;
                res.emplace_back(s);
            }
        else
            for (auto & [c1, c2] : cp) {
                if (!l && c1 == '0') continue;
                s[l] = c1; s[r] = c2;
                dfs(s, l + 1, r - 1);
            }
    }
    vector<string> findStrobogrammatic(int n) {
        string tmp(n, ' ');
        dfs(tmp, 0, n - 1);
        return res;
    }
};
```