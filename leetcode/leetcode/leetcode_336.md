---
title: Palindrome Pairs
date: 2021-01-04
---

Given a list of unique words, return all the pairs of the distinct indices (i, j) in the given list, so that the concatenation of the two words words[i] + words[j] is a palindrome.

 

Example 1:

Input: words = ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
Example 2:

Input: words = ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]
Example 3:

Input: words = ["a",""]
Output: [[0,1],[1,0]]
 

Constraints:

1 <= words.length <= 5000
0 <= words[i] <= 300
words[i] consists of lower-case English letters.


#### Solutions

1. ##### straight forward O(n2 * len(w))

- May got TLE.

```cpp
class Solution {
public:
    bool ispalin(string & s1, string & s2, int i, int j) {
        int n1 = s1.size(), n2 = s2.size();
        while (i < n1 && j > 0)
            if (s1[i++] != s2[--j])
                return false;

        if (&s1 == &s2)
            return true;
        else if (i < n1)
            return ispalin(s1, s1, i, s1.size());
        else if (j > 0)
            return ispalin(s2, s2, 0, j);
        else
            return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size();
        vector<vector<int>> res;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (ispalin(words[i], words[j], 0, words[j].size()))
                    res.push_back({i, j});
            }
        
        return res;
    }
};
```


2. ##### trie O(mn)

- `O(mn)`. m is number of words, n is the average length of each word.
- For `s1 + s2, len(s1) > len(s2)` to be palindrome, we can put `rev(s2)` into a trie, then for a given `s1`, we can search for all possible `s2` such that `rev(s2)` equals to a prefix string of `s1` in `O(len(s1))` time.
    - After that, we only need to check if the trailing part of `s1` is a palindrome.
- For cases when `len(s1) < len(s2)`, we can treat `rev(s2)` as `s1` and put all `s1` into a trie, then all steps followed are the same as above.
- Check if a substring is a palindrome can be achieved in `O(n)` time when using `Manacher` alrogithm.

```cpp
struct Trie {
    Trie* links[26] = {nullptr};
    int pos = -1;
    ~Trie() {
        for (auto pch : links)
            if (pch) delete pch;
    }
    template <typename It>
    void insert(It lo, It hi, int pos) {
        Trie * root = this;
        while (lo < hi) {
            auto c = *lo++ - 'a';
            if (!root->links[c])
                root->links[c] = new Trie;
            root = root->links[c];
        }
        root->pos = pos;
    }
};

bool ispalin(const string & s, int i, int j) {
    while (i < j && s[i] == s[j]) {
        i++; j--;
    }
    return i >= j;
}

class Solution {
public:
    Trie root, rroot;
    vector<vector<int>> palindromePairs(vector<string>& words) {
        // handle empty string specifically.
        vector<int> empty, palins;
        for (int wi = 0; wi < words.size(); wi++) {
            auto & w = words[wi];
            if (w.size() == 0)
                empty.push_back(wi);
            else {
                root.insert(w.rbegin(), w.rend(), wi);
                rroot.insert(w.begin(), w.end(), wi);
                // can be precomputed by manacher algorithm and will be reused in later step.
                if (ispalin(w, 0, w.size() - 1))
                    palins.push_back(wi);
            }
        }

        set<vector<int>> s;
        for (int wi = 0; wi < words.size(); wi++) {
            auto & w = words[wi];
            int n = w.size();

            // case when s1 + s2, len(s1) > len(s2)
            Trie * root = &this->root;
            for (int i = 0; i < n; i++) {
                if (!(root = root->links[w[i] - 'a']))
                    break;
                if (root->pos == -1 || root->pos == wi)
                    continue;
                if (ispalin(w, i + 1, n - 1)) // can be precomputed
                    s.insert({wi, root->pos});
            }
            // case when s1 + s2, len(s1) < len(s2)
            root = &this->rroot;
            for (int i = n - 1; i >= 0; i--) {
                if (!(root = root->links[w[i] - 'a']))
                    break;
                if (root->pos == -1 || root->pos == wi)
                    continue;
                if (ispalin(w, 0, i - 1)) { // can be precomputed
                    s.insert({root->pos, wi});
                }
            }
        }

        vector<vector<int>> res {s.begin(), s.end()};
        // handle empty string specifically.
        for (auto ei : empty)
            for (auto pi : palins) {
                res.push_back({ei, pi});
                res.push_back({pi, ei});
            }

        return res;
    }
};
```