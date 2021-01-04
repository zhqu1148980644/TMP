---
title: Sudoku Solver
date: 2021-01-04
---
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
Empty cells are indicated by the character '.'.


A sudoku puzzle...


...and its solution numbers marked in red.

Note:

The given board contain only digits 1-9 and the character '.'.
You may assume that the given Sudoku puzzle will have a single unique solution.
The given board size is always 9x9.


#### Solutions

1. ##### backtrack O(9!)^9

- For each row, there are `9!` possibilities in the worst case.

```cpp
class Solution {
public:
#define bi(x, y) (((x / 3) * 3 + y / 3))
    inline bool valid(int i, int j, int key) {
        return !((cols[j] & key) || (rows[i] & key) || (boxes[bi(i, j)] & key));
    }
    inline void flip(int i, int j, int key) {
        cols[j] ^= key; rows[i] ^= key; boxes[bi(i, j)] ^= key;
    }
    // backtrack row by row
    bool solve(vector<vector<char>> & board, int i, int j) {
        if (i == 8 && j == 9) return true;
        if (j == 9) { i++; j = 0;}
        if (board[i][j] > '9')
            return solve(board, i, j + 1);
        else {
            for (int n = 1; n <= 9; n++) {
                // pass invalid path
                if (!valid(i, j, 1 << n)) continue;
                board[i][j] = '0' + n;
                flip(i, j, 1 << n);
                if (solve(board, i, j + 1))
                    return true;
                flip(i, j, 1 << n);
            }
            return false;
        }
    }
    vector<int> cols, rows, boxes;
    void solveSudoku(vector<vector<char>>& board) {
        rows = cols = boxes = vector<int>(9);
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    flip(i, j, 1 << (board[i][j] - '0'));
                    board[i][j] += 10;
                }
                else board[i][j] = '0';
            }
        solve(board, 0, 0);
        for (auto & v : board)
            for (auto & c : v)
                if (c > '9') c -= 10;
    }
};
```