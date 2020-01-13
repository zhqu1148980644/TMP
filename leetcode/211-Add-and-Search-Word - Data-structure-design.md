#### Design a data structure that supports the following two operations:

- void addWord(word)
- bool search(word)

- search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

```
Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
```

#### Note:
- You may assume that all words are consist of lowercase letters a-z.

#### Solutions

1. ##### trie

```c++
class Trie {
private:
    Trie *links[26] = {nullptr};
    bool is_word = false;
public:
    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (links[i]) delete links[i];
    }
    Trie * insert(string & word) {
        Trie * root = this;
        for (int i = 0; i < word.size(); i++) {
            char cur = word[i];
            if (!root->links[cur - 'a'])
                root->links[cur - 'a'] = new Trie();
            root = root->links[cur - 'a'];
        }
        root->is_word = true;
        return root;
    }
    // A total recursive version could be more concise, however when the string is too long, this may be inadequate.
    Trie * searchPrefix(const string & word) {
        Trie * root = this;
        for (int i = 0; i < word.size(); i++) {
            char cur = word[i];
            if (cur == '.') {
                Trie * find = nullptr;
                for (int j = 0; j < 26; j++) {
                    if (!root->links[j]) continue;
                    if (i + 1 == word.size())
                        find = root->links[j];
                    else
                        find = root->links[j]->searchPrefix(word.substr(i + 1));
                    if (find && find->isWord())
                        break;
                }
                return find;
            }
            else if (root->links[cur - 'a'])
                root = root->links[cur - 'a'];
            else
                return nullptr;
        }
        return root;
    }
    bool isWord() {
        return is_word;
    }
};

class WordDictionary {
private:
    Trie root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {}

    /** Adds a word into the data structure. */
    void addWord(string word) {
        root.insert(word);
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        Trie * res = root.searchPrefix(word);
        return res != nullptr && res->isWord();
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
```