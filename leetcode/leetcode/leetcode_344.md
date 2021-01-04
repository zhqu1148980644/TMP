---
title: Reverse String
date: 2021-01-04
---
#### Write a function that reverses a string. The input string is given as an array of characters char[].

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

You may assume all the characters consist of printable ascii characters.

 

```
Example 1:

Input: ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
Example 2:

Input: ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
```

#### Solutions

1. #####  Straight forward

```cpp
void reverseString(char* s, int sSize){
    int i = 0;
    sSize--;
    if (sSize < 1) return;
    while (i < sSize) {
        char tmp = s[i];
        s[i++] = s[sSize];
        s[sSize--] = tmp;
    }
}
```

```cpp
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, len = s.size();
        if (--len < 1) return;
        while (i < len)
            swap(s[i++], s[len--]);
    }
};
```