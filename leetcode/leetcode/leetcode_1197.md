---
title: Minimum Knight Moves
date: 2021-01-04
---
In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at square [0, 0].

A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.



Return the minimum number of steps needed to move the knight to the square [x, y].  It is guaranteed the answer exists.

 

Example 1:

Input: x = 2, y = 1
Output: 1
Explanation: [0, 0] → [2, 1]
Example 2:

Input: x = 5, y = 5
Output: 4
Explanation: [0, 0] → [2, 1] → [4, 2] → [3, 4] → [5, 5]
 

Constraints:

|x| + |y| <= 300

#### Solutions

1. ##### bfs with pruning

```cpp
class Solution {
public:
    int minKnightMoves(int x, int y) {
        if (!x && !y) return 0;
        x = abs(x) + 50; y = abs(y) + 50;
        vector<vector<bool>> visited(400, vector<bool>(400));
        queue<pair<int, int>> q;
        visited[50][50] = true;
        q.push({50, 50});


        int step = 0;
        int dirs[8][2] = {{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, 
                          {2, 1}, {2, -1}, {1, -2}, {-1, -2}};
        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto [i, j] = q.front(); q.pop();
                int curdis = abs(x - i) + abs(y - j);
                for (auto & d : dirs) {
                    int nx = i + d[0], ny = j + d[1];
                    if (nx < 0 || ny < 0 || nx >= 400 || ny >= 400) continue;
                    int newdis = abs(nx - x) + abs(ny - y);
                    // pruning
                    if (curdis > 4 && newdis > curdis) continue;
                    if (visited[nx][ny]) continue;
                    if (nx == x && ny == y) return step + 1;
                    visited[nx][ny] = true;
                    q.emplace(nx, ny);
                }
            }
            step++;
        }

        return 0;
    }
};
```