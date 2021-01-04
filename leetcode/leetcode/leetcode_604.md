---
title: Design Compressed String Iterator
date: 2021-01-04
---
Design and implement a data structure for a compressed string iterator. The given compressed string will be in the form of each letter followed by a positive integer representing the number of this letter existing in the original uncompressed string.

Implement the StringIterator class:

next() Returns the next character if the original string still has uncompressed characters, otherwise returns a white space.
hasNext() Returns true if there is any letter needs to be uncompressed in the original string, otherwise returns false.
 

Example 1:

Input
["StringIterator", "next", "next", "next", "next", "next", "next", "hasNext", "next", "hasNext"]
[["L1e2t1C1o1d1e1"], [], [], [], [], [], [], [], [], []]
Output
[null, "L", "e", "e", "t", "C", "o", true, "d", true]

Explanation
StringIterator stringIterator = new StringIterator("L1e2t1C1o1d1e1");
stringIterator.next(); // return "L"
stringIterator.next(); // return "e"
stringIterator.next(); // return "e"
stringIterator.next(); // return "t"
stringIterator.next(); // return "C"
stringIterator.next(); // return "o"
stringIterator.hasNext(); // return True
stringIterator.next(); // return "d"
stringIterator.hasNext(); // return True
 

Constraints:

1 <= compressedString.length <= 1000
compressedString consists of lower-case an upper-case English letters and digits.
The number of a single character repetitions in compressedString is in the range [1, 10^9]
At most 100 calls will be made to next and hasNext.

#### Solutions

1. ##### preprocessing

```cpp
class StringIterator {
public:
    vector<pair<char, int>> chars;
    decltype(chars)::iterator cur;
    StringIterator(string compressedString) {
        int i = 0, n = compressedString.size();
        while (i < n) {
            auto c = compressedString[i++];
            int num = 0;
            while (isdigit(compressedString[i]))
                num = num * 10 + (compressedString[i++] - '0');
            chars.emplace_back(c, num);
        }
        cur = chars.begin();
    }
    
    char next() {
        if (!hasNext()) return ' ';
        auto c = cur->first;
        if (--cur->second == 0)
            ++cur;
        return c;
    }
    
    bool hasNext() {
        return cur != chars.end();
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```


2. ##### online version

```cpp
class StringIterator {
public:
    char c = ' ';
    int num = 0, cur = 0;
    string s;
    StringIterator(string compressedString) : s(compressedString) {

    }
    
    char next() {
        if (!hasNext())
            return ' ';
        else {
            if (num <= 0) {
                c = s[cur++];
                while (cur < s.size() && isdigit(s[cur]))
                    num = num * 10 + (s[cur++] - '0');
            }
            num--;
            return c;
        }
    }
    
    bool hasNext() {
        return cur < s.size() || num > 0;
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```