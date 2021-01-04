---
title: Number of Connected Components in an Undirected Graph
date: 2021-01-04
---
#### Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.

```
Example 1:

Input: n = 5 and edges = [[0, 1], [1, 2], [3, 4]]

     0          3
     |          |
     1 --- 2    4 

Output: 2

Example 2:

Input: n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]]

     0           4
     |           |
     1 --- 2 --- 3

Output:  1
```

#### Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

#### Solutions

1. ##### Union Find

```cpp
class UnionFind {
private:
    int * nodes;
    int * sizes;
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
        while (nodes[node] != node)
            node = nodes[node] = nodes[nodes[node]];
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
};
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        for (auto & e : edges)
            if (uf.merge(e[0], e[1]))
                n--;
        return n;
    }
};
```


2. ##### dfs

```cpp
class Solution {
public:
    void dfs(int node, vector<vector<int>> & adjs, vector<bool> & visited) {
        for (auto & outnode : adjs[node]) {
            if (!visited[outnode]) {
                visited[outnode] = true;
                dfs(outnode, adjs, visited);
            }
        }
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjs(n, vector<int>());
        for (auto & e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        int num_com = 0;
        vector<bool> visited(n, false);
        for (int node = 0; node < n; node++) {
            if (!visited[node]) {
                num_com++;
                visited[node] = true;
                dfs(node, adjs, visited);
            }
        }
        return num_com;
    }
};
```

3. ##### bfs

```cpp
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjs(n, vector<int>());
        for (auto & e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        int num_com = 0;
        queue<int> q;
        vector<bool> visited(n, false);
        for (int node = 0; node < n; node++) {
            if (visited[node]) continue;
            q.push(node);
            visited[node] = true;

            while (!q.empty()) {
                auto cur = q.front(); q.pop();
                for (auto & outnode : adjs[cur]) {
                    if (!visited[outnode]) {
                        visited[outnode] = true;
                        q.push(outnode);
                    }
                }
            }
            num_com++;
        }
        return num_com;
    }
};
```