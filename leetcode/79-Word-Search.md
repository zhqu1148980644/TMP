#### Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

```
Example:

board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

Given word = "ABCCED", return true.
Given word = "SEE", return true.
Given word = "ABCB", return false.
```

#### Solutions

1. ##### dfs

- As each character can be used only once, we should use a visited table to record the passed character.
- Or use in-place mark. ie. mark traversed character to `.` and restore the original character when tracebacked.

```c++
class Solution {
private:
    int nrow;
    int ncol;
    string word;

public:

    bool dfs(vector<vector<char>> & board, int i, int j, int start) {
        if (start == word.size())
            return true;

        if (i < 0 || i >= nrow 
            || j < 0 || j >= ncol 
            || board[i][j] != word[start]
            || board[i][j] == '.')
            return false;

        board[i][j] = '.';
        bool find = dfs(board, i + 1, j, start + 1)
                    || dfs(board, i - 1, j, start + 1)
                    || dfs(board, i, j + 1, start + 1)
                    || dfs(board, i, j - 1, start + 1);
        board[i][j] = word[start];

        return find;
    }

    bool exist(vector<vector<char>>& board, string word) {
        nrow = board.size();
        if (!nrow) return false;
        ncol = board[0].size();
        if (nrow * ncol < word.size() || !ncol) return false;

        this->word = word;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (board[i][j] == word[0] && dfs(board, i, j, 0))
                    return true;


        return false;

    }
};
```