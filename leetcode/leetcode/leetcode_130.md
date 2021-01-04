---
title: Surrounded Regions
date: 2021-01-04
---
#### Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

```
Example:

X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
```

#### Explanation:

- Surrounded regions shouldn’t be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.

#### Solutions

- Find all `O` at borders, then find all `O` connected with these `O` at borders. Mark these unsurrounded region with any characters except `O/X`. For example: `@`
- Traverse the whole board and repalce `O` with `X` and replace `@` back to `O`.

1. ##### dfs with recursion

```cpp
class Solution {
public:

    void dfs(vector<vector<char>> & board, int x, int y) {
        if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size())
            return;
        else if (board[x][y] == 'O') {
            board[x][y] = '@';
            dfs(board, x - 1, y);
            dfs(board, x + 1, y);
            dfs(board, x, y - 1);
            dfs(board, x, y + 1);
        }
    }

    void solve(vector<vector<char>>& board) {
        int nrow = board.size(); if (!nrow) return;
        int ncol = board[0].size();

        for (int j = 0; j < ncol; j++) {
                dfs(board, 0, j);
                dfs(board, nrow - 1, j);
        }

        for (int i = 0; i < nrow; i++) {
                dfs(board, i, 0);
                dfs(board, i, ncol - 1);
        }

        for (auto & row : board)
            for (auto & item : row)
                if (item == '@')
                    item = 'O';
                else
                    item = 'X';

    }
};
```


2. ##### bfs with queue


```cpp

typedef pair<int, int> Coor;
class Solution {
private:
    int nrow;
    int ncol;

public:
    void bfs(vector<vector<char>> & board, queue<Coor> & todos, char mark) {
        int x, y;
        while (!todos.empty()) {
            x = todos.front().first;
            y = todos.front().second;
            todos.pop();
            auto & item = board[x][y];
            if (item == 'O') {
                item = mark;
                if (x - 1 > 0)
                    todos.push(make_pair(x - 1, y));
                if (x + 1 < nrow)
                    todos.push(make_pair(x + 1, y));
                if (y - 1 > 0)
                    todos.push(make_pair(x, y - 1));
                if (y + 1 < ncol)
                    todos.push(make_pair(x, y + 1));
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        this->nrow = board.size(); if (!nrow) return;
        this->ncol = board[0].size();
        queue<pair<int, int>> todos;

        for (int j = 0; j < ncol; j++) {
                todos.push(make_pair(0, j));
                todos.push(make_pair(nrow - 1, j));
        }

        for (int i = 0; i < nrow; i++) {
                todos.push(make_pair(i, 0));
                todos.push(make_pair(i, ncol - 1));
        }

        bfs(board, todos, '@');

        for (auto & row : board)
            for (auto & item : row)
                if (item == '@')
                    item = 'O';
                else
                    item = 'X';

    }
};
```

3. ##### Union find O(n2) S(n2)


- Treat every `O` at borders or connected to borders as a union, and set every item not in this union as `X`.

```cpp
template <typename T>
class UnionFind {
public:
    vector<T> nodes;
    vector<T> sizes;

    UnionFind(T size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    T find(T node) {
        while (nodes[node] != node) {
            nodes[node] = nodes[nodes[node]];
            node = nodes[node];
        }
        return node;
    }
    bool merge(T node1, T node2) {
        T f1 = find(node1);
        T f2 = find(node2);
        if (f1 == f2)
            return false;
        else {
            if (sizes[f2] < sizes[f1])
                swap(f1, f2);
            sizes[f2] += sizes[f1];
            nodes[f1] = f2;
            return true;
        }
    }
};

class Solution {
public:
    int nrow, ncol;
    inline int node(int i, int j) {
        return i * ncol + j;
    }
    void solve(vector<vector<char>>& board) {
        nrow = board.size(); if (!nrow) return;
        ncol = board[0].size();

        UnionFind<int> uf(nrow * ncol + 1);
        int border = nrow * ncol;

        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (board[i][j] != 'O')
                    continue;
                int curnode = node(i, j);
                if (i == 0 || i == nrow - 1 || j == 0 || j == ncol - 1)
                    uf.merge(node(i, j), border);
                if (i + 1 < nrow && board[i + 1][j] == 'O')
                    uf.merge(node(i + 1, j), curnode);
                if (j + 1 < ncol && board[i][j + 1] == 'O')
                    uf.merge(node(i, j + 1), curnode);
            }
        
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (uf.find(node(i, j)) == uf.find(border))
                    board[i][j] = 'O';
                else
                    board[i][j] = 'X';
    }
};
```