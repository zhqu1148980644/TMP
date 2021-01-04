---
title: Unique Word Abbreviation
date: 2021-01-04
---

An abbreviation of a word follows the form `<first letter><number><last letter>`. Below are some examples of word abbreviations:

```
a) it                      --> it    (no abbreviation)

     1
     ↓
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
     ↓   ↓    ↓    ↓  ↓    
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
     ↓   ↓    ↓
d) l|ocalizatio|n          --> l10n
```


Additionally for any string s of size less than or equal to 2 their abbreviation is the same string s.
Find whether its abbreviation is unique in the dictionary. A word's abbreviation is called unique if any of the following conditions is met:

There is no word in dictionary such that their abbreviation is equal to the abbreviation of word.
Else, for all words in dictionary such that their abbreviation is equal to the abbreviation of word those words are equal to word.
 

Example 1:

Input
["ValidWordAbbr", "isUnique", "isUnique", "isUnique", "isUnique"]
[[["deer", "door", "cake", "card"]], ["dear"], ["cart"], ["cane"], ["make"]]
Output
[null, false, true, false, true]

Explanation
ValidWordAbbr validWordAbbr = new ValidWordAbbr(["deer", "door", "cake", "card"]);
validWordAbbr.isUnique("dear"); // return False
validWordAbbr.isUnique("cart"); // return True
validWordAbbr.isUnique("cane"); // return False
validWordAbbr.isUnique("make"); // return True
 

Constraints:

Each word will only consist of lowercase English characters.

#### Solutions

1. ##### hash map

```cpp
class ValidWordAbbr {
public:
    unordered_map<string, unordered_set<string>> m;

    string abbrev(const string & w) {
        return w.size() <= 2 ? w : string(1, w[0]) + to_string(w.size() - 2) + w.back();
    }

    ValidWordAbbr(vector<string>& dictionary) {
        for (auto & w : dictionary) {
            // reduce space cost
            auto & ws = m[abbrev(w)];
            if (ws.size() < 2)
                ws.insert(w);
        }
    }
    // Two cases to be unique
    bool isUnique(string word) {
        auto abv = abbrev(word);
        return !m.count(abv) || (m[abv].size() == 1 && m[abv].count(word));
    }
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
```


Another solution is to use a boolean tag to record if an abbreviation has two different source words. 