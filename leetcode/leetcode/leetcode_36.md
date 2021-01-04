---
title: Valid Sudoku
date: 2021-01-04
---
### Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.

![soduku](https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png)

A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

```
Example 1:

Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true
Example 2:

Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
```

### Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
The given board contain only digits 1-9 and the character '.'.
The given board size is always 9x9.

### Solutions

1. #### One pass

- Use `hashtable` to record the occurrence of each number in each row, column and block.
- Since the numers are no more than 9, a bit map can be used as hashtable.

```cpp
class Solution {
private:
    int rowm[9];
    int colm[9];
    int boardm[9];
    
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int n;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if ((n = board[i][j] - '0') <= 0) continue;
                n = 1 << n - 1;
                if (rowm[i] & n) return false; else rowm[i] |= n;
                if (colm[j] & n) return false; else colm[j] |= n;
                int bn = (i / 3) * 3 + j / 3;
                if (boardm[bn] & n) return false; else boardm[bn] |= n;
            }
        }
        return true;
    }
};
```



