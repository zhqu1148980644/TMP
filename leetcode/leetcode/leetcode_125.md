---
title: Valid Palindrome
date: 2021-01-04
---
#### Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

#### Note: 
For the purpose of this problem, we define empty string as valid palindrome.

```
Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false
```

#### Solutions

1. ##### Straight forward

- Skip the undesirable characters when checking palindrome string in normal way(Two pointers).

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            if (!isalnum(s[i]))
                i++;
            else if (!isalnum(s[j]))
                j--;
            else {
                if (!(tolower(s[i]) == tolower(s[j])))
                    return false;
                else {
                    i++; j--;
                }
            }
        }
        return true;
    }
};
```
