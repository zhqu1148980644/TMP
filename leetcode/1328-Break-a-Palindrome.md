Given a palindromic string palindrome, replace exactly one character by any lowercase English letter so that the string becomes the lexicographically smallest possible string that isn't a palindrome.

After doing so, return the final string.  If there is no way to do so, return the empty string.

 

```
Example 1:

Input: palindrome = "abccba"
Output: "aaccba"

Example 2:

Input: palindrome = "a"
Output: ""
```

 

#### Constraints:

    1 <= palindrome.length <= 1000
    palindrome consists of only lowercase English letters.


#### Solutions

1. ##### greedy

- For palindromes with length of `odd` numbers, the change of the middle character would not affect the existence of palindrome.
- Except for the middle character, there are two cases:
    - All characters are `a`, change the last `a` into `b` is the answer.
    - Else, change the first `non-a` character to `a` is the answer.

```c++
class Solution {
public:
    string breakPalindrome(string palindrome) {
        if (palindrome.size() <= 1) return "";
        for (int i = 0; i < palindrome.size() / 2; i++) {
            if (palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        palindrome.back() = 'b';
        return palindrome;
    }
};
```