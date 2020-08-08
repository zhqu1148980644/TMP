Given a m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:
1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
Notice that there could be some invalid signs on the cells of the grid which points outside the grid.

You will initially start at the upper left cell (0,0). A valid path in the grid is a path which starts from the upper left cell (0,0) and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid path doesn't have to be the shortest.

You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.

Return the minimum cost to make the grid have at least one valid path.

 


Example 1:

![](https://assets.leetcode.com/uploads/2020/02/13/grid1.png)
```
Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
Output: 3
Explanation: You will start at point (0, 0).
The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
The total cost = 3.
```

Example 2:

![](https://assets.leetcode.com/uploads/2020/02/13/grid2.png)
```
Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
Output: 0
Explanation: You can follow the path from (0, 0) to (2, 2).
```

Example 3:

![](https://assets.leetcode.com/uploads/2020/02/13/grid3.png)
```
Input: grid = [[1,2],[4,3]]
Output: 1
Example 4:

Input: grid = [[2,2,2],[2,2,2]]
Output: 3
Example 5:

Input: grid = [[4]]
Output: 0
```
 

#### Constraints:

- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 100


#### Solutions

- reference: https://leetcode-cn.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/solution/shi-wang-ge-tu-zhi-shao-you-yi-tiao-you-xiao-lu-2/
- Convert the problem into a shortestpath problem with `0` weight for connected edges(same sign in two nodes) and `1` weight/cost for nonconnected nodes.

1. ##### dijkstra O(mnlog(mn)) O((e + v) * log(e + v))

```c++
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(); if (!m) return 0;
        int n = grid[0].size();
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dis(m * n, INT_MAX);
        vector<bool> seen(m * n);
        pq.push({0, 0}); 
        dis[0] = 0;

        int target = m * n - 1;
        static int dir[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!pq.empty()) {
            auto [curdis, cur] = pq.top();
            pq.pop();
            if (seen[cur]) continue;
            if (cur == target) break;
            seen[cur] = true;
            int x = cur / n, y = cur % n;
            for (int i = 1; i <= 4; i++) {
                int nx = x + dir[i][0], ny = y + dir[i][1];
                int outnode = nx * n + ny;
                int newdis = curdis + !(i == grid[x][y]);
                if (nx < 0 || ny < 0 || nx >= m || ny >= n 
                || dis[outnode] < newdis || seen[outnode])
                    continue;
                dis[outnode] = newdis;
                pq.push({newdis, outnode});
            }
        }

        return dis[target];
    }
};
```


2. ##### 0-1 bfs O(mn)

- Bfs can be used to find the shorted path in an unweighted graph(or graph with equals weigts for all edges), as nodes with smaller distance will be visited before nodes with larger distance which is achieved by pushing nodes at the back of queue and visiting(popping) at the front.
    - In this problem, edge weights are no longer the same, the property mentioned above will not be hold.
- To maintain this property, we can push 0 edges at the front and push 1 edges at the back with a `deque`.
- `dis` vector is used for guaranting each node will be pushed at most twice(front and back), though the time complexity will not change if we simply use a `pair<node, dis>` as the element of deque.

```c++
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(); if (!m) return 0;
        int n = grid[0].size();
        deque<int> dq;
        vector<int> dis(m * n, INT_MAX);
        vector<bool> seen(m * n);
        dq.push_back(0);
        dis[0] = 0;

        int dir[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!dq.empty()) {
            int cur = dq.front(); dq.pop_front();
            if (seen[cur])
                continue;
            seen[cur] = true;
            int x = cur / n, y = cur % n;
            for (int i = 1; i <= 4; i++) {
                int nx = x + dir[i][0], ny = y + dir[i][1];
                int next = nx * n + ny;
                int newdis = dis[cur] + !(i == grid[x][y]);
                if (nx < 0 || ny < 0 || nx >= m || ny >= n || seen[next] || dis[next] < newdis)
                    continue;
                dis[next] = newdis;
                if (i == grid[x][y])
                    dq.push_front(next);
                else
                    dq.push_back(next);
            }
        }

        return dis[m * n - 1];
    }
};
```


3. ##### SPFA

```c++
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(); if (!m) return 0;
        int n = grid[0].size();
        
        queue<int> q;
        vector<int> dis(m * n, INT_MAX);
        // seen is used to ensuring there are no duplicates nodes in the queue
        vector<bool> seen(m * n);
        q.push(0); dis[0] = 0;

        int target = m * n - 1;
        int dirs[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (q.size()) {
            int cur = q.front(); q.pop();
            seen[cur] = false;
            int x = cur / n, y = cur % n;
            for (int i = 1; i <= 4; i++) {
                int nx = x + dirs[i][0], ny = y + dirs[i][1];
                if (nx < 0 || ny < 0 || nx >= m | ny >= n) continue;
                int next = nx * n + ny;
                int newdis = dis[cur] + (i != grid[x][y]);
                if (newdis < dis[next]) {
                    dis[next] = newdis;
                    if (!seen[next]) {
                        seen[next] = true;
                        q.push(next);
                    }
                }
            }
        }
        return dis[target];
    }
};
```