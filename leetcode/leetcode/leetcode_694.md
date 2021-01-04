---
title: Number of Distinct Islands
date: 2021-01-04
---
#### Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.

```
Example 1:

11000
11000
00011
00011

Given the above grid map, return 1.

Example 2:

11011
10000
00001
11011

Given the above grid map, return 3.

Notice that:

11
1

and

 1
11

are considered different island shapes, because we do not consider reflection / rotation.
```

### Note: The length of each dimension in the given grid does not exceed 50. 


#### Solutions

1. ##### dfs with recursion

- We record each point's relative coordinate with respect to the top left point when traversing nodes in an island.

```cpp
class Solution {
public:
    void dfs(vector<vector<int>> & grid, vector<int> & coor, int x, int y, int & x0, int & y0) {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] != 1)
            return;
        grid[x][y] = 2;
        coor.push_back(x - x0);
        coor.push_back(y - y0);
        dfs(grid, coor, x + 1, y, x0, y0);
        dfs(grid, coor, x, y + 1, x0, y0);
        dfs(grid, coor, x - 1, y, x0, y0);
        dfs(grid, coor, x, y - 1, x0, y0);
    }
    int numDistinctIslands(vector<vector<int>>& grid) {
        int nrow = grid.size();
        int ncol = grid[0].size();
        set<vector<int>> islands;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == 1) {
                    vector<int> coor;
                    dfs(grid, coor, i, j, i, j);
                    islands.insert(coor);
                }
            }
        return islands.size();
    }
};
```


2. ##### dfs with stack

```cpp
class Solution {
public:
    void dfs(vector<vector<int>> & grid, vector<int> & coor, int x, int y) {
        stack<pair<int, int>> s;
        s.push(make_pair(x, y));

        int x0 = x, y0 = y;
        while (!s.empty()) {
            auto cur = s.top(); s.pop();
            x = cur.first; y = cur.second;
            if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] != 1)
                continue;
            coor.push_back(x - x0);
            coor.push_back(y - y0);
            grid[x][y] = 2;
            s.push(make_pair(x + 1, y));
            s.push(make_pair(x, y + 1));
            s.push(make_pair(x - 1,  y));
            s.push(make_pair(x, y - 1));
        }
    }
    int numDistinctIslands(vector<vector<int>>& grid) {
        int nrow = grid.size();
        int ncol = grid[0].size();
        set<vector<int>> islands;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == 1) {
                    vector<int> coor;
                    dfs(grid, coor, i, j);
                    islands.insert(coor);
                }
            }
        return islands.size();
    }
};
```