---
title: Minimum Deletions to Make String Balance
date: 2021-01-04
---
You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.

 

Example 1:

Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
Example 2:

Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.
 

Constraints:

1 <= s.length <= 105
s[i] is 'a' or 'b'​​.


#### Solutions

1. ##### dynamic programming

- `dp1` represents the minimum cost to keep the string balanced by deleting the `last a`.
- `dp0` represents the ........  by deleting all b before the `last a`.
- `num1` represents the remaining number of b in the first case.
- `num0` ...                                     the second case.

```cpp
class Solution {
public:
    int minimumDeletions(string s) {
        int dp1, dp0, num1, num0;
        dp1 = dp0 = num1 = num0 = 0;
        for (auto c : s) {
            if (c == 'b') {
                num1++; num0++;
            }
            else {
                if (dp1 + (num1 > 0) < dp0 + (num0 > 0))
                    dp1 += (num1 > 0);
                else {
                    dp1 = dp0 +(num0 > 0);
                    num1 = num0;
                }
                if (dp1 + num1 < dp0 + num0)
                    dp0 = dp1 + num1;
                else
                    dp0 = dp0 + num0;
                num0 = 0;
            }
        }

        return min(dp1, dp0);
    }
};

```