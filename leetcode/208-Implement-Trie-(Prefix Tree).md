#### Implement a trie with insert, search, and startsWith methods.

```
Example:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");   
trie.search("app");     // returns true
```

#### Note:

-    You may assume that all inputs are consist of lowercase letters a-z.
-    All inputs are guaranteed to be non-empty strings.

#### Solutions

1. ##### straight forward

```c++
class Trie {
private:
    class TrieNode {
    private:
        TrieNode * links[26] = {nullptr};
        bool End = false;

    public:
        TrieNode() {}
        ~TrieNode() {
            for (int i = 0; i < 26; i++)
                if (!links[i]) delete links[i];
        }
        bool contain(char ch) {
            return links[ch - 'a'] != nullptr;
        }
        bool put(char ch) {
            if (links[ch - 'a'])
                return false;
            else {
                links[ch - 'a'] = new TrieNode();
                return true;
            }
        }
        TrieNode * get(char ch) {
            return links[ch - 'a'];
        }
        bool & end() { return End; }
    };

    TrieNode root;

public:
    /** Initialize your data structure here. */
    Trie() {}

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode * root = &(this->root);
        for (int i = 0; i < word.size(); i++) {
            if (!root->contain(word[i])) {
                root->put(word[i]);
            }
            root = root->get(word[i]);
        }
        root->end() = true;
    }

    TrieNode * searchPrefix(string word) {
        TrieNode * root = &(this->root);
        for (int i = 0; i < word.size(); i++) {
            if (root->contain(word[i]))
                root = root->get(word[i]);
            else
                return nullptr;
        }
        return root;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode * pnode = searchPrefix(word);
        return pnode != nullptr && pnode->end();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return searchPrefix(prefix) != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```