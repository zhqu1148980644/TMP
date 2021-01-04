---
title: Short Encoding of Words
date: 2021-01-04
---
Given a list of words, we may encode it by writing a reference string S and a list of indexes A.

For example, if the list of words is ["time", "me", "bell"], we can write it as S = "time#bell#" and indexes = [0, 2, 5].

Then for each index, we will recover the word by reading from the reference string from that index until we reach a "#" character.

What is the length of the shortest reference string S possible that encodes the given words?

```
Example:

Input: words = ["time", "me", "bell"]
Output: 10
Explanation: S = "time#bell#" and indexes = [0, 2, 5].
```

 

#### Note:

-    1 <= words.length <= 2000.
-    1 <= words[i].length <= 7.
-    Each word has only lowercase letters.


#### Solutions

- The order of words in encoded string is not necessarily the same as the original list.

1. ##### straight forward O(n2) S(nw)


- As long as a string is suffix of other string, this substring can be represented by the longer string.


```cpp
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        unordered_set<string> dict(words.begin(), words.end());
        for (auto & w : words)
            for (int i = 1 ; i < w.size(); i++)
                if (dict.count(w.substr(i)))
                    dict.erase(w.substr(i));
        
        int res = 0;
        for (auto & w : dict)
            res += w.size() + 1;

        return res;
    }
};
```

2. ##### reverse and sort o(nlog(n)) S(1)

- Firtly reverse all
- After we sorted words by lexicographical order, strings with same(similar) suffix will be putted together.

```cpp
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        for (auto & w : words)
            reverse(w.begin(), w.end());
        sort(words.begin(), words.end());

        int res = 0;
        for (int i = 0; i < words.size() - 1; i++) {
            if (words[i].size() > words[i + 1].size()) {
                res += words[i].size() + 1;
                continue;
            }
            for (int j = 0; j < words[i].size(); j++)
                if (words[i][j] != words[i + 1][j]) {
                    res += words[i].size() + 1;
                    break;
                }
        }
        res += words[words.size() - 1].size() + 1;

        return res;
    }
};
```

3. ##### suffix trie O(nw)

```cpp
class Solution {
public:
    struct TrieNode {
        int size = 0;
        bool isend = true;
        TrieNode * links[26] = {nullptr};
        TrieNode(int s) : size(s) {}
        TrieNode * get(char c) {
            if (!links[c - 'a']) {
                links[c - 'a'] = new TrieNode(size + 1);
                isend = false;
            }
            return links[c - 'a'];
        }
    };

    int minimumLengthEncoding(vector<string>& words) {
        for (auto & w : words)
            reverse(w.begin(), w.end());

        TrieNode * root = new TrieNode(0);
        unordered_set<TrieNode *> ends;
        for (auto & w : words) {
            TrieNode * cur = root;
            for (auto & c : w)
                cur = cur->get(c);
            ends.insert(cur);
        }

        int res = 0;
        for (auto & pend : ends)
            if (pend->isend)
                res += pend->size + 1;

        return res;
    }
};
```

or

```cpp
struct Trie {
    Trie * links[26] = {nullptr};
    const string * ps = nullptr;
    Trie(const string * ps = nullptr) : ps(ps) {}
    Trie * insert(const string & w) {
        Trie * root = this;
        for (auto c : w) {
            if (!root->links[c - 'a'])
                root->links[c - 'a'] = new Trie(&w);
            root->ps = nullptr;
            root = root->links[c - 'a'];
        }
        return root;
    }
};
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        for (auto & w : words)
            reverse(w.begin(), w.end());
        Trie root;
        unordered_set<Trie *> ends;
        for (auto & w : words)
            ends.insert(root.insert(w));
        
        int res = 0;
        for (auto pend : ends)
            if (pend->ps)
                res += pend->ps->size() + 1;
        
        return res;
    }
};
```