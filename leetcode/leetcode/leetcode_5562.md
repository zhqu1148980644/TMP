---
title: Minimum Deletions to Make Character Frequencies Unique
date: 2021-01-04
---
A string s is called good if there are no two different characters in s that have the same frequency.

Given a string s, return the minimum number of characters you need to delete to make s good.

The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.

 

Example 1:

Input: s = "aab"
Output: 0
Explanation: s is already good.
Example 2:

Input: s = "aaabbbcc"
Output: 2
Explanation: You can delete two 'b's resulting in the good string "aaabcc".
Another way it to delete one 'b' and one 'c' resulting in the good string "aaabbc".
Example 3:

Input: s = "ceabaacb"
Output: 2
Explanation: You can delete both 'c's resulting in the good string "eabaab".
Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).
 

Constraints:

1 <= s.length <= 105
s contains only lowercase English letters.


#### Solutions

1. ##### greedy approach O(n)

- reference: https://leetcode-cn.com/problems/minimum-deletions-to-make-character-frequencies-unique/solution/tan-xin-on-suan-fa-by-arsenal-591/
- The main idea is to keep characters with higher counts unchanged and delete characters with lower counts when needed.

```cpp
class Solution {
public:
    int minDeletions(string s) {
        unordered_map<char, int> m;
        for (auto c : s) ++m[c];

        vector<int> counts;
        for (auto [c, n] : m)
            counts.push_back(n);
        
        sort(counts.rbegin(), counts.rend());
        unordered_set<int> seen;

        int del = 0;
        for (auto n : counts) {
            if (!seen.count(n))
                seen.insert(n);
            else {
                while (seen.count(n)) {
                    n--; del++;
                }
                if (n) seen.insert(n);
            }
        }

        return del;
    }
};
```


- since the count can only be decreased, the hashet is redundant.


```cpp
class Solution {
public:
    int minDeletions(string s) {
        vector<int> cnts(26);
        for (auto c : s)
            cnts[c - 'a']++;
        
        sort(cnts.rbegin(), cnts.rend());

        int del = 0, prev = INT_MAX;
        for (auto n : cnts) {
            if (!n) break;
            if (n >= prev) {
                del += min(n, n - (prev - 1));
                prev = prev - 1;
            }
            else
                prev = n;
        }

        return del;
    }
};
```