---
title: Path With Maximum Minimum Value
date: 2021-01-04
---
Given a matrix of integers A with R rows and C columns, find the maximum score of a path starting at [0,0] and ending at [R-1,C-1].

The score of a path is the minimum value in that path.  For example, the value of the path 8 →  4 →  5 →  9 is 4.

A path moves some number of times from one visited cell to any neighbouring unvisited cell in one of the 4 cardinal directions (north, east, west, south).

 

Example 1:



Input: [[5,4,5],[1,2,6],[7,4,6]]
Output: 4
Explanation: 
The path with the maximum score is highlighted in yellow. 
Example 2:



Input: [[2,2,1,2,2,2],[1,2,2,2,1,2]]
Output: 2
Example 3:



Input: [[3,4,6,3,4],[0,2,1,1,7],[8,8,3,2,7],[3,2,4,9,8],[4,1,2,0,0],[4,6,5,4,3]]
Output: 3
 

Note:

1 <= R, C <= 100
0 <= A[i][j] <= 10^9

#### Solutions

- Shortest path problem

1. ##### dijkstra O(mn)

```cpp
aclass Solution {
public:
#define node(x, y) ((x) * n + (y))
    int maximumMinimumPath(vector<vector<int>>& A) {
        int m = A.size(), n = A[0].size();        

        vector<bool> visited(m * n);
        vector<int> scores(m * n, INT_MIN);
        scores[0] = 0;
        priority_queue<pair<int, int>> pq;
        pq.emplace(A[0][0], 0);
        
        int target = m * n - 1;
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        while (pq.size()) {
            auto [score, node] = pq.top(); pq.pop();
            if (visited[node]) continue;
            if (node == target) return score;
            visited[node] = true;
            int x = node / n, y = node % n;
            for (auto & d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                int out = node(nx, ny);
                if (visited[out]) continue;
                if (min(score, A[nx][ny]) > scores[out]) {
                    scores[out] = min(score, A[nx][ny]);
                    pq.emplace(scores[out], out);
                }
            }
        }

        return -1;
    }
};
```