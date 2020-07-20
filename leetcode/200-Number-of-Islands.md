#### Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

```
Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3
```

#### Solutions

- See problem 130 for similar problem.

1. ##### dfs with recursion

```c++
class Solution {
public:
    void dfs(vector<vector<char>> & grid, int x, int y) {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
            return;
        if (grid[x][y] == '1') {
            grid[x][y] = '2';
            dfs(grid, x - 1, y);
            dfs(grid, x + 1, y);
            dfs(grid, x, y - 1);
            dfs(grid, x, y + 1);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == '1' && ++count)
                    dfs(grid, i, j);
        return count;
    }
};
```

2. ##### bfs with queue


3. ##### union find

- Treat all zeros as a union.

```c++
template <typename T>
class UnionFind {
private:
    T * nodes;
public:
    UnionFind(T size){
        nodes = new T[size];
        for (int i = 0; i < size; i++)
            nodes[i] = i;
    }

    ~UnionFind() {
        delete [] nodes;
    }

    T find(T node) {
        while (nodes[node] != node) {
            nodes[node] = nodes[nodes[node]];
            node = nodes[node];
        }
        return node;
    }

    void merge(const T & node1, const T & node2) {
        nodes[find(node1)] = find(node2);
    }

    bool is_connected(const T & node1, const T & node2) {
        return find(node1) == find(node2);
    }

};

#define node(x, y) ( (x) * ncol + (y) )
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nrow = grid.size(); if (!nrow) return 0;
        int ncol = grid[0].size();

        UnionFind<int> uf(nrow * ncol + 1);
        int water = nrow * ncol;

        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == '0')
                    uf.merge(node(i, j), water);
                else {
                    int curnode = node(i, j);
                    if (i + 1 < nrow && grid[i + 1][j] == '1')
                        uf.merge(node(i + 1, j), curnode);
                    if (j + 1 < ncol && grid[i][j + 1] == '1')
                        uf.merge(node(i, j + 1), curnode);
                }
            }

        unordered_set<int> islands;

        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++)
                if (!uf.is_connected(node(i, j), water))
                    islands.insert(uf.find(node(i, j)));

        return islands.size();
    }
};
```

Or count when merging in union find.


```c++
template <typename T>
class UnionFind {
private:
    T * nodes;
    int _size;

public:
    UnionFind(T size) : _size(size) {
        nodes = new T[size];
        for (int i = 0; i < size; i++)
            nodes[i] = i;
    }

    ~UnionFind() {
        delete [] nodes;
    }

    T find(T node) {
        while (nodes[node] != node) {
            nodes[node] = nodes[nodes[node]];
            node = nodes[node];
        }
        return node;
    }

    void merge(const T & node1, const T & node2) {
        int father1 = find(node1);
        int father2 = find(node2);
        if (father1 != father2) {
            nodes[father1] = father2;
            _size--;
        }
    }

    bool is_connected(const T & node1, const T & node2) {
        return find(node1) == find(node2);
    }

    inline int size() {
        return _size;
    }
};

#define node(x, y) ( (x) * ncol + (y) )
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nrow = grid.size(); if (!nrow) return 0;
        int ncol = grid[0].size();

        UnionFind<int> uf(nrow * ncol + 1);
        int water = nrow * ncol;

        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == '0')
                    uf.merge(node(i, j), water);
                else {
                    int curnode = node(i, j);
                    if (i + 1 < nrow && grid[i + 1][j] == '1')
                        uf.merge(node(i + 1, j), curnode);
                    if (j + 1 < ncol && grid[i][j + 1] == '1')
                        uf.merge(node(i, j + 1), curnode);
                }
            }
        // plus one water node
        return uf.size() - 1;

    }
};
```
Or count the number of `1` at first and decuce the count whenever make new merge and ignore all zeros.

```c++
#define node(x, y) ( (x) * ncol + (y) )
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int nrow = grid.size(); if (!nrow) return 0;
        int ncol = grid[0].size();

        UnionFind<int> uf(nrow * ncol);
        // remember to make the size member public.
        uf.size = 0;

        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == '1') {
                    uf.size++;
                    int curnode = node(i, j);
                    if (i + 1 < nrow && grid[i + 1][j] == '1')
                        uf.merge(node(i + 1, j), curnode);
                    if (j + 1 < ncol && grid[i][j + 1] == '1')
                        uf.merge(node(i, j + 1), curnode);
                }
            }
        return uf.size;

    }
};
```

Or

```c++
class Solution {
public:
    int nrow, ncol;
    inline int node(int i, int j) {
        return i * ncol + j;
    }
    int numIslands(vector<vector<char>>& grid) {
        nrow = grid.size(); if (!nrow) return 0;
        ncol = grid[0].size();
        UnionFind<int> uf(nrow * ncol);
        int numisaland = nrow * ncol;
        for (int i = 0; i < nrow; i++)
            for (int j = 0; j < ncol; j++) {
                if (grid[i][j] == '0')
                    numisaland--;
                else {
                    int curnode = node(i, j);
                    if (i + 1 < nrow && grid[i + 1][j] == '1' 
                        && uf.merge(node(i + 1, j), curnode) )
                        numisaland--;
                    if (j + 1 < ncol && grid[i][j + 1] == '1' 
                        && uf.merge(node(i, j + 1), curnode))
                        numisaland--;
                }
            }
        
        return numisaland;
    }
};
```