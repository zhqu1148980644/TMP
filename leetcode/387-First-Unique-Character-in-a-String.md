#### Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

```
Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
```

#### Note: You may assume the string contain only lowercase letters. 

#### Solutions

1. ##### straight forward

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> m(26, INT_MAX);
        for (int i = 0; i < s.size(); i++)
            if (m[s[i] - 'a'] == INT_MAX)
                m[s[i] - 'a'] = i;
            else
                m[s[i] - 'a'] = -1;
        int res = INT_MAX;
        for (int i = 0; i < 26; i++)
            if (m[i] != -1)
                res = min(res, m[i]);

        return res == INT_MAX ? -1 : res;
    }
};
```

Or a general method

```c++
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<int, int> counter;
        for (auto & c : s)
            counter[c]++;
        for (int i = 0; i < s.size(); i++)
            if (counter[s[i]] == 1)
                return i;
        return -1;
    }
};
```