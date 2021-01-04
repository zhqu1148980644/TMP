---
title: Available Captures for Rook
date: 2021-01-04
---
On an 8 x 8 chessboard, there is one white rook.  There also may be empty squares, white bishops, and black pawns.  These are given as characters 'R', '.', 'B', and 'p' respectively. Uppercase characters represent white pieces, and lowercase characters represent black pieces.

The rook moves as in the rules of Chess: it chooses one of four cardinal directions (north, east, west, and south), then moves in that direction until it chooses to stop, reaches the edge of the board, or captures an opposite colored pawn by moving to the same square it occupies.  Also, rooks cannot move into the same square as other friendly bishops.

Return the number of pawns the rook can capture in one move.

 

Example 1:



Input: [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","R",".",".",".","p"],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation: 
In this example the rook is able to capture all the pawns.
Example 2:



Input: [[".",".",".",".",".",".",".","."],[".","p","p","p","p","p",".","."],[".","p","p","B","p","p",".","."],[".","p","B","R","B","p",".","."],[".","p","p","B","p","p",".","."],[".","p","p","p","p","p",".","."],[".",".",".",".",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 0
Explanation: 
Bishops are blocking the rook to capture any pawn.
Example 3:



Input: [[".",".",".",".",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".","p",".",".",".","."],["p","p",".","R",".","p","B","."],[".",".",".",".",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","p",".",".",".","."],[".",".",".",".",".",".",".","."]]
Output: 3
Explanation: 
The rook can capture the pawns at positions b5, d6 and f5.
 

Note:

board.length == board[i].length == 8
board[i][j] is either 'R', '.', 'B', or 'p'
There is exactly one cell with board[i][j] == 'R'

#### Solutions

- In sumarray, starting at `R`, you can go four directions utill meets a `p`/`B` or outside of the board. Return the total sum of `p` you can visit in four directions. Apparently, the maxinum num is `4`.

1. ##### straight forward

```cpp
class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        
        auto [x, y] = [&]() {
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    if  (board[i][j] == 'R')
                        return make_pair(i, j);
            return make_pair(0, 0);
        }();

        int res = 0;
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (auto & d : dirs) {
            int i = x, j = y;
            while (true) {
                i += d[0]; j += d[1];
                if (i < 0 || j < 0 || i >= m || j >= n)
                    break;
                if (board[i][j] == 'p') {
                    res++; break;
                }
                if (board[i][j] == 'B')
                    break;
            }
        }

        return res;
    }
};
```