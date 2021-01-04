---
title: Substring with Concatenation of All Words
date: 2021-01-04
---
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

 

```
Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.

Example 2:

Input:
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
Output: []
```


#### Solutions

1. ##### straight forward

- Check every substring with length of the concatenated words string.

```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (!s.size() || !words.size()) return {};
        vector<int> res;
        int ws = words[0].size(), wn = words.size(), num;
        if (s.size() < ws * wn) return res;

        unordered_map<string, int> m;
        for (auto & _s : words) m[_s]++;
        unordered_map<string, int> cm;
        int count;

        for (int i = 0; i <= s.size() - ws * wn; i++) {
            cm.clear(); count = 0;
            for (int j = 0; j < wn; j++) {
                auto word = s.substr(i + j * ws, ws);
                int expcount = m.count(word) ? m[word] : 0;
                if (++cm[word] > expcount) break;
                else count++;
            }
            if (count == wn) res.push_back(i);
        }
        return res;
    }
};
```


2. ##### sliding window

- Maintaining a sliding window with `valid` substring:
    - Length is smaller/equal than the total length of words in words vector.
    - Frequency of each word should be smaller/equal than the frequency of the word in words vector.
    - The substring contains only words in words vector.
- When the current valid substring is full length, add to result.
- When the current checking word is not valid, start a new window after this word with length 0.
- When the current checking word is appeared more than permitted, move the left bound of the window forward till this word is removed.


```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (!s.size() || !words.size()) return {};
        int ws = words[0].size(), wn = words.size();
        if (s.size() < ws * wn) return {};

        unordered_map<string, int> m;
        for (auto & w : words) m[w]++;
        vector<int> res;

        for (int st = 0; st < ws; st++) {
            int i = st, counter = 0;
            unordered_map<string, int> cm;
            for (int j = i; j <= s.size() - ws; j += ws) {
                auto word = s.substr(j, ws);
                if (m.count(word)) {
                    // Exceed the maximum number of appearance
                    // remove this word in the current valid string
                    if (++cm[word] > m[word])
                        while (cm[word] != m[word]) {
                            cm[s.substr(i, ws)]--;
                            counter--;
                            i += ws;
                        }
                    counter++;
                    // push into result vector
                    if (counter == wn) {
                        res.push_back(i);
                        cm[s.substr(i, ws)]--;
                        counter--;
                        i += ws;
                    }
                } else {
                    // invalid. start a new window with length 0.
                    i = j + ws;
                    cm.clear();
                    counter = 0;
                }
            }
        }

        return res;
    }
};
```