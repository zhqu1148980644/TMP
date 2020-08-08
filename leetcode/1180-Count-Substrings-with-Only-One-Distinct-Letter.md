Given a string S, return the number of substrings that have only one distinct letter.

 

Example 1:

Input: S = "aaaba"
Output: 8
Explanation: The substrings with one distinct letter are "aaa", "aa", "a", "b".
"aaa" occurs 1 time.
"aa" occurs 2 times.
"a" occurs 4 times.
"b" occurs 1 time.
So the answer is 1 + 2 + 4 + 1 = 8.
Example 2:

Input: S = "aaaaaaaaaa"
Output: 55
 

Constraints:

1 <= S.length <= 1000
S[i] consists of only lowercase English letters.

#### Solutions

1. ##### sliding window

```c++
class Solution {
public:
    int countLetters(string S) {
        int i = 0, j = 0, len = 0, res = 0;
        for (int i = 0, j = 0; j < S.size(); j++) {
            if (S[j] != S[i]) {
                i = j; len = 0;
            }
            res += ++len;
        }

        return res;
    }
};
```