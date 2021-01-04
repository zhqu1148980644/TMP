---
title: Bold Words in String
date: 2021-01-04
---
Given a set of keywords words and a string S, make all appearances of all keywords in S bold. Any letters between <b> and </b> tags become bold.

The returned string should use the least number of tags possible, and of course the tags should form a valid combination.

For example, given that words = ["ab", "bc"] and S = "aabcd", we should return "a<b>abc</b>d". Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.

#### Note:

-    words has length in range [0, 50].
-    words[i] has length in range [1, 10].
-    S has length in range [0, 500].
-    All characters in words[i] and S are lowercase letters.


#### Solutions

1. ##### hash map O(n*(toal len of words))

```cpp
class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        unordered_set<string> seen(words.begin(), words.end());
        int n = S.size();

        vector<bool> isbold(n);
        auto begin = isbold.begin();
        for (auto & word : seen) {
            int st = 0, wsize = word.size();
            while ((st = S.find(word, st)) != string::npos) {
                fill(begin + st, begin + st + wsize, true);
                st++;
            }
        }

        string res;
        int i = 0;
        while (i < n) {
            if (!isbold[i])
                res += S[i++];
            else {
                res += "<b>";
                while (i < n && isbold[i])
                    res += S[i++];
                res += "</b>";
            }
        }

        return res;
    }
};
```

2. ##### trie O(max(len(word)) * n)

```cpp
struct Trie {
    vector<Trie *> links {26};
    int len = 0;
    Trie * insert(const string & s) {
        Trie * root = this;
        for (auto c : s) {
            if (!root->links[c - 'a'])
                root->links[c - 'a'] = new Trie;
            root = root->links[c - 'a'];
        }
        root->len = s.size();
        return root;
    }
    int search(const string & s, int st) {
        Trie * root = this, * match = nullptr;
        while (st < s.size()) {
            if (!(root = root->links[s[st] - 'a']))
                break;
            if (root->len) match = root;
            st++;
        }
        return match ? match->len : 0;
    }
};
class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        Trie root;
        for (auto & w : words)
            root.insert(w);

        int n = S.size();
        vector<int> isbold(n);
        auto begin = isbold.begin();
        int i = 0, j = 0;
        while (i < n) {
            int matchlen = root.search(S, i);
            if (matchlen && i + matchlen > j) {
                fill(begin + j, begin + i + matchlen, true);
                j = i + matchlen;
            }
            i++; j = max(i, j);
        }

        string res;
        i = 0;
        while (i < n) {
            if (!isbold[i])
                res += S[i++];
            else {
                res += "<b>";
                while (i < isbold.size() && isbold[i])
                    res += S[i++];
                res += "</b>";
            }
        }

        return res;
    }
};
```