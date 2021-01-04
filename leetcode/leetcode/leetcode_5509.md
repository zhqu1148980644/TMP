---
title: Minimum Deletion Cost to Avoid Repeating Letters
date: 2021-01-04
---
Given a string s and an array of integers cost where cost[i] is the cost of deleting the character i in s.

Return the minimum cost of deletions such that there are no two identical letters next to each other.

Notice that you will delete the chosen characters at the same time, in other words, after deleting a character, the costs of deleting other characters will not change.

 

Example 1:

Input: s = "abaac", cost = [1,2,3,4,5]
Output: 3
Explanation: Delete the letter "a" with cost 3 to get "abac" (String without two identical letters next to each other).
Example 2:

Input: s = "abc", cost = [1,2,3]
Output: 0
Explanation: You don't need to delete any character because there are no identical letters next to each other.
Example 3:

Input: s = "aabaa", cost = [1,2,3,4,1]
Output: 2
Explanation: Delete the first and the last character, getting the string ("aba").
 

Constraints:

s.length == cost.length
1 <= s.length, cost.length <= 10^5
1 <= cost[i] <= 10^4
s contains only lowercase English letters.


#### Solutions

1. ##### greedy approach

- For each continuous region, delete characters except for the one with the maximum cost.

```cpp
class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        s += '_';
        int res = 0, i = 0;
        for (int j = 1; j < s.size(); j++) {
            if (s[j] != s[j - 1]) {
                if (j - i > 1) {
                    int sum = 0, maxc = 0, len = j - i;
                    for (int r = i; r < i + len; r++) {
                        sum += cost[r]; maxc = max(maxc, cost[r]);
                    }
                    res += sum - maxc;
                }
                i = j;
            }
        }

        return res;
    }
};
```