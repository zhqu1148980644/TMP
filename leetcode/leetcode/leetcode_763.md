---
title: Partition Labels
date: 2021-01-04
---
A string S of lowercase English letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

 

Example 1:

Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
 

Note:

S will have length in range [1, 500].
S will consist of lowercase English letters ('a' to 'z') only.

#### Soltuions

1. ##### hash map

```cpp
class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<int> last(26);
        for (int i = 0; i < S.size(); i++)
            last[S[i] - 'a'] = i;

        vector<int> res;
        int prev = 0, end = INT_MIN;
        for (int i = 0; i < S.size(); i++) {
            end = max(last[S[i] - 'a'], end);
            if (end == i) {
                res.push_back(i - prev + 1);
                prev = i + 1;
            }
        }
        return res;
    }
};
```