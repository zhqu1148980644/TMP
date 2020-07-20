A message containing letters from A-Z is being encoded to numbers using the following mapping way:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers from 1 to 9.

Given the encoded message containing digits and the character '*', return the total number of ways to decode it.

Also, since the answer may be very large, you should return the output mod 109 + 7.

Example 1:
Input: "*"
Output: 9
Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".
Example 2:
Input: "1*"
Output: 9 + 9 = 18
Note:
The length of the input string will fit in range [1, 105].
The input string will only contain the character '*' and digits '0' - '9'.

##### Solutions

1. ##### dynamic programming

- `dp[i]` only depends on `dp[i - 1]` and `dp[i - 2]`

```c++
class Solution {
public:
    int numDecodings(string s) {
        int MOD = 1e9 + 7;
        long pprev = 1, prev =  s[0] == '*' ? 9 : (s[0] != '0' ? 1 : 0);

        for (int i = 1; i < s.size(); i++) {
            long tmp = prev;
            if (s[i] == '*') {
                // the current character represent a single letter
                prev *= 9;
                // coupled with the previous character
                if (s[i - 1] == '1')
                    prev += 9 * pprev;
                else if (s[i - 1] == '2')
                    prev += 6 * pprev;
                else if (s[i - 1] == '*')
                    prev += 15 * pprev;
            }
            else {
                // when the current character is 0, it can not be a single letter
                // if the current 0 can not be combined with the previous character, s is undecodable.
                prev = s[i] == '0' ? 0 : prev;
                if (s[i - 1] == '1')
                    prev += pprev;
                else if (s[i - 1] == '2' && s[i] <= '6')
                    prev += pprev;
                else if (s[i - 1] == '*')
                    prev += s[i] <= '6' ? 2 * pprev : pprev;
            }
            pprev = tmp;
            prev %= MOD;
        }

        return prev;
    }
};
```