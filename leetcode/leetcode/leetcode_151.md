---
title: Reverse Words in a String
date: 2021-01-04
---
#### Given an input string, reverse the string word by word.

 

```
Example 1:

Input: "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: "  hello world!  "
Output: "world! hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.
```
 

#### Note:

- A word is defined as a sequence of non-space characters.
- Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
- You need to reduce multiple spaces between two words to a single space in the reversed string.
 

#### Follow up:

For C programmers, try to solve it in-place in O(1) extra space.


#### Solutions

1. ##### straight forward

- borrowed from others
- First reverse the sting.
- Loop through the target string and put each character at the first avaibale position and reverse the pisitioned world when ever meet an empty space.
- There are two different situations when ending the loop:
    - when the last character of the reverse string is not a space, the last world need to be reversed as it has no chance to be reversed within the for loop.
    - otherwise the `end` pointer has been moved one step further. We need to move one step back an set this position as `\0`.
        - Moving back one step happens only when we met at leat one word before. ie. when the input string contains only space, `0 - 1` will be invalid.

```cpp
void reverse(char * st, char * ed) {
    while (st < ed) {
        char tmp = *st;
        *st++ = *--ed;
        *ed = tmp;
    }
}

char * reverseWords(char * s){
    int len = strlen(s); if (!len) return s;
    reverse(s, s + len);
    int start = 0, end = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] != ' ')
            s[end++] = s[i];
        else if (i && s[i - 1] != ' ') {
            reverse(s + start, s + end);
            s[end++] = ' ';
            start = end;
        }
    }
    // when the last character is not a space, reverse the last word.
    reverse(s + start, s + end);
    // otherwise move end one step back.
    if (s[len - 1] == ' ' && start) end--;
    // mark end as end of string.
    s[end] = '\0';
    return s;
}
```

Not-inplace version.

```python
class Solution:
    def reverseWords(self, s: str) -> str:
        return " ".join(s.split()[::-1])
```