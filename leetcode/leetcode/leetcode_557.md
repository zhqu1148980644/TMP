---
title:  Reverse Words in a String III
date: 2021-01-04
---
#### Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

```
Example 1:

Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
```
#### Note: In the string, each word is separated by single space and there will not be any extra space in the string. 


#### Solutions

1. ##### straight forward

- Inplace C version.

```cpp
char * reverseWords(char * s){
    char * res = s, * pre = s;
    while (*s) {
        if (*s == ' ' || !*(s + 1)) {
            char * cur = *s == ' ' ? s - 1 : s;
            while (pre < cur) {
                char back = *pre;
                *pre++ = *cur;
                *cur-- = back;
            }
            pre = s + 1;
        }
        s++;
    }

    return res;
}
```

- C++ version

```cpp
class Solution {
public:
    string reverseWords(string s) {
        s.push_back(' ');
        auto it = s.begin(), begin = s.begin();
        while (it != s.end()) {
            if (*it == ' ') {
                reverse(begin, it);
                begin = it + 1;
            }
            it++;
        }
        s.pop_back();
        return s;
    }
};
```


- Or malloc a new string.

```cpp
char * reverseWords(char * s){
    int len = strlen(s);
    char * res, * pre;
    res = pre = (char *) malloc(sizeof(char) * (len + 1));
    res[len] = '\0';
    len = 0;
    while (*s) {
        if (*s != ' ')
            len++;
        if (*s == ' ' || !*(s + 1)) {
            char * cur = *s == ' ' ? s - 1 : s;
            char * end = pre + len;
            while (pre != end)
                *pre++ = *cur--;
            if (*s == ' ')
                *pre++ = ' ';
            len = 0;
        }
        s++;
    }
    return res;
}
```