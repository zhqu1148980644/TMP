---
title: Word Search II
date: 2021-01-04
---
#### Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

```
Example:

Input: 
board = [
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
words = ["oath","pea","eat","rain"]

Output: ["eat","oath"]
```
 

#### Note:

-    All inputs are consist of lowercase letters a-z.
-    The values of words are distinct.


#### Solutions

1. ##### dfs with trie

- reference: https://leetcode.com/problems/word-search-ii/discuss/59780/Java-15ms-Easiest-Solution-(100.00)
- The idea is to check `multiple` words at `O(1) `time when we traversing each characters in the board. ie. if the current character is not a part of prefixs of any word, we should backtrack to the last step. 
- To speed up the algorithm:
    - Store words at the `end` of trie nodes. Thus there is no need to pass a prefix string through the dfs traversal.
    - Remove the `end mark` of a node after we saved the string to prevent collecting multiple duplicate words.
    - Use inplace mark to represent passed characters in dfs.

```cpp
class Trie {
public:
    Trie * links[26] = {nullptr};
    string * word;

    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (links[i]) delete links[i];
        if (word) delete word;
    }
    void insert(string & word) {
        Trie * root = this;
        for (int i = 0; i < word.size(); i++) {
            char cur = word[i];
            if (!root->links[cur - 'a'])
                root->links[cur - 'a'] = new Trie();
            root = root->links[cur - 'a'];
        }
        root->word = new string(word);
    }
};

class Solution {
private:
    Trie trie;
    vector<string> res;

    void dfs(int x, int y, Trie * root, vector<vector<char>> & board) {
        char cur = board[x][y];
        if (cur == '#' || !(root->links[cur - 'a']))
            return;
        root = root->links[cur - 'a'];
        if (root->word) {
            res.push_back(*(root->word));
            root->word = nullptr;
        }

        board[x][y] = '#';
        if (x > 0) dfs(x - 1, y, root, board);
        if (y > 0) dfs(x, y - 1, root, board);
        if (x + 1 < board.size()) dfs(x + 1, y, root, board);
        if (y + 1 < board[0].size()) dfs(x, y + 1, root, board);
        board[x][y] = cur;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for (auto & word : words)
            trie.insert(word);

        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++) {
                dfs(i, j, &trie, board);
            }
        return res;
    }
};
```