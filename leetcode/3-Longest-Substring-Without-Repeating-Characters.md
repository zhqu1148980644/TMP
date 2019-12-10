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

```c++
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

3. #### Optimised Sliding window O(n) S(n)

As we can see in the second method, We have to move the `s[i]` forward several times until the duplicate of `s[j]` is removed. Why don't we jump directly to the index `next` to the duplicate of `s[j]`. 

- A `HashMap` can be used to record this information. ie. Each character's last index we seen before.
- For ascii characters. We can directly use `int[256]` as a hashmap.

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int maps[128] = {0};
        int n = s.length(), ans = 0;
        for (int i = 0, j = 0; j < n; ++j) {
            char & c = s[j];
            i = max(maps[c], i);
            ans = max(ans, j - i + 1);
            maps[c] = j + 1;
        }
        return ans;
    }
};
```
