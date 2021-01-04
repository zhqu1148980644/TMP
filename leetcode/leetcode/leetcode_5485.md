---
title: Find Longest Awesome Substring
date: 2021-01-04
---
Given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it palindrome.

Return the length of the maximum length awesome substring of s.

 

Example 1:

Input: s = "3242415"
Output: 5
Explanation: "24241" is the longest awesome substring, we can form the palindrome "24142" with some swaps.
Example 2:

Input: s = "12345678"
Output: 1
Example 3:

Input: s = "213123"
Output: 6
Explanation: "213123" is the longest awesome substring, we can form the palindrome "231132" with some swaps.
Example 4:

Input: s = "00"
Output: 2
 

Constraints:

1 <= s.length <= 10^5
s consists only of digits.

#### Solutions

1. ##### prefix sum

- The same strategy as in `problem 1371`, check for details.
- Two cases:
    - all digits within has even counts;
    - except for digits with even counts, permit a single digit with odd count(put at the center of palindrome). 

```cpp
class Solution {
public:
    int longestAwesome(string s) {
        unordered_map<int, int> pos; pos[0] = -1;
        int state = 0, res = 0;
        for (int i = 0; i < s.size(); i++) {
            int d = s[i] - '0';
            state ^= (1 << d);
            // count the first appearance of each state
            if (!pos.count(state))
                pos[state] = i;
            else
                res = max(res, i - pos[state]);
            // check for the second case
            for (int d = 0; d <= 9; d++) {
                int tmp = state ^ (1 << d);
                if (pos.count(tmp))
                    res = max(res, i - pos[tmp]);
            }
        }
        
        return res;
    }
};
```