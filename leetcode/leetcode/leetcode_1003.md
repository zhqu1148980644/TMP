---
title: Check If Word Is Valid After Substitutions
date: 2021-01-04
---
We are given that the string "abc" is valid.

From any valid string V, we may split V into two pieces X and Y such that X + Y (X concatenated with Y) is equal to V.  (X or Y may be empty.)  Then, X + "abc" + Y is also valid.

If for example S = "abc", then examples of valid strings are: "abc", "aabcbc", "abcabc", "abcabcababcc".  Examples of invalid strings are: "abccba", "ab", "cababc", "bac".

Return true if and only if the given string S is valid.

 

Example 1:

Input: "aabcbc"
Output: true
Explanation: 
We start with the valid string "abc".
Then we can insert another "abc" between "a" and "bc", resulting in "a" + "abc" + "bc" which is "aabcbc".
Example 2:

Input: "abcabcababcc"
Output: true
Explanation: 
"abcabcabc" is valid after consecutive insertings of "abc".
Then we can insert "abc" before the last letter, resulting in "abcabcab" + "abc" + "c" which is "abcabcababcc".
Example 3:

Input: "abccba"
Output: false
Example 4:

Input: "cababc"
Output: false
 

Note:

1 <= S.length <= 20000
S[i] is 'a', 'b', or 'c'

#### Solutions

- In summary, the root valid string is `abc`, we can build valid strings by iteratively inserting `abc` into valid strings. In a reverse view, when we iteratively revmoving `abc` in a valid string(when the substrin abs is removed, the two ends of `abc` will be adjacent now), the final string would be empty.

1. ##### stack

```cpp
class Solution {
public:
    bool isValid(string S) {
        string s;
        for (auto c : S) {
            if (c == 'c' && s.size() >= 2) {
                int len = s.size();
                if (s[len - 2] == 'a' && s[len - 1] == 'b') {
                    s.pop_back(); s.pop_back();
                    continue;
                }
            }
            s.push_back(c);
        }

        return s.size() == 0;
    }
};
```