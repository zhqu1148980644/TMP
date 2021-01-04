---
title: To Lower Case
date: 2021-01-04
---
Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.

 

Example 1:

Input: "Hello"
Output: "hello"
Example 2:

Input: "here"
Output: "here"
Example 3:

Input: "LOVELY"
Output: "lovely"

#### Solutions

```cpp
class Solution {
public:
    string toLowerCase(string str) {
        for (auto & c : str)
            c = tolower(c);
        return str;
    }
};
```