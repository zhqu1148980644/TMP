---
title: Find Words That Can Be Formed by Characters
date: 2021-01-04
---
You are given an array of strings words and a string chars.

A string is good if it can be formed by characters from chars (each character can only be used once).

Return the sum of lengths of all good strings in words.

 

Example 1:

Input: words = ["cat","bt","hat","tree"], chars = "atach"
Output: 6
Explanation: 
The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
Example 2:

Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
Output: 10
Explanation: 
The strings that can be formed are "hello" and "world" so the answer is 5 + 5 = 10.
 

Note:

1 <= words.length <= 1000
1 <= words[i].length, chars.length <= 100
All strings contain lowercase English letters only.

#### Solutions

1. ##### hash map

```cpp
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        vector<int> canuse(126);
        for (auto c : chars)
            canuse[c]++;
        
        int res = 0;
        for (auto & w : words) {
            vector<int> need(126);
            bool ok = true;
            for (auto c : w)
                if (++need[c] > canuse[c]) {
                    ok = false;
                    break;
                }
            if (ok) res += w.size();
        }

        return res;
    }
};
```