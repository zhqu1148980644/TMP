---
title: HTML Entity Parser
date: 2021-01-04
---
HTML entity parser is the parser that takes HTML code as input and replace all the entities of the special characters by the characters itself.

The special characters and their entities for HTML are:

- Quotation Mark: the entity is &quot; and symbol character is ".
Single Quote Mark: the entity is &apos; and symbol character is '.
- Ampersand: the entity is &amp; and symbol character is &.
Greater Than Sign: the entity is &gt; and symbol character is >.
- Less Than Sign: the entity is &lt; and symbol character is <.
- Slash: the entity is &frasl; and symbol character is /.
- Given the input text string to the HTML parser, you have to implement the entity parser.

Return the text after replacing the entities by the special characters.

 
```
Example 1:

Input: text = "&amp; is an HTML entity but &ambassador; is not."
Output: "& is an HTML entity but &ambassador; is not."
Explanation: The parser will replace the &amp; entity by &
Example 2:

Input: text = "and I quote: &quot;...&quot;"
Output: "and I quote: \"...\""
Example 3:

Input: text = "Stay home! Practice on Leetcode :)"
Output: "Stay home! Practice on Leetcode :)"
Example 4:

Input: text = "x &gt; y &amp;&amp; x &lt; y is always false"
Output: "x > y && x < y is always false"
Example 5:

Input: text = "leetcode.com&frasl;problemset&frasl;all"
Output: "leetcode.com/problemset/all"
```

Constraints:

1 <= text.length <= 10^5
The string may contain any possible characters out of all the 256 ASCII characters.


#### Solutions

1. ##### straight forward

```cpp
class Solution {
public:
    string entityParser(string text) {
        unordered_map<string, char> m = {
            {"&quot;", '"'}, {"&apos;", '\''}, {"&amp;", '&'}, 
            {"&gt;", '>'}, {"&lt;", '<'}, {"&frasl;", '/'}
        };
        
        string res;
        string_view sv(text);
        int cur = 0;
        while (cur < text.size()) {
            bool match = false;
            if (sv[cur] == '&') {
                for (auto & [w, c] : m) {
                    if (sv.substr(cur, w.size()) == w) {
                        res.push_back(c);
                        cur += w.size();
                        match = true;
                        break;
                    }
                }
            }
            if (!match)
                res.push_back(sv[cur++]);
        }

        return res;
    }
};
```

2. ##### trie

- Since there are only few entities, the efficiency of trie may not be prominent.

```cpp
class Trie {
public:
    struct TrieNode {
        TrieNode * links[256] = {nullptr};
        int size = 0;
        char replace = 0;
        ~TrieNode() {
            for (int i = 0; i < 256; i++)
                if (!links[i]) delete links[i];
        }
    };
    TrieNode root;

    void insert(const string & word, char replace) {
        TrieNode * root = &(this->root);
        for (int i = 0; i < word.size(); i++) {
            if (!root->links[word[i]])
                root->links[word[i]] = new TrieNode();
            root = root->links[word[i]];
        }
        root->size = word.size();
        root->replace = replace;
    }
    TrieNode * search(string_view word) {
        TrieNode * root = &(this->root);
        for (int i = 0; i < word.size(); i++) {
            if (root->links[word[i]]) {
                root = root->links[word[i]];
                if (root->size) return root;
            }
            else
                return nullptr;
        }
        return root;
    }
};
class Solution {
public:
    string entityParser(string text) {
        unordered_map<string, char> m = {
            {"&quot;", '"'}, {"&apos;", '\''}, {"&amp;", '&'}, 
            {"&gt;", '>'}, {"&lt;", '<'}, {"&frasl;", '/'}
        };
        Trie trie;
        for (auto & [w, c] : m)
            trie.insert(w, c);
        
        string res;
        string_view sv(text);
        int cur = 0;
        while (cur < text.size()) {
            auto pfind = trie.search(sv.substr(cur));
            res.push_back(pfind ? pfind->replace :text[cur]);
            cur += pfind ? pfind->size : 1;
        }

        return res;
    }
};
```