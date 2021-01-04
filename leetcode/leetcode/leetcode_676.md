---
title: Implement Magic Dictionary
date: 2021-01-04
---
Implement a magic directory with buildDict, and search methods.

For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.

For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word, the modified word is in the dictionary you just built.

Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
Note:
You may assume that all the inputs are consist of lowercase letters a-z.
For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases. Please see here for more details.

#### Solutions

- Note: The target string `must replace` exactly one character(no less and no greater), and the search return true if this changed string is within the dictionary.

1. ##### preprocessing the dictionary

- For each word in the dictionary, generate a set of strings that could be converted to this word with a single character replacement.

```cpp
class MagicDictionary {
public:
    /** Initialize your data structure here. */
    unordered_map<string, int> m;
    unordered_set<string> words;
    MagicDictionary() {

    }
    
    vector<string> geneibors(string & s) {
        vector<string> res;
        for (int i = 0; i < s.size(); i++) {
            char back = s[i];
            s[i] = '*'; res.push_back(s); s[i] = back;
        }
        return res;
    }
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        words = unordered_set<string>(dict.begin(), dict.end());
        for (auto & s : dict)
            for (auto const & ns : geneibors(s))
                m[move(ns)]++;
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        for (auto const & s : geneibors(word))
            if (m.count(s) && (m[s] > 1 || !words.count(word)))
                return true;
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dict);
 * bool param_2 = obj->search(word);
 */
```


2. ##### trie permit a single mismatch

```cpp
struct TrieNode {
    TrieNode * links[26] = {nullptr};
    bool end = false;
    TrieNode * insert(string & word) {
        TrieNode * root = this;
        for (auto c : word) {
            if (!root->links[c - 'a'])
                root->links[c - 'a'] = new TrieNode;
            root = root->links[c - 'a'];
        }
        root->end = true;
        return root;
    }
    static bool search(TrieNode * root, string & word, int st, int mismatch = 1) {
        if (!root) return false;
        if (st == word.size())
            return root->end && !mismatch;
        char c = word[st] - 'a';
        if (!mismatch)
            return search(root->links[c], word, st + 1, 0);
        else {
            for (int i = 0; i < 26; i++) {
                if (!root->links[i]) continue;
                if (search(root->links[i], word, st + 1, mismatch - (i != c)))
                    return true;
            }
            return false;
        }
    }
};

class MagicDictionary {
public:
    TrieNode root;
    /** Initialize your data structure here. */
    MagicDictionary() {

    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for (auto & s : dict)
            root.insert(s);
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        return TrieNode::search(&root, word, 0, 1);
    }
};
```