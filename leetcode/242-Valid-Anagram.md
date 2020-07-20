#### Given two strings s and t , write a function to determine if t is an anagram of s.

```
Example 1:

Input: s = "anagram", t = "nagaram"
Output: true

Example 2:

Input: s = "rat", t = "car"
Output: false
```

#### Note:
You may assume the string contains only lowercase alphabets.

#### Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

#### Solutions

- wiki: An anagram is a word or phrase formed by rearranging the letters of a different word or phrase.

1. ##### hash map

- For unicode characters, we can use a dynamic hash table.

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int count[26] = {0};
        for (auto & ch : s) count[ch - 'a']++;
        for (auto & ch : t) count[ch - 'a']--;
        for (auto c : count)
            if (c) return false;
        return true;
    }
};
```