---
title: Ransom Note
date: 2021-01-04
---
#### Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

#### Note:
You may assume that both strings contain only lowercase letters.

```
canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
```

#### Solutions

1. ##### straight forward

- O(n + m)

```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int counter[126] = {0};
        for (auto & c : magazine)
            counter[c]++;
        for (auto & c: ransomNote)
            if (--counter[c] < 0)
                return false;

        return true;
    }
};
```

- O(nm)

```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int pos[26] = {0};
        for (auto c : ransomNote) {
            auto find = magazine.find(c, pos[c - 'a']);
            if (find == string::npos)
                return false;
            pos[c - 'a'] = find + 1;
        }
        return true;
    }
};
```