#### Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)

```
Example 1:

[[0,0,1,0,0,0,0,1,0,0,0,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,1,1,0,1,0,0,0,0,0,0,0,0],
 [0,1,0,0,1,1,0,0,1,0,1,0,0],
 [0,1,0,0,1,1,0,0,1,1,1,0,0],
 [0,0,0,0,0,0,0,0,0,0,1,0,0],
 [0,0,0,0,0,0,0,1,1,1,0,0,0],
 [0,0,0,0,0,0,0,1,1,0,0,0,0]]

Given the above grid, return 6. Note the answer is not 11, because the island must be connected 4-directionally.

Example 2:

[[0,0,0,0,0,0,0,0]]

Given the above grid, return 0.
```

#### Note: The length of each dimension in the given grid does not exceed 50.


#### Solutions

1. ##### Union Find O(n + num1 * log(n)) S(n)

- You can also record the maxinum size in merge function of UnionFind to speed up the process.

```c++
class UnionFind {
private:
    int * nodes;
    int * sizes;
    int len;
    // int maxsize = 1;
public:
    UnionFind(int size) : len(size) {
        nodes = new int[size];
        sizes = new int[size];
        for (int i = 0; i < size; i++) {
            nodes[i] = i;
            sizes[i] = 1;
        }
    }
    ~UnionFind() {
        delete [] nodes; delete [] sizes;
    }
    int find(int node) {
        while (nodes[node] != node) {
            nodes[node] = nodes[nodes[node]];
            node = nodes[node];
        }
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1);
        int f2 = find(node2);
        if (f1 == f2)
            return false;
        else {
            if (sizes[f1] > sizes[f2])
                swap(f1, f2);
            nodes[f1] = f2;
            sizes[f2] += sizes[f1];
            // Or use a maxsize variable.
            // maxsize = max(sizes[f2], maxsize);
            return true;
        }
    }
    int maxsize() {
        int maxsize = 1;
        for (int i = 0; i < len; i++)
            if (sizes[i] > maxsize)
                maxsize = sizes[i];
        return maxsize;
    }
};
#define node(x, y) ((((x) * ncol) + (y)))
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int nrow = grid.size(); if (!nrow) return 0;
        int ncol = grid[0].size();

        UnionFind uf(nrow * ncol);

        int num1 = 0;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == 0)
                    continue;
                num1++;
                int curnode = node(i, j);
                if (i + 1 < nrow && grid[i + 1][j])
                    uf.merge(node(i + 1, j), curnode);
                if (j + 1 < ncol && grid[i][j + 1])
                    uf.merge(node(i, j + 1), curnode);
            }

        return num1 != 0 ? uf.maxsize() : 0;
    }
};
```

2. ##### dfs with recursion

```c++
class Solution {
public:
    int m, n;
    int area(vector<vector<int>> & grid, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1)
            return 0;
        grid[i][j] = 2;
        return 1 + area(grid, i + 1, j) 
                + area(grid, i, j + 1) 
                + area(grid, i, j - 1) 
                + area(grid, i - 1, j);
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size();

        int res = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                    res = max(res, area(grid, i, j));
        
        return res;
    }
};
```

2. iteration

- Bfs with queue as example.

```c++
class Solution {
public:
    int maxarea(vector<vector<int>> & grid, int x, int y) {
        queue<pair<int, int>> todos;
        todos.push(make_pair(x, y));
        int size = 0; grid[x][y] = 0;
        int nrow = grid.size();
        int ncol = grid[0].size();
        while (!todos.empty()) {
            int x = todos.front().first;
            int y = todos.front().second;
            todos.pop(); size++;
            if (x + 1 < nrow && grid[x + 1][y]) {
                todos.push(make_pair(x + 1, y));
                grid[x + 1][y] = 0;
            }
            if (y + 1 < ncol && grid[x][y + 1]) {
                todos.push(make_pair(x, y + 1));
                grid[x][y + 1] = 0;
            }
            if (x > 0 && grid[x - 1][y]) {
                todos.push(make_pair(x - 1, y));
                grid[x - 1][y] = 0;
            }
            if (y > 0 && grid[x][y - 1]) {
                todos.push(make_pair(x, y - 1));
                grid[x][y - 1] = 0;
            }
        }

        return size;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxsize = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j])
                    maxsize = max(maxsize, maxarea(grid, i, j));
        return maxsize;
    }
};
```