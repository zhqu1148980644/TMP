---
title: Uncommon Words from Two Sentences
date: 2021-01-04
---
We are given two sentences A and B.  (A sentence is a string of space separated words.  Each word consists only of lowercase letters.)

A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.

Return a list of all uncommon words. 

You may return the list in any order.

 

Example 1:

Input: A = "this apple is sweet", B = "this apple is sour"
Output: ["sweet","sour"]
Example 2:

Input: A = "apple apple", B = "banana"
Output: ["banana"]
 

Note:

0 <= A.length <= 200
0 <= B.length <= 200
A and B both contain only spaces and lowercase letters.

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    vector<string> uncommonFromSentences(string A, string B) {
        unordered_map<string, int> m;
        istringstream ss(A + " " + B);
        string word;
        while (ss >> word)
            m[word]++;
        vector<string> res;
        for (auto & [w, cnt] : m)
            if (cnt == 1)
                res.push_back(move(w));
        return res;
    }
};
```