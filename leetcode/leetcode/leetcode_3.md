---
title: Longest Substring Without Repeating Characters
date: 2021-01-04
---
### Given a string, find the length of the longest substring without repeating characters.

### Example 1

```
Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
```

### Example 2

```
Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

### Example 3

```
Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
            Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```


### Solutions

1. #### Brute force O(n3)

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        max_len = 0
        for i in range(len(s)):  #O(n)
            for j in range(i + 1, len(s) + 1): #O(n)
                if len(set(s[i: j])) == j - i: #O(j - i)
                    max_len = j - i if max_len < j - i else max_len
        return max_len
```

2. #### Sliding window O(n) S(n)

- Use a hash set to record the occurence of characters we see before and maitain two pointer `i and j` to ensure that there are no duplicate within `s[i:j]`.

- When the current `s[j]` character doesn't exist in hashset, this means `s[i:j]` contain no duplicate characters. So record the current length `j - i + 1` and update `max_len` if needed.
- When the current `s[j]` character are fond in hashset, unset `s[i]` and move i one step forward. This step may be called sevaral times until the duplicate of `s[j]` is removed and `s[i:j]` is `non-duplicated` again.

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> seen;
        int i = 0, j = 0, max_len = 0;
        while (i < s.size() && j < s.size()) {
            auto it = seen.find(s[j]);
            if (it == seen.end()) {
                max_len = max(j - i + 1, max_len);
                seen.insert(s[j++]);
            } else
                seen.erase(s[i++]);
        }
        return max_len;
    }
};
```

Or use template borrowed from others.
- https://leetcode.com/problems/minimum-window-substring/discuss/26808/Here-is-a-10-line-template-that-can-solve-most-'substring'-problems


```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int count[128] = {0}, maxlen = 0;
        int i = 0, j = 0;
        while (j < s.size()) {
            if (++count[s[j++]] == 2)
                while (--count[s[i++]] != 1);
            if (j - i >= maxlen)
                maxlen = j - i;
        }
        return maxlen;
    }
};
```

Use the same template in problem: `Longest Substring with At Most Two Distinct Characters`

```cpp
int lengthOfLongestSubstringTwoDistinct(string s) {
    int count[128] = {0};
    int counter = 0, i = 0, j = 0, maxlen = 0;
    while (j < s.size()) {
        if (++count[s[j++]] == 1) counter++;
        while (counter > 2)
            if (--count[s[i++]] == 0) counter--;
        if (j - i >= maxlen)
            maxlen = j - i;
    }
    return maxlen;
}
```

Use the same template in problem: `minimum window substring`

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int count[128] = {0};
        for (auto & c : t) count[c]++;
        int i = 0, j = 0, counter = t.size();
        int minlen = s.size(), start = s.size();
        while (j < s.size()) {
            if (--count[s[j++]] >= 0) counter--;
            if (counter == 0) {
                while (counter == 0)
                    if (++count[s[i++]] > 0) counter++;
                if (j - i  + 1 <= minlen) {
                    minlen = j - i + 1;
                    start = i - 1;
                }
            }
        }
        return start == s.size() ? "" : s.substr(start, minlen);
    }
};
```

3. #### Optimised Sliding window O(n) S(n)

As we can see in the second method, We have to move the `s[i]` forward several times until the duplicate of `s[j]` is removed. Why don't we jump directly to the index `next` to the duplicate of `s[j]`. 

- A `HashMap` can be used to record this information. ie. Each character's last index + 1 we seen before.
- For ascii characters. We can directly use `int[256]` as a hashmap.

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int cache[128] = {0};
        int i = 0, res = 0;
        for (int j = 0; j < s.size(); j++) {
            i = max(i, cache[s[j]]);
            if (j - i + 1 > res)
                res = j - i + 1;
            cache[s[j]] = j + 1;
        }

        return res;
    }
};
```
