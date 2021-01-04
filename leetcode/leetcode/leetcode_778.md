---
title: Swim in Rising Water
date: 2021-01-04
---
On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).

Now rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distance in zero time. Of course, you must stay within the boundaries of the grid during your swim.

You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?

Example 1:

Input: [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.

You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
Example 2:

Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6

The final route is marked in bold.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
Note:

2 <= N <= 50.
grid[i][j] is a permutation of [0, ..., N*N - 1].

#### Solutions

1. ##### greedy with priority queue

- In each step, move to a unseen surrounding(surround all visited grids) grid with the minimum height(move doest not cost time, only need to wait). The least time equals to the maximum height within the travsered path.

```cpp
class Solution {
public:
#define node(x, y) ((x) * n + (y))
    int swimInWater(vector<vector<int>>& grid) {
        auto cmp = [&](auto & p1, auto & p2) {
            return grid[p1.first][p1.second] > grid[p2.first][p2.second];
        };
        int n = grid.size();

        vector<bool> seen(n * n);
        seen[node(0, 0)] = true;
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        pq.push({0, 0});

        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        int maxh = 0;
        while (pq.size()) {
            auto [x, y] = pq.top(); pq.pop();
            maxh = max(maxh, grid[x][y]);
            for (auto & d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                int next = node(nx, ny);
                if (nx < 0 || ny < 0 || nx >= n || ny >= n || seen[next])
                    continue;
                if (nx == n - 1 && ny == n - 1)
                    return max(maxh, grid[nx][ny]);
                seen[next] = true;
                pq.push({nx, ny});
            }
        }

        return maxh;
    }
};
```

2. ##### binary search
