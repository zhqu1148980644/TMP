---
title: Group Shifted Strings
date: 2021-01-04
---
Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of non-empty strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

Example:

Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Output: 
[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]

#### Solutions

1. ##### hash map

```cpp
class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> m;
        for (int i = 0; i < strings.size(); i++) {
            string key = "*";
            for (int j = 1; j < strings[i].size(); j++)
            // For az->ba,  z - a should be equal to a - b
                key.push_back((strings[i][j] - strings[i][j - 1] + 26) % 26 + 'a');
            m[key].push_back(strings[i]);
        }

        vector<vector<string>> res;
        for (auto & [k, v] : m)
            res.emplace_back(move(v));
        
        return res;
    }
};
```