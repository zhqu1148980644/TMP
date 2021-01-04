---
title: Find Common Characters
date: 2021-01-04
---
Given an array A of strings made only from lowercase letters, return a list of all characters that show up in all strings within the list (including duplicates).  For example, if a character occurs 3 times in all strings but not 4 times, you need to include that character three times in the final answer.

You may return the answer in any order.

 

Example 1:

Input: ["bella","label","roller"]
Output: ["e","l","l"]
Example 2:

Input: ["cool","lock","cook"]
Output: ["c","o"]
 

Note:

1 <= A.length <= 100
1 <= A[i].length <= 100
A[i][j] is a lowercase letter

#### Solutions

1. #### hashmap

```cpp
class Solution {
public:
    vector<string> commonChars(vector<string>& A) {
        vector<int> count(26, 100);
        for (auto & w : A) {
            vector<int> cur(26);
            for (auto c : w)
                cur[c - 'a']++;
            for (int i = 0; i < 26; i++)
                count[i] = min(count[i], cur[i]);
        }

        vector<string> res;
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < count[i]; j++)
                res.emplace_back(1, i + 'a');
        return res;
    }
};
```