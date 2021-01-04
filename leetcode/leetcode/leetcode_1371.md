---
title: Find the Longest Substring Containing Vowels in Even Counts
date: 2021-01-04
---
Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

 

```
Example 1:

Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
Example 2:

Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.
Example 3:

Input: s = "bcbcbc"
Output: 6
Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.
```
 

#### Constraints:

- 1 <= s.length <= 5 x 10^5
- s contains only lowercase English letters.


#### Solutions


1. ##### prefix xor sum O(n)

- reference: https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/solution/jian-dan-de-si-lu-by-mnizy/
- A naive strategy using ordinary prefix sum(counting) would leads to `O(n2)` time complexity.
    - However the counting of each elements are not necessarily needed, only the `odd/even` properties matters due to the fact that `odd - odd` and `even - even` are always even numbers. To record the maximum length, we record the first appearance of `odd count` and `even count`.    
- The occurrence of each vowel character has two states(odd or even). Thus there are 32(2^5) states in total when taking all 5 vowel chatacters into consideration.
    - Use a integer to represent a certain state. For example, the lowest bit is 1 represents `a` appeared odd times, the second lowest bit is 1 represents `e` appeared odd times......
- More specifically, we choose to record xor sums of each prefix, by using this representation, `s[i + 1: j]` is a valid substring when `prefix_state[i] == prefix_state[j]`. ie: even number of vowel characters were xored to 0 in this substring `s[i + 1: j]`.
    - `prefix_state[0] = -1` suits for cases when the prefix itself is a valid substring(i - -1 == i + 1 == len of prefix)
    - To record valid substring with the maximum length, use a hashtable to record the first appearence of each state.

```
                              i   k1    j    k2
                          c***e***e****e*****e
xor sum of e in prefix    0   2   0    2     0
valid substrings are:
    s[:k1]  s[:k2]
    s[i + 1: j]
```

```cpp
class Solution {
public:
    int findTheLongestSubstring(string s) {
        vector<int> cache(32, INT_MAX);
        cache[0] = -1;
        int state = 0, res = 0;
        for (int i = 0; i < s.size(); i++) {
            switch(s[i]) {
                case 'a' : state ^= 1; break;
                case 'e' : state ^= 2; break;
                case 'i' : state ^= 4; break;
                case 'o' : state ^= 8; break;
                case 'u' : state ^= 16; break;
                default : break;
            }
            if (cache[state] == INT_MAX)
                cache[state] = i;
            else
                res = max(res, i - cache[state]);
        }

        return res;
    }
};
```