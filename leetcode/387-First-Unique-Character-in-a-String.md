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
        vector<int> counter(26, INT_MAX);
        for (int i = 0; i < s.size(); i++)
            if (counter[s[i] - 'a'] != INT_MAX)
                counter[s[i] - 'a'] = -1;
            else
                counter[s[i] - 'a'] = i;
        
        int minindex = INT_MAX;
        for (int i = 0; i < 26; i++)
            if (counter[i] != -1)
                minindex = min(minindex, counter[i]);
        
        return minindex == INT_MAX ? -1 : minindex;
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