#### A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

```
Example:

Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
Output: [1,1,2,3]

Explanation:

Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0

Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0

Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0

Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0

Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0
```

#### Follow up:

- Can you do it in time complexity O(k log mn), where k is the length of the positions?

#### Solutions

1. ##### Union Find O(m * n + k(log(m * n)))

- With the strategy of path compression and union by rank, the average time complexity of unionfind is `log(n)`.
- Whenever make and operation, plus the number of islands by 1, and check the neighbors of this added island, deduce the number of islands by 1 whenever merged with a neighbor island.

```c++
class UnionFind {
private:
    int * sizes;
    int * nodes;
public:
    UnionFind(int size) {
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
            return true;
        }
    }
    int size(int node) {
        return sizes[node];
    }
};

#define node(x, y) ((((x) * n) + (y)))
class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        UnionFind uf(m * n);
        unordered_set<int> grid;
        vector<int> res;

        int num_islands = 0;
        for (auto & pos : positions) {
            int x = pos[0], y = pos[1];
            if (grid.count(node(x, y))) {
                res.push_back(num_islands);
                continue;  
            }
            int curnode = node(x, y);
            num_islands += 1;
            if (x + 1 < m && grid.count(node(x + 1, y)))
                if (uf.merge(node(x + 1, y), curnode))
                    num_islands--;
            if (y + 1 < n && grid.count(node(x, y + 1)))
                if (uf.merge(node(x, y + 1), curnode))
                    num_islands--;
            if (x - 1 >= 0 && grid.count(node(x - 1, y)))
                if (uf.merge(node(x - 1, y), curnode))
                    num_islands--;
            if (y - 1 >= 0 && grid.count(node(x, y - 1)))
                if (uf.merge(node(x, y - 1), curnode))
                    num_islands--;
            grid.insert(node(x, y));
            res.push_back(num_islands);
        }

        return res;
    }
};
```


Or

```c++
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size, int initial) : nodes(size, initial), sizes(size, 1) {}
    int find(int node) {
        while (nodes[node] != node)
            node = nodes[node] = nodes[nodes[node]];
        return node;
    }
    bool merge(int node1, int node2) {
        int f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return false;
        else {
            if (sizes[f2] < sizes[f1])
                swap(f1, f2);
            nodes[f1] = f2;
            sizes[f2] += sizes[f1];
            return true;
        }
    }
};
class Solution {
public:
    int nrow, ncol;
    inline int node(int x, int y) {
        return x * ncol + y;
    }
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        nrow = m, ncol = n;
        int water =  nrow * ncol;
        UnionFind uf(nrow * ncol + 1, water);
        vector<int> res;
        int numisland = 0;

        for (auto & vpos : positions) {
            int x = vpos[0], y = vpos[1];
            int curnode = x * ncol + y;
            if (uf.nodes[curnode] == water) {
                uf.nodes[curnode] = curnode;
                numisland++; 
                if (x + 1 < nrow && uf.find(curnode + ncol) != water)
                    if (uf.merge(curnode + ncol, curnode))
                        numisland--;
                if (y + 1 < ncol && uf.find(curnode + 1) != water)
                    if (uf.merge(curnode + 1, curnode))
                        numisland--;
                if (x - 1 >= 0 && uf.find(curnode - ncol) != water)
                    if (uf.merge(curnode - ncol, curnode))
                        numisland--;
                if (y - 1 >= 0 && uf.find(curnode - 1) != water)
                    if (uf.merge(curnode - 1, curnode))
                        numisland--;
            }
            res.push_back(numisland);
        }
        return res;
    }
};
```