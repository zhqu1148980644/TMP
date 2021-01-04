---
title: Restore IP Addresses
date: 2021-01-04
---
#### Given a string containing only digits, restore it by returning all possible valid IP address combinations.

```
Example:

Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]
```

#### Solutions

1. ##### dfs

```cpp
class Solution {
private:
    vector<string> res;
    vector<string> com;

    void dfs(string & s, int start) {
        if (start == s.size()) {
            if (com.size() != 4) return;
            string ip = com[0];
            for (int i = 1; i < 4; i++)
                ip = ip + "." + com[i];
            res.push_back(move(ip));
        }

        for (int i = start; i < start + 3 && i < s.size(); i++) {
            string subs = s.substr(start, i - start + 1);
            if (subs.size() > 1 && subs[0] == '0') continue;
            if (stoi(subs) <= 255) {
                com.push_back(move(subs));
                dfs(s, i + 1);
                com.pop_back();
            }
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        if (s.size() <= 4 * 3) dfs(s, 0);
        return res;
    }
};
```

2. ##### straight forward

```cpp
#define valid(s) ((!(s.size() > 1 && s[0] == '0') && stoi(s) <= 255))
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.size() > 12) return {};
        vector<string> res;
        int len = s.size();
        for (int i = 0; i < 3 && i <= len - 4; i++) {
            string s1 = s.substr(0, i + 1);
            if (!valid(s1)) continue;
            for (int j = i + 1; j <= i + 3 && j <= len - 3; j++) {
                string s2 = s.substr(i + 1, j - i);
                if (!valid(s2)) continue;
                for (int k = j + 1; k <= j + 3 && k <= len - 2; k++) {
                    if (s.size() > k + 4) continue;
                    string s3 = s.substr(j + 1, k - j);
                    if (!valid(s3)) continue;
                    string s4 = s.substr(k + 1, 3);
                    if (!valid(s4)) continue;
                    res.push_back(s1 + "." + s2 + "." + s3 + "." + s4);
                }
            }
        }
        return res;
    }
};
```