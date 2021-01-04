---
title: K Similar Strings
date: 2021-01-04
---
Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.

Given two anagrams A and B, return the smallest K for which A and B are K-similar.

Example 1:

Input: A = "ab", B = "ba"
Output: 1
Example 2:

Input: A = "abc", B = "bca"
Output: 2
Example 3:

Input: A = "abac", B = "baca"
Output: 2
Example 4:

Input: A = "aabc", B = "abca"
Output: 2
Note:

1 <= A.length == B.length <= 20
A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}

#### Solutions

1. ##### bfs

- reference: https://leetcode.com/problems/k-similar-strings/discuss/140099/JAVA-BFS-32-ms-cleanconciseexplanationwhatever
- In each bfs level, swap the first unequal character with characters after that could fix this inconsistency.

```cpp
class Solution {
public:
    int kSimilarity(string A, string B) {
        if (A == B) return 0;
        unordered_set<string> seen = {A};
        queue<string> q; q.push(A);

        int res = 0, n = B.size();
        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto cur = q.front(); q.pop();
                int i = 0;
                while (i < n && cur[i] == B[i]) i++;
                for (int j = i + 1; j < n; j++) {
                    if (cur[j] == B[j] || cur[i] != B[j]) continue;
                    auto next = cur;
                    swap(next[i], next[j]);
                    if (seen.insert(next).second) {
                        if (next == B) return res + 1;
                        q.push(next);
                    }
                }
            }
            res++;
        }
        return res;
    }
};
```