Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

#### Solutions

1. ##### sliding window

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) return {};
        vector<int> m(26);
        for (auto c : p) m[c - 'a']++;

        vector<int> res;
        int i = 0, j = 0, matched = 0;
        while (j < s.size()) {
            if (--m[s[j++] - 'a'] < 0)
            // move i forward till the window is ok
            // there are two cases: 1: the char shows too many times, 2: the char doesn't exist in p
                while (++m[s[i++] - 'a'] != 0)
                    matched--;
            else
                matched++;
            if (matched == p.size())
                res.push_back(i);
        }

        return res;
    }
};
```