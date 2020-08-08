In a given 2D binary array A, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)

Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.

Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)

 

Example 1:

Input: A = [[0,1],[1,0]]
Output: 1
Example 2:

Input: A = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2
Example 3:

Input: A = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1
 

Constraints:

2 <= A.length == A[0].length <= 100
A[i][j] == 0 or A[i][j] == 1

#### Solutions

1. ##### bfs O(mn)

- Starting from an island, then bfs searching for the other island.
- Q, what if there are more than two islands?

```c++
class Solution {
public:
    int m, n;
    queue<pair<int, int>> q;
    // returen true represent the previous cell is a border
    bool dfs(vector<vector<int>> & A, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || A[i][j] == 2)
            return false;
        if (A[i][j] == 0) return true;
        A[i][j] = 2;
        bool l = dfs(A, i, j - 1);
        bool r = dfs(A, i, j + 1);
        bool u = dfs(A, i - 1, j);
        bool d = dfs(A, i + 1, j);
        if (l || r || u || d)
            q.emplace(i, j);
        return false;
    }
    int shortestBridge(vector<vector<int>>& A) {
        m = A.size(); n = A[0].size();
        bool find = false;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                if (A[i][j] == 1) {
                    dfs(A, i, j);
                    find = true;
                    break;
                }
            if (find) break;
        }
        // or
        // [&] {
        //     for (int i = 0; i < m; i++)
        //         for (int j = 0; j < n; j++)
        //             if (A[i][j] == 1) {
        //                 dfs(A, i, j); return;
        //             }
        // }();

        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        int step = 0;
        while (q.size()) {
            int size = q.size();
            while (size--) {
                auto [x, y] = q.front(); q.pop();
                for (auto & d : dirs) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n)
                        continue;
                    if (A[nx][ny] == 1) return step;
                    if (A[nx][ny] != 0) continue;
                    q.emplace(nx, ny);
                    A[nx][ny] = -1;
                }
            }
            step++;
        }
        
        return -1;
    }
};
```