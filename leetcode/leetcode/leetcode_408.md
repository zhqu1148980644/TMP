---
title: Valid Word Abbreviation
date: 2021-01-04
---
Given a non-empty string s and an abbreviation abbr, return whether the string matches with the given abbreviation.

A string such as "word" contains only the following valid abbreviations:

["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
Notice that only the above abbreviations are valid abbreviations of the string "word". Any other string is not a valid abbreviation of "word".

Note:
Assume s contains only lowercase letters and abbr contains only lowercase letters and digits.

Example 1:
Given s = "internationalization", abbr = "i12iz4n":

Return true.
Example 2:
Given s = "apple", abbr = "a2e":

Return false.


#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        abbr.push_back(' ');
        int st = 0;
        for (int i = 0, num = 0; i < abbr.size(); i++) {
            if (!isdigit(abbr[i])) {
                if (num > 0)
                    st += num;
                if (abbr[i] == ' ')
                    return st == word.size();
                else if (!(st < word.size() && abbr[i] == word[st++]))
                    return false;
                num = 0;
            }
            else {
                if (!num && abbr[i] == '0') return false;
                num = num * 10 + (abbr[i] - '0');
            }
        }
        return true;
    }
};
```

or

```cpp
class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        abbr.push_back(' ');
        word.push_back(' ');
        int st = 0;
        for (int i = 0, num = 0; i < abbr.size(); i++) {
            if (!isdigit(abbr[i])) {
                if (num > 0)
                    st += num;
                if (!(st < word.size() && abbr[i] == word[st++]))
                    return false;
                num = 0;
            }
            else {
                if (!num && abbr[i] == '0') return false;
                num = num * 10 + (abbr[i] - '0');
            }
        }
        return true;
    }
};
```