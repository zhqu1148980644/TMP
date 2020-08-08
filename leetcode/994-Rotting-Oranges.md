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
        int m = grid.size(), n = grid[0].size();
        queue<int> q;
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        int good = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 2)
                    q.push(i * n + j);
                else if (grid[i][j] == 1)
                    good++;
        
        int minutes = 0;
        while (!q.empty()) {
            if (good == 0) break;
            int size = q.size();
            while (size--) {
                int x = q.front() / n;
                int y = q.front() % n;
                q.pop();
                for (auto & d : dirs) {
                    int curx = x + d[0];
                    int cury = y + d[1];
                    if (curx < 0 || cury < 0 
                        || curx >= m || cury >= n 
                        || grid[curx][cury] != 1)
                        continue;
                    grid[curx][cury] = 2;
                    q.push(curx * n + cury);
                    if (--good == 0) return minutes + 1;
                }
            }
            minutes++;
        }
        return good > 0 ? -1 : minutes;
    }
};
```