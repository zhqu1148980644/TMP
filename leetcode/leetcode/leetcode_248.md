---
title: Strobogrammatic Number III
date: 2021-01-04
---
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

Example:

Input: low = "50", high = "100"
Output: 3 
Explanation: 69, 88, and 96 are three strobogrammatic numbers.
Note:
Because the range might be a large number, the low and high numbers are represented as string.


#### Solutions


1. ##### dfs


```cpp
class Solution {
public:
    vector<pair<char, char>> cp = {{'6', '9'}, {'9', '6'}, {'0', '0'}, {'8', '8'}, {'1', '1'}};
    int res = 0;
    string lo, hi;
    void dfs(string & s, int l, int r) {
        if (l > r) {
            if (l && s.size() == hi.size() && s > hi) return;
            if (l && s.size() == lo.size() && s < lo) return;
            res++;
        }
        else if (l == r)
            for (auto c : {'1', '8', '0'}) {
                s[l] = c;
                dfs(s, l + 1, r - 1);
            }
        else
            for (auto & [c1, c2] : cp) {
                if (!l && c1 == '0') continue;
                s[l] = c1; s[r] = c2;
                dfs(s, l + 1, r - 1);
            }
    }

    int strobogrammaticInRange(string low, string high) {
        this->lo = low, this->hi = high;
        for (int i = low.size(); i <= high.size(); i++) {
            string tmp(i, '0');
            dfs(tmp, 0, i - 1);
        }
        return res;
    }
};
```

Or

```cpp
class Solution {
public:
    vector<pair<char, char>> cp = {{'6', '9'}, {'9', '6'}, {'0', '0'}, {'8', '8'}, {'1', '1'}};
    int res = 0;
    void dfs(string & lo, string & hi, string cur) {
        if (cur.size() > hi.size()) return;
        else if (cur.size() <= hi.size() && cur.size() >= lo.size()) {
            if (cur.size() == hi.size() && cur > hi) return;
            if (cur.size() == lo.size() && cur < lo) return;
            if (!(cur.size() > 1 && cur[0] == '0')) res++;
        }
        for (auto & [c1, c2] : cp)
            dfs(lo, hi, c1 + cur + c2);
    }
    int strobogrammaticInRange(string low, string high) {
        for (auto mid : {"", "1", "0", "8"})
            dfs(low, high, mid);
        return res;
    }
};
```