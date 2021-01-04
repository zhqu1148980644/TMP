---
title: Keyboard Row
date: 2021-01-04
---
Given a List of words, return the words that can be typed using letters of alphabet on only one row's of American keyboard like the image below.

 



 
Example:

![](https://assets.leetcode.com/uploads/2018/10/12/keyboard.png)

Input: ["Hello", "Alaska", "Dad", "Peace"]
Output: ["Alaska", "Dad"]
 

Note:

You may use one character in the keyboard more than once.
You may assume the input string will only contain letters of alphabet.

#### Solutions

1. ##### hashset

```cpp
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> rows = {"ZXCVBNM", "ASDFGHJKL", "QWERTYUIOP"};
        vector<unordered_set<char>> m;
        for (auto & s : rows)
            m.emplace_back(s.begin(), s.end());
        using namespace std::placeholders;
        auto within = [](auto & dict, auto c) { return dict.count(toupper(c)); };
        vector<string> res;
        for (auto & w : words)
            for (auto & dict : m) {
                if (all_of(w.begin(), w.end(), bind(within, dict, _1))) {
                    res.push_back(w); break;
                }
            }
        
        return res;
    }
};
```