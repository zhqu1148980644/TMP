---
title: Cut Off Trees for Golf Event
date: 2021-01-04
---
You are asked to cut off trees in a forest for a golf event. The forest is represented as a non-negative 2D map, in this map:

0 represents the obstacle can't be reached.
1 represents the ground can be walked through.
The place with number bigger than 1 represents a tree can be walked through, and this positive number represents the tree's height.
In one step you can walk in any of the four directions top, bottom, left and right also when standing in a point which is a tree you can decide whether or not to cut off the tree.

You are asked to cut off all the trees in this forest in the order of tree's height - always cut off the tree with lowest height first. And after cutting, the original place has the tree will become a grass (value 1).

You will start from the point (0, 0) and you should output the minimum steps you need to walk to cut off all the trees. If you can't cut off all the trees, output -1 in that situation.

You are guaranteed that no two trees have the same height and there is at least one tree needs to be cut off.

Example 1:

Input: 
[
 [1,2,3],
 [0,0,4],
 [7,6,5]
]
Output: 6
 

Example 2:

Input: 
[
 [1,2,3],
 [0,0,0],
 [7,6,5]
]
Output: -1
 

Example 3:

Input: 
[
 [2,3,4],
 [0,0,5],
 [8,7,6]
]
Output: 6
Explanation: You started from the point (0,0) and you can cut off the tree in (0,0) directly without walking.
 

Constraints:

1 <= forest.length <= 50
1 <= forest[i].length <= 50
0 <= forest[i][j] <= 10^9

#### Solutions

1. ##### bfs search

- In each step, use bfs to find the shorted path to the tree with the minimum height, when the current minimum height tree is found, start a new bfs from this tree.

```cpp
class Solution {
public:
#define node(x, y) (((x) * n + (y)))
    int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int m, n;
    int cutOffTree(vector<vector<int>>& forest) {
        if (forest[0][0] == 0) return -1;

        m = forest.size(), n = forest[0].size();
        vector<int> trees;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest[i][j] > 1)
                    trees.push_back(node(i, j));

        sort(trees.begin(), trees.end(), [&](int k1, int k2) {
            return forest[k1 / n][k1 % n] < forest[k2 / n][k2 % n];
        });

        int res = 0;
        vector<bool> visited(m * n);
        int origin = 0;
        for (int i = 0; i < trees.size(); i++) {
            int step = bfs(origin, trees[i], forest, visited);
            if (step == -1) return -1;
            res += step;
            origin = trees[i];
        }
        
        return res;
    }
    int bfs(int origin, int target, vector<vector<int>>& forest, vector<bool> & visited) {
        fill(visited.begin(), visited.end(), false);
        queue<int> q; q.push(origin);
        int step = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto cur = q.front(); q.pop();
                int x = cur / n, y = cur % n;
                if (cur == target) {
                    forest[x][y] = 1;
                    return step;
                }
                for (auto & d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    int next = node(nx, ny);
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n 
                    || visited[next] || !forest[nx][ny])
                        continue;
                    q.push(next); visited[next] = true;
                }
            }
            step++;
        }
        return -1;
    }
};
```

2. ##### other search strategies