Given a paragraph and a list of banned words, return the most frequent word that is not in the list of banned words.  It is guaranteed there is at least one word that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of punctuation.  Words in the paragraph are not case sensitive.  The answer is in lowercase.

 

Example:

Input: 
paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
banned = ["hit"]
Output: "ball"
Explanation: 
"hit" occurs 3 times, but it is a banned word.
"ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
Note that words in the paragraph are not case sensitive,
that punctuation is ignored (even if adjacent to words, such as "ball,"), 
and that "hit" isn't the answer even though it occurs more because it is banned.
 

Note:

1 <= paragraph.length <= 1000.
0 <= banned.length <= 100.
1 <= banned[i].length <= 10.
The answer is unique, and written in lowercase (even if its occurrences in paragraph may have uppercase symbols, and even if it is a proper noun.)
paragraph only consists of letters, spaces, or the punctuation symbols !?',;.
There are no hyphens or hyphenated words.
Words only consist of letters, never apostrophes or other punctuation symbols.

#### Solutions

1. ##### trie

```c++
struct Trie {
    vector<Trie *> links {26};
    int cnt = 0;
    string_view word;
    Trie * maxs = nullptr;

    Trie * insert(string_view w) {
        Trie * root = this;
        for (auto c : w) {
            c = tolower(c);
            if (!root->links[c - 'a'])
                root->links[c - 'a'] = new Trie;
            root = root->links[c - 'a'];
        }
        if (!root->word.size())
            root->word = w;
        root->cnt++;
        if (!maxs || maxs->cnt < root->cnt)
            maxs = root;
        return root;
    }
    
};
class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        Trie root;
        for (auto & w : banned) {
            Trie * pw = root.insert(w);
            if (pw->cnt >= 0) pw->cnt = INT_MIN;
        }

        paragraph.push_back(' ');
        string_view sv(paragraph);
        for (int i = 0, j = 0; j < sv.size(); j++) {
            if (!isalpha(sv[j])) {
                if (!j || isalpha(sv[j - 1]))
                    root.insert(sv.substr(i, j - i));
                i = j + 1;
            }
        }

        string res(root.maxs->word);
        for (auto & c : res)
            c = tolower(c);
        
        return res;
    }
};
```

2. ##### hashmap

```c++
class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        for (auto & c : paragraph) c = tolower(c);
        for (auto & w : banned)
            for (auto & c : w)
                c = tolower(c);
        unordered_set<string_view> forbid(banned.begin(), banned.end());
        unordered_map<string_view, int> count;
        paragraph.push_back(' ');
        string_view sv(paragraph), maxs, word;
        int maxc = 0;
        
        for (int i = 0, j = 0; j < sv.size(); j++)
            if (!isalpha(sv[j])) {
                if ((!j || isalpha(sv[j - 1])) && !forbid.count(word = sv.substr(i, j - i)))
                    if (maxc < ++count[word]) {
                        maxs = word;
                        maxc = count[word];
                    }
                i = j + 1;
            }

        return string(maxs);
    }
};
```