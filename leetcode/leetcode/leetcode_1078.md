---
title: Occurrences After Bigra
date: 2021-01-04
---
Given words first and second, consider occurrences in some text of the form "first second third", where second comes immediately after first, and third comes immediately after second.

For each such occurrence, add "third" to the answer, and return the answer.

 

Example 1:

Input: text = "alice is a good girl she is a good student", first = "a", second = "good"
Output: ["girl","student"]
Example 2:

Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]
 

Note:

1 <= text.length <= 1000
text consists of space separated words, where each word consists of lowercase English letters.
1 <= first.length, second.length <= 10
first and second consist of lowercase English letters.

#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    string_view genword(string_view s, int & st) {
        auto find = s.find(' ', st);
        if (find == - 1)
            find = s.size();
        auto sv = s.substr(st, find - st);
        st += sv.size() + (find != s.size());
        return sv;
    }
    vector<string> findOcurrences(string text, string first, string second) {
        int st = 0;
        vector<string> res;
        string_view pprev, prev;
        while (st < text.size()) {
            string_view cur =genword(text, st);
            if (pprev == first && prev == second)
                res.push_back(string(cur));
            pprev = prev;
            prev = cur;
        }

        return res;
    }
};
```

or

```cpp
class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string> ws;
        istringstream ss(text);
        string w;
        while ((ss >> w)) ws.push_back(w);

        vector<string> res;
        for (int i = 0; i <= (int)ws.size() - 3; i++)
            if (ws[i] == first && ws[i + 1] == second)
                res.push_back(ws[i + 2]);
        
        return res;
    }
};
```