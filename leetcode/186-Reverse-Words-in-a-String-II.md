Given an input string , reverse the string word by word. 

Example:

Input:  ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
Note: 

A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces.
The words are always separated by a single space.
Follow up: Could you do it in-place without allocating extra space?

#### Solutions

1. ##### straight forward

- check problem 151

```c++
class Solution {
public:
    void reverseWords(vector<char>& s) {
        reverse(s.begin(), s.end());
        int len = s.size();
        int start = 0, end = 0;
        for (int i = 0; i < len; i++) {
            if (s[i] != ' ')
                s[end++] = s[i];
            else if (i && s[i - 1] != ' ') {
                reverse(s.begin() + start, s.begin() + end);
                s[end++] = ' ';
                start = end;
            }
        }
        reverse(s.begin() + start, s.begin() + end);
        // no trailing spaces
    }
};
```