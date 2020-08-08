On a 2D plane, we place stones at some integer coordinate points.  Each coordinate point may have at most one stone.

Now, a move consists of removing a stone that shares a column or row with another stone on the grid.

What is the largest possible number of moves we can make?

 

Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Example 3:

Input: stones = [[0,0]]
Output: 0
 

Note:

1 <= stones.length <= 1000
0 <= stones[i][j] < 10000

#### Solutions

1. ##### UnionFind

- Connect stones pairs with the same row/column into communities. For each community with size greater 1, the maximum possible number of moves equals to iteratively removeing leaf nodes, i.e. : `size - 1`.

- Merging stones. Need to check all pairs, O(n2) complexity

```c++
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        return node;
    }
    bool merge(int node1, int node2) {
        int  f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return;
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        sizes[f2] += sizes[f1];
        nodes[f1] = f2;
    }
};
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        UnionFind uf(n);

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                if (stones[i][0] == stones[j][0] 
                || stones[i][1] == stones[j][1])
                    uf.merge(i, j);
            }
        int res = 0;
        for (int p = 0; p < n; p++)
            if (uf.nodes[p] == p)
                res += uf.sizes[p] - 1;
        
        return res;
    }
};
```

- mergging rows with columns, O(n)

```c++
struct UnionFind {
    vector<int> nodes, sizes;
    UnionFind(int size) : nodes(size), sizes(size, 1) {
        iota(nodes.begin(), nodes.end(), 0);
    }
    int find(int node) {
        if (nodes[node] != node)
            return nodes[node] = find(nodes[node]);
        return node;
    }
    void merge(int node1, int node2) {
        int  f1 = find(node1), f2 = find(node2);
        if (f1 == f2) return;
        if (sizes[f1] > sizes[f2])
            swap(f1, f2);
        sizes[f2] += sizes[f1];
        nodes[f1] = f2;
    }
};
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        UnionFind uf(20000);

        for (auto & p : stones)
            uf.merge(p[0], p[1] + 10000);
    
        unordered_set<int> coms;
        for (auto & p : stones) {
            coms.insert(uf.find(p[0]));
            // can be exluded
            // coms.insert(uf.find(p[1] + 10000));
        }
        
        return stones.size() - coms.size();
    }
};
```


2. ##### dfs

- Find all communities and their corresponding sizes using dfs.

```c++

```