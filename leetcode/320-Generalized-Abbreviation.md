Write a function to generate the generalized abbreviations of a word. 

Note: The order of the output does not matter.

Example:

Input: "word"
Output:
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

#### Solutions

- To be precise, the problem need to find all permutations of the string and replace contiguous spaces with the corresponding number.

1. ##### permutation with bit representation O(n * 2^n)

```c++
class Solution {
public:
    string build(string & word, int com) {
        string s; 
        int len = word.size(), slen = 0;
        for (int i = 0; i < len; i++) {
            if (com & 1 << (len - i - 1)) {
                if (slen) s += to_string(slen);
                s.push_back(word[i]);
                slen = 0;
            }
            else
                slen++;
        }
        if (slen) s += to_string(slen);
        return s;
    }
    vector<string> generateAbbreviations(string word) {
        int mask = 1 << word.size();
        vector<string> res;
        for (int com = 0; com < mask; com++)
            res.push_back(build(word, com));
        return res;
    }
};
```


2. ##### dfs

```c++
class Solution {
public:
    vector<string> res;
    void dfs(string & word, string cur, int st, int numspace) {
        if (st == word.size()) {
            if (numspace > 0) cur += to_string(numspace);
            res.push_back(cur);
        }
        else {
            dfs(word, cur, st + 1, numspace + 1);
            if (numspace) cur += to_string(numspace);
            cur.push_back(word[st]);
            dfs(word, cur, st + 1, 0);
        }
    }
    vector<string> generateAbbreviations(string word) {
        dfs(word, "", 0, 0);
        return res;
    }
};
```