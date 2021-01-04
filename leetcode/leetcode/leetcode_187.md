---
title: Repeated DNA Sequences
date: 2021-01-04
---
#### All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

```
Example:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"

Output: ["AAAAACCCCC", "CCCCCAAAAA"]
```

#### Solutions

1. ##### hash map

```cpp
 straight forward with hash map.
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if (s.size() < 10) return vector<string>();
        unordered_map<string, int> m;
        vector<string> res;
        for (int i = 0; i < s.size() - 9; i++) {
            string substr = s.substr(i, 10);
            m[substr]++;
            if (m[substr] == 2) res.push_back(substr);
        }
        return res;
    }
};
```

2. ##### hash map with bit representation

- Since there are only `4` possible characters in string, `20`(2 bit per char) bits is the smallest number of bits that can represent a unique `10-char` substring.
- A 32 bits `integer` is enough.
- When sliding the string, bits representation of the next substring can be quickly calculated by `shifting` the integer of the current substring.
- To faciliate the integer-subtring conversion, use `3 bits` representation(`char & 7`) instead.
    - `A = 0b1000001, B = 0b000010, C = 0b1000011, D = 0b1000100`
```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, unsigned int> m;
        vector<string> res;
        unsigned int hash = 0;
        for (int i = 0; i < s.size(); i++)
        // hash & 0x3fffffff to make sure the first two bits are always 0.
            if (m[hash = hash << 3 & 0x3FFFFFFF | s[i] & 7]++ == 1)
                res.push_back(s.substr(i - 9, 10));
        return res;
    }  
};
```

Or replace the `int` value type to `bool`.

```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, bool> m;
        vector<string> res;
        unsigned int hash = 0;
        for  (int i = 0; i < s.size(); i++) {
            hash = hash << 3 & 0x3FFFFFFF | s[i] & 7;
            if (m.find(hash) != m.end())
                if (m[hash]) {
                    m[hash] = false;
                    res.push_back(s.substr(i - 9, 10));
                }
            else
                m[hash] = true;
        }
        return res;
    }  
};
```

3. ##### rolling hash


