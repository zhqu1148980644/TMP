In a 2D grid of 0s and 1s, we change at most one 0 to a 1.

After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).

Example 1:

Input: [[1, 0], [0, 1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: [[1, 1], [1, 0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
Example 3:

Input: [[1, 1], [1, 1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.
 

Notes:

1 <= grid.length = grid[0].length <= 50.
0 <= grid[i][j] <= 1.

#### Solutions

1. ##### UnionFind O(n2) n: row size

- Utilize the rank array in UnionFind structure which represents the size of community.
- After the UnionFind structure has bee settled(connected all communities), for each zero point, record the sum size of it's four neibor communities.

```c++
struct UnionFind {
    vector<int> nodes, sizes;
    int maxsize = 0;
    UnionFind(int size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        else
            return nodes[node];
    }
    int merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        maxsize = max(maxsize, sizes[f2] += sizes[f1]);
        nodes[f1] = f2;
        return true;
    }
};
class Solution {
public:
#define node(x, y) ((x) * n + (y))
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        UnionFind uf(m * n);
        int maxsize = 0;
        // Connect all elements
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (!grid[i][j]) continue;
                maxsize = 1;
                if (i + 1 < m && grid[i + 1][j])
                    uf.merge(node(i, j), node(i + 1, j));
                if (j + 1 < n && grid[i][j + 1])
                    uf.merge(node(i, j), node(i, j + 1));
            }
        // for each zero, check it's four beighbor's com size.
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        maxsize = max(maxsize, uf.maxsize);
        unordered_map<int, int> neighbor;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) continue;
                for (auto & d : dirs) {
                    int nx = i + d[0], ny = j + d[1];
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n || !grid[nx][ny])
                        continue;
                    int fa = uf.find(node(nx, ny));
                    neighbor[fa] = uf.sizes[fa];
                }
                int sumsize = 1;
                for (auto [com, size] : neighbor)
                    sumsize += size;
                maxsize = max(sumsize, maxsize);
                neighbor.clear();
            }
        
        return maxsize;
    }
};
```

2. ##### dfs O(n2)

- This solution is more suitable when islands are sparse.
- Use dfs to find the size of each connected community and mark them with unique community indexes, after all communities has been marked, use the same strategy as the previous solution to find the sumsize of four neighboring communities.

```c++
class Solution {
public:
    unordered_map<int, int> sizes;
    int m, n;
    int dfs(vector<vector<int>> & grid, int i, int j, int index) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1)
            return 0;
        grid[i][j] = index;
        return 1 + dfs(grid, i + 1, j, index) 
                    + dfs(grid, i, j + 1, index)
                    + dfs(grid, i - 1, j, index) 
                    + dfs(grid, i, j - 1, index);
    }
    int largestIsland(vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size();
        // index starts at 2 to avoid mixing with 1/0
        int index = 2;
        int maxsize = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                    maxsize = max(maxsize, sizes[index++] = dfs(grid, i, j, index));
        
        unordered_set<int> neighbors;
        int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) continue;
                for (auto & d : dirs) {
                    int nx = i + d[0], ny = j + d[1];
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n || !grid[nx][ny])
                        continue;
                    neighbors.insert(grid[nx][ny]);
                }
                int size = 1;
                for (auto neindex : neighbors)
                    size += sizes[neindex];
                maxsize = max(maxsize, size);
                neighbors.clear();
            }
        return maxsize;
    }
};
```