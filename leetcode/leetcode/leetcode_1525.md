---
title: Number of Good Ways to Split a String
date: 2021-01-04
---
You are given a string s, a split is called good if you can split s into 2 non-empty strings p and q where its concatenation is equal to s and the number of distinct letters in p and q are the same.

Return the number of good splits you can make in s.

 

Example 1:

Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.
Example 2:

Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").
Example 3:

Input: s = "aaaaa"
Output: 4
Explanation: All possible splits are good.
Example 4:

Input: s = "acbadbaada"
Output: 2
 

Constraints:

s contains only lowercase English letters.
1 <= s.length <= 10^5


#### Solutions

1. ##### hashs set

```cpp
class Solution {
public:
    int numSplits(string s) {
        int count1[126] = {0}, count2[126] = {0};
        int c1 = 0, c2 = 0;
        for (auto c : s)
            if (++count2[c] == 1)
                c2++;
        
        int res = 0;
        for (int i = 0; i < s.size() - 1; i++) {
            if (++count1[s[i]] == 1) c1++;
            if (--count2[s[i]] == 0) c2--;
            res += c1 == c2;
        }
        
        return res;
    }
};
```