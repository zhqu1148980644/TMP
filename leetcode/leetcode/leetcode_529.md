---
title: Minesweeper
date: 2021-01-04
---
Let's play the minesweeper game (Wikipedia, online game)!

You are given a 2D char matrix representing the game board. 'M' represents an unrevealed mine, 'E' represents an unrevealed empty square, 'B' represents a revealed blank square that has no adjacent (above, below, left, right, and all 4 diagonals) mines, digit ('1' to '8') represents how many mines are adjacent to this revealed square, and finally 'X' represents a revealed mine.

Now given the next click position (row and column indices) among all the unrevealed squares ('M' or 'E'), return the board after revealing this position according to the following rules:

If a mine ('M') is revealed, then the game is over - change it to 'X'.
If an empty square ('E') with no adjacent mines is revealed, then change it to revealed blank ('B') and all of its adjacent unrevealed squares should be revealed recursively.
If an empty square ('E') with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
Return the board when no more squares will be revealed.
 

Example 1:

Input: 

[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

Output: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:

Example 2:

Input: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

Output: 

[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'X', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Explanation:

 

Note:

The range of the input matrix's height and width is [1,50].
The click position will only be an unrevealed square ('M' or 'E'), which also means the input board contains at least one clickable square.
The input board won't be a stage when game is over (some mines have been revealed).
For simplicity, not mentioned rules should be ignored in this problem. For example, you don't need to reveal all the unrevealed mines when the game is over, consider any cases that you will win the game or flag any squares.


#### Solutions

1. ##### dfs

- Note that we need to stop the recusion as soon as there are mines in the neighbor of the current node.

```cpp
class Solution {
public:
    int m, n;
    int dirs[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
                {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    vector<vector<char>> board;
    int ismine(int x, int y) {
        if (x < 0 || x >= m || y < 0 || y >= n 
        || board[x][y] == 'B' || isdigit(board[x][y]))
            return 0;
        return board[x][y] != 'E';
    }
    void reveal(int x, int y) {
        if (x < 0 || x >= m || y < 0 || y >= n 
        || board[x][y] != 'E')
            return;
        int nummine = 0;
        for (auto & d : dirs)
            nummine += ismine(x + d[0], y + d[1]);
        // stop recusion
        if (nummine)
            board[x][y] = nummine + '0';
        else {
            board[x][y] = 'B';
            for (auto & d : dirs)
                reveal(x + d[0], y + d[1]);
        }
    }
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        m = board.size(); n = board[0].size();
        int x = click[0], y = click[1];
        swap(this->board, board);
        if (this->board[x][y] == 'M')
            this->board[x][y] = 'X';
        else
            reveal(x, y);
        return this->board;
    }
};
```

2. ##### bfs

```cpp
class Solution {
public:
    int m, n;
    int dirs[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
                {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    int ismine(vector<vector<char>> & board, int x, int y) {
        if (x < 0 || x >= m || y < 0 || y >= n 
        || board[x][y] == 'B' || isdigit(board[x][y]))
            return 0;
        return board[x][y] != 'E';
    }
    bool check(vector<vector<char>> & board, int x, int y) {
        if (board[x][y] == 'M')
            board[x][y] = 'X';
        else {
            int nummine = 0;
            for (auto & d : dirs)
                nummine += ismine(board, x + d[0], y + d[1]);
            if (nummine > 0)
                board[x][y] = nummine + '0';
            else
                board[x][y] = 'B';
        }
        return board[x][y] == 'B';
    }
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        m = board.size(); n = board[0].size();
        int x = click[0], y = click[1];

        queue<pair<int, int>> q;
        if (check(board, x, y)) q.push({x, y});
        while (q.size()) {
            auto [x, y] = q.front(); q.pop();
            for (auto & d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n 
                    || board[nx][ny] != 'E')
                    continue;
                if (check(board, nx, ny)) q.push({nx, ny});
            }
        }

        return board;
    }
};
```