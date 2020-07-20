#### Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

```
Example 1:

Input: "aba"
Output: True

Example 2:

Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
```

#### Note:

    The string will only contain lowercase characters a-z. The maximum length of the string is 50000.

#### Solutions

1. ##### two pointers

- Find the first pair of characters that are unequal and separately check if the remaining characters are palindrome after deleted one of them.

```c++
class Solution {
public:
    bool isPalin(const string & s, int i, int j, bool check) {
        while (i < j && s[i] == s[j]) {
            i++; j--;
        }
        if (s[i] != s[j] && check)
            return isPalin(s, i, j - 1, false) || isPalin(s, i + 1, j, false);
        else
            return s[i] == s[j];
    }
    bool validPalindrome(string s) {
        return isPalin(s, 0, s.size() - 1, true);
    }
};
```

or iterative version

```c++
class Solution {
public:
    bool valid(string & s, int & i, int & j) {
        while (i < j && s[i] == s[j]) {
            i++; j--;
        }
        return i >= j;
    }
    bool validPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        if (valid(s, i, j)) return true;
        int x1 = i + 1, y1 = j, x2 = i, y2 = j - 1;

        return valid(s, x1, y1) || valid(s, x2, y2);
    }
};
```