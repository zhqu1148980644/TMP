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
public:
    int m, n;
    bool dfs(vector<vector<char>> & board, string & word, int i, int j, int st) {
        if (st == word.size()) return true;
        if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[st])
            return false;
        board[i][j] = '@';
        bool find = dfs(board, word, i + 1, j, st + 1)
                    || dfs(board, word, i - 1, j , st + 1)
                    || dfs(board, word, i, j + 1, st + 1)
                    || dfs(board, word, i, j - 1, st + 1);

        board[i][j] = word[st];
        return find;
    }
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size(); n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (board[i][j] == word[0] && dfs(board, word, i, j, 0))
                    return true;
        return false;
    }
};
```