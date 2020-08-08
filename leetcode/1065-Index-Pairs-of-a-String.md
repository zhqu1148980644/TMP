Given a text string and words (a list of strings), return all index pairs [i, j] so that the substring text[i]...text[j] is in the list of words.

 

Example 1:

Input: text = "thestoryofleetcodeandme", words = ["story","fleet","leetcode"]
Output: [[3,7],[9,13],[10,17]]
Example 2:

Input: text = "ababa", words = ["aba","ab"]
Output: [[0,1],[0,2],[2,3],[2,4]]
Explanation: 
Notice that matches can overlap, see "aba" is found in [0,2] and [2,4].
 

Note:

All strings contains only lowercase English letters.
It's guaranteed that all strings in words are different.
1 <= text.length <= 100
1 <= words.length <= 20
1 <= words[i].length <= 50
Return the pairs [i,j] in sorted order (i.e. sort them by their first coordinate in case of ties sort them by their second coordinate).

#### Solutions

1. ##### trie

```c++
struct Trie {
    Trie * links[26] = {nullptr};
    bool isend = false;
    Trie * insert(string & s) {
        Trie * root = this;
        for (auto & c : s) {
            c -= 'a';
            if (!root->links[c])
                root->links[c] = new Trie;
            root = root->links[c];
        }
        root->isend = true;
        return root;
    }
    template <typename It>
    vector<int> count(It begin, It end) {
        Trie * root = this;
        vector<int> lens;
        int len = 0;
        while (begin != end) {
            auto c = *begin++ - 'a';
            root = root->links[c];
            len++;
            if (root) {
                if (root->isend)
                    lens.push_back(len);
            }
            else break;
        }
        return lens;
    }
};
class Solution {
public:
    vector<vector<int>> indexPairs(string text, vector<string>& words) {
        Trie root;
        for (auto & w : words)
            root.insert(w);
        
        vector<vector<int>> res;
        auto begin = text.begin();
        auto end = text.end();
        while (begin != end) {
            auto vlen =  root.count(begin, end);
            int i = begin - text.begin();
            for (auto len : vlen)
                res.push_back({i, i + len - 1});
            begin++;
        }
        
        return res;
    }
};
```