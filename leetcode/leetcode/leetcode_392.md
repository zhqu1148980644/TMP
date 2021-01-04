---
title: Is Subsequence
date: 2021-01-04
---
#### Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in both s and t. t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).

```
Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.
```

#### Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence. In this scenario, how would you change your code?

#### Credits:
Special thanks to @pbrother for adding this problem and creating all test cases.

#### Solutions

1. ##### Two pointers

```cpp
bool isSubsequence(char * s, char * t){
    while (*s && *t) {
        if (*s == *t)
            s++;
        t++;
    }
    return *s == '\0';
}
```

2. ##### binary search

- Record indexes of each char in t.
- Use binary search to find the first occurrence in the legal range, and shrink the legal range after each match.

```cpp
class Solution {
public:
    int bisearch(vector<int> & nums, int target) {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + ((hi - lo) / 2);
            if (target > nums[mid])
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo;
    }
    bool isSubsequence(string s, string t) {
        if (t.size() < s.size())
            return false;
        
        vector<vector<int>> cache(26);
        for (int i = 0; i < t.size(); i++)
            cache[t[i] - 'a'].push_back(i);
        
        int target = -1;
        for (auto c : s) {
            if (!cache[c - 'a'].size())
                return false;
            // use upper_bound
            int find = bisearch(cache[c - 'a'], target + 1);
            if (find >= cache[c - 'a'].size())
                return false;
            target = cache[c - 'a'][find];
        }
        return true;
    }
};
```