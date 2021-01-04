---
title: Search Suggestions Syste
date: 2021-01-04
---
Given an array of strings products and a string searchWord. We want to design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with the searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.

Return list of lists of the suggested products after each character of searchWord is typed. 

 

Example 1:

Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
After typing mou, mous and mouse the system suggests ["mouse","mousepad"]
Example 2:

Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Example 3:

Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
Example 4:

Input: products = ["havana"], searchWord = "tatiana"
Output: [[],[],[],[],[],[],[]]
 

Constraints:

1 <= products.length <= 1000
There are no repeated elements in products.
1 <= Σ products[i].length <= 2 * 10^4
All characters of products[i] are lower-case English letters.
1 <= searchWord.length <= 1000
All characters of searchWord are lower-case English letters.


#### Solutions

1. ##### trie and recursive search

- Store all products in a trie, then for each prefix, use recursive search to find at most k words in lexicographical order.

```cpp
struct Trie {
    Trie* nodes[26] = {nullptr};
    bool isworld = false;
    ~Trie() {
        for (auto node : nodes)
            if (node) delete node;
    }
    template <typename It>
    void insert(It lo, It hi) {
        if (lo == hi) return;
        Trie * cur = this;
        int len = 0;
        while (lo != hi) {
            len++;
            auto c = *lo++ - 'a';
            if (!cur->nodes[c])
                cur->nodes[c] = new Trie;
            cur = cur->nodes[c];
        }
        if (len) cur->isworld = true;
    }
};

// recursive search, untill no ways left or k words has been encountered
void search(Trie * cur, string & s, vector<string> & res, int & k) {
    if (k <= 0) return;
    if (cur->isworld) {
        res.push_back(s);
        k--;
    }
    for (int i = 0; i < 26 && k > 0; i++) {
        if (!cur->nodes[i]) continue;
        s.push_back('a' + i);
        search(cur->nodes[i], s, res, k);
        s.pop_back();
    }
}

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie root;
        for (auto & ps : products)
            root.insert(ps.begin(), ps.end());

        Trie * cur = &root;
        vector<vector<string>> res;
        string curs;
        for (auto c : searchWord) {
            if (!cur->nodes[c - 'a']) break;
            cur = cur->nodes[c - 'a'];
            curs += c;
            res.push_back({});
            int maxnum = 3;
            search(cur, curs, res.back(), maxnum);
        }

        res.resize(searchWord.size());
        return res;
    }
};
```

2. ##### trie with treeset

- For each character of the trie, maintaining the three smallest words passed on this character.

```cpp

struct Trie {
    Trie* nodes[26] = {nullptr};
    set<string> words;
    ~Trie() {
        for (auto node : nodes)
            if (node) delete node;
    }
    void insert(const string & s) {
        if (!s.size()) return;
        Trie * cur = this;
        for (auto c : s) {
            c -= 'a';
            if (!cur->nodes[c])
                cur->nodes[c] = new Trie;
            cur = cur->nodes[c];
            // insert. only store the 3 smallest words.
            auto & words = cur->words;
            words.insert(s);
            if (words.size() > 3)
                words.erase(prev(words.end()));
        }
    }
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie root;
        for (auto & ps : products)
            root.insert(ps);

        Trie * cur = &root;
        vector<vector<string>> res;
        for (auto c : searchWord) {
            if (!cur->nodes[c - 'a']) break;
            cur = cur->nodes[c - 'a'];
            res.emplace_back(cur->words.begin(), cur->words.end());
        }

        res.resize(searchWord.size());
        return res;
    }
};
```

3. ##### binary search

- Sort all products in lexicographical ascending order, then use binary search to find the first product >= cur_prefix.

```cpp
class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());

        string s;
        vector<vector<string>> res;
        for (auto c : searchWord) {
            s += c;
            vector<string> row;
            // first product >= cur_prefix
            auto it = lower_bound(products.begin(), products.end(), s);
            for (int i = 0; i < 3 && it != products.end(); i++) {
                if (it->substr(0, s.size()) == s)
                    row.push_back(*it++);
                else break;
            }
            res.push_back(move(row));
        }

        return res;
    }
};
```