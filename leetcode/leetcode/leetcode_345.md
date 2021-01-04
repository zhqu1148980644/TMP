---
title: Reverse Vowels of a String
date: 2021-01-04
---
#### Write a function that takes a string as input and reverse only the vowels of a string.

```
Example 1:

Input: "hello"
Output: "holle"


Example 2:

Input: "leetcode"
Output: "leotcede"
```

#### Note:
The vowels does not include the letter "y".


#### Solutions

```cpp
class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u', 
                                      'A', 'E', 'I', 'O', 'U'};
        int i = 0, j = s.size() - 1;
        while (i < j) {
            if (!vowels.count(s[i]))  {
                i++; continue;
            }
            if (!vowels.count(s[j])) {
                j--; continue;
            }
            swap(s[i++], s[j--]);
        }

        return s;
    }
};
```