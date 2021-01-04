---
title: Longest Common Prefix
date: 2021-01-04
---
### Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

```
Example 1:

Input: ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
```

### Note:

All given inputs are in lowercase letters a-z.


### Solutions

Base condition: common prefix between two strings.

There is no tricky way can fetch the common prefix with time less than `O(n)` when comparing two string.

```cpp
int commonPrefix(string & str1, string & str2) {
    int min_len = min(str1.size(), str2.size());
    for (int i = 0; i < min_len; i++) {
        if (str1[i] != str2[i])
            return i;
    }
    return min_len;
}
```

1. #### horizontal scanning O(n)

`commonPrefix(s1, s2, s3) = commnPrefix(commonPrefix(s1, s2), s3)`

This can be generalized to any number of strings.

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (!strs.size()) return "";
        int min_i = 0, min_len = strs[0].size();
        // get the shortest string.
        for (int i = 1; i < strs.size(); i++)
            if (strs[i].size() < min_len) {
                min_len = strs[i].size();
                min_i = i;
            }
        string prefix = strs[min_i];
        for (int i = 0; i < strs.size(); i++) {
            if (i == min_i) continue;
            prefix = prefix.substr(0, commonPrefix(prefix, strs[i]));
            if (!prefix.size()) return "";
        }
        return prefix; 
    }
};
```

2. #### vertical scanning O(n)

We can also iteratively check every position from the beginning.

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string> & strs) {
        if (!strs.size()) return "";
        int min_len = strs[0].size();
        for (int i = 1; i < strs.size(); i++)
            if (strs[i].size() < min_len)
                min_len = strs[i].size();
        for (int i = 0; i < min_len; i++) {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (c != strs[j][i]) return strs[0].substr(0, i);
            }
        }
        return strs[0].substr(0, min_len);
    }
};
```

3. #### divide and conquer O(n)

- The same time complexity.
- A recursion verison would cost extra mlog(n) space. log(n) times stack call, m space for intermediate commonPrefix.
