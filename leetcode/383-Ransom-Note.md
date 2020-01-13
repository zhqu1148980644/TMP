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

```c++
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