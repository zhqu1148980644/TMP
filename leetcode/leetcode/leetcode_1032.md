---
title: Stream of Characters
date: 2021-01-04
---
Implement the StreamChecker class as follows:

StreamChecker(words): Constructor, init the data structure with the given words.
query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.
 

Example:

StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
streamChecker.query('a');          // return false
streamChecker.query('b');          // return false
streamChecker.query('c');          // return false
streamChecker.query('d');          // return true, because 'cd' is in the wordlist
streamChecker.query('e');          // return false
streamChecker.query('f');          // return true, because 'f' is in the wordlist
streamChecker.query('g');          // return false
streamChecker.query('h');          // return false
streamChecker.query('i');          // return false
streamChecker.query('j');          // return false
streamChecker.query('k');          // return false
streamChecker.query('l');          // return true, because 'kl' is in the wordlist
 

Note:

1 <= words.length <= 2000
1 <= words[i].length <= 2000
Words will only consist of lowercase English letters.
Queries will only consist of lowercase English letters.
The number of queries is at most 40000.

#### Solutions

1. ##### trie

- reference: https://leetcode-cn.com/problems/stream-of-characters/solution/hen-jian-dan-de-qian-zhui-shu-ban-zi-by-xiaoneng/

```cpp
struct Trie {
    Trie * links[26] = {nullptr};
    bool isend = false;
    template <typename It>
    Trie * insert(It begin, It end) {
        Trie * root = this;
        while (begin != end) {
            auto c =  *begin - 'a';
            if (!root->links[c])
                root->links[c] = new Trie;
            root = root->links[c];
            begin++;
        }
        root->isend = true;
        return root;
    }
    template <typename It>
    Trie * find(It begin, It end) {
        Trie * root = this;
        while (begin != end) {
            int c = *begin - 'a';
            if (!root->links[c]) return nullptr;
            root = root->links[c];
            if (root->isend) return root;
            ++begin;
        }
        return nullptr;
    }
};
class StreamChecker {
public: 
    Trie root;
    string cur;
    StreamChecker(vector<string>& words) {
        for (auto & w : words)
            root.insert(w.rbegin(), w.rend());
    }
    
    bool query(char letter) {
        cur += letter;
        return root.find(cur.rbegin(), cur.rend());
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
```



2. ##### Aho–Corasick