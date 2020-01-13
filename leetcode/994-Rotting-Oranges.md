####In a given grid, each cell can have one of three values:

-    the value 0 representing an empty cell;
-    the value 1 representing a fresh orange;
-    the value 2 representing a rotten orange.

Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.

 

```
Example 1:

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.
```
 

#### Note:

-    1 <= grid.length <= 10
-    1 <= grid[0].length <= 10
-    grid[i][j] is only 0, 1, or 2.

#### Solutions

1. ##### bfs with queue

```c++
class Solution {
public:

    int orangesRotting(vector<vector<int>>& grid) {
        int nrow = grid.size();
        int ncol = grid[0].size();
        queue<int> q;
        vector<bool> visited(nrow * ncol, false);
        vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        int good = 0;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (grid[i][j] == 2)
                    q.push(i * ncol + j);
                else if (grid[i][j] == 1)
                    good++;

        int minutes = 0;
        int x, y, curx, cury;
        while (!q.empty()) {
            // break if there are no good oranges.
            if (good == 0) break;
            int size = q.size();
            while (size--) {
                x = q.front() / ncol;
                y = q.front() % ncol;
                q.pop();
                for (auto dir : dirs) {
                    curx = x + dir[0];
                    cury = y + dir[1];
                    if (curx < 0 || cury < 0
                        || curx >= nrow || cury >= ncol
                        || grid[curx][cury] != 1)
                        continue;
                    grid[curx][cury] = 2;
                    q.push(curx * ncol + cury);
                    good--;
                }
            }
            minutes++;
        }

        return good > 0 ? -1 : minutes;
    }
};
```