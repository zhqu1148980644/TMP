We are given a matrix with R rows and C columns has cells with integer coordinates (r, c), where 0 <= r < R and 0 <= c < C.

Additionally, we are given a cell in that matrix with coordinates (r0, c0).

Return the coordinates of all cells in the matrix, sorted by their distance from (r0, c0) from smallest distance to largest distance.  Here, the distance between two cells (r1, c1) and (r2, c2) is the Manhattan distance, |r1 - r2| + |c1 - c2|.  (You may return the answer in any order that satisfies this condition.)

 

Example 1:

Input: R = 1, C = 2, r0 = 0, c0 = 0
Output: [[0,0],[0,1]]
Explanation: The distances from (r0, c0) to other cells are: [0,1]
Example 2:

Input: R = 2, C = 2, r0 = 0, c0 = 1
Output: [[0,1],[0,0],[1,1],[1,0]]
Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2]
The answer [[0,1],[1,1],[0,0],[1,0]] would also be accepted as correct.
Example 3:

Input: R = 2, C = 3, r0 = 1, c0 = 2
Output: [[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
Explanation: The distances from (r0, c0) to other cells are: [0,1,1,2,2,3]
There are other answers that would also be accepted as correct, such as [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]].
 

Note:

1 <= R <= 100
1 <= C <= 100
0 <= r0 < R
0 <= c0 < C

#### Solutions

1. ##### sort O(nlog(n))

```c++
class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        vector<vector<int>> res;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) {
                res.push_back({i, j});
            }
        
        sort(res.begin(), res.end(), [&](auto & p1, auto & p2){
            return abs(p1[0] - r0) + abs(p1[1] - c0)
                 < abs(p2[0] - r0) + abs(p2[1] - c0);
        });

        return res;
    }
};
```

2. ##### bucket sort O(n)

```c++
class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        // the size of buckets can be optimized
        vector<vector<vector<int>>> buckets(R + C);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                buckets[abs(i - r0) + abs(j - c0)].push_back({i, j});
        
        vector<vector<int>> res;
        for (auto & bv : buckets)
            for (auto & p : bv)
                res.push_back(move(p));

        return res;
    }
};
```


3. ##### bfs O(n)

```c++
class Solution {
public:
#define node(x, y) ((x) * C + (y))
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        vector<vector<int>> res;

        vector<bool> visited(R * C);
        queue<pair<int, int>> q;
        q.push({r0, c0}); visited[node(r0, c0)] = true;

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            res.push_back({r, c});
            for (auto & d : dirs) {
                int x = r + d[0], y = c + d[1];
                if (x < 0 || y < 0 || x >= R || y >= C || visited[node(x, y)])
                    continue;
                visited[node(x, y)] = true;
                q.push({x, y});
            }
        }

        return res;
    }
};
```

4. ##### math

- Check the official answer.