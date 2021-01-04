---
title: Longest Happy String
date: 2021-01-04
---
A string is called happy if it does not have any of the strings 'aaa', 'bbb' or 'ccc' as a substring.

Given three integers a, b and c, return any string s, which satisfies following conditions:

s is happy and longest possible.
s contains at most a occurrences of the letter 'a', at most b occurrences of the letter 'b' and at most c occurrences of the letter 'c'.
s will only contain 'a', 'b' and 'c' letters.
If there is no such string s return the empty string "".

 

```
Example 1:

Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.
Example 2:

Input: a = 2, b = 2, c = 1
Output: "aabbc"
Example 3:

Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It's the only correct answer in this case.
```
 

Constraints:

0 <= a, b, c <= 100
a + b + c > 0

#### Solutions

1. ##### greedy approach

- To fetch the longest string satisfying all constraints, the most ideal string should be looked like this: `aabaabccb` ie: char pairs(limit = 2) separated by single char.
- reference: https://leetcode-cn.com/problems/longest-happy-string/solution/c-zhong-gui-zhong-ju-de-4msjie-fa-ji-shu-by-gary-2/

```cpp
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        int limit = 2;
        vector<pair<int, char>> v = {{a, 'a'}, {b, 'b'}, {c, 'c'}};

        string res;
        int n = a + b + c;
        while (res.size() < n) {
            sort(v.rbegin(), v.rend());
            if (res.empty() || res.back() != v[0].second) {
                for (int i = 0; i < limit; i++)
                    if (v[0].first-- > 0)
                        res += v[0].second;
            }
            else if (v[1].first-- > 0)
                res += v[1].second;
            else break;
        }
        
        return res;
    }
};
```